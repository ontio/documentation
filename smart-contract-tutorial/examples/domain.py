from boa.interop.System.Runtime import Log, GetTrigger, CheckWitness, Notify
from boa.interop.System.ExecutionEngine import GetScriptContainer, GetExecutingScriptHash
from boa.interop.System.Blockchain import GetHeight, GetHeader
from boa.interop.System.Storage import GetContext, Get, Put, Delete


def Main(operation, args):
    if operation == 'Query':
        domain = args[0]
        return Query(domain)

    if operation == 'Register':
        domain = args[0]
        owner = args[1]
        return Register(domain, owner)

    if operation == 'Transfer':
        domain = args[0]
        to = args[1]
        return Transfer(domain, to)

    if operation == 'Delete':
        domain = args[0]
        return Delete(domain)

    return False


def Query(domain):
    context = GetContext()
    owner = Get(context, domain);

    Notify('query', domain)
    if owner != None:
        return False

    return owner

def Register(domain, owner):
    context = GetContext()
    occupy = Get(context, domain);
    if occupy != None:
        return False;
    Put(context, domain, owner)
    Notify('Register', domain, owner)

    return True

def  Transfer(domain, to):
    if to == None:
        return False

    context = GetContext()
    owner = Get(context, domain)
    if owner == None:
        return False
    if owner == to:
        return True

    is_owner = CheckWitness(owner)

    if not is_owner:
        return False

    Put(context, domain, to)
    Notify('Transfer', domain)

    return True

def  Delete(domain):
    context = GetContext()
    occupy = Get(context, domain);
    if occupy == None:
        return False;

    Delete(context, domain)
    Notify('Delete', domain)

    return True
