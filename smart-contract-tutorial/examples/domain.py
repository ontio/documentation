from boa.interop.Neo.Runtime import Log, GetTrigger, CheckWitness
from boa.interop.System.ExecutionEngine import GetScriptContainer, GetExecutingScriptHash
from boa.interop.Neo.Transaction import *
from boa.interop.Neo.Blockchain import GetHeight, GetHeader
from boa.interop.Neo.Action import *
from boa.interop.Neo.Output import GetScriptHash, GetValue, GetAssetId
from boa.interop.Neo.Storage import GetContext, Get, Put, Delete
from boa.interop.Neo.Header import GetTimestamp, GetNextConsensus


Push = RegisterAction('event', 'operation', 'msg')

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

    Push('query', domain)
    if owner != None:
        return False

    return owner

def Register(domain, owner):
    context = GetContext()
    occupy = Get(context, domain);
    if occupy != None:
        return False;
    Put(context, domain, owner)
    Push('Register', domain, owner)
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
    Push('Transfer', domain)

    return True

def  Delete(domain):
    context = GetContext()
    occupy = Get(context, domain);
    if occupy != None:
        return False;
    # Put(context, domain, owner)
    Push('Delete', domain)

    return True
