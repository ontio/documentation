# Python Smart Contract


## Compile


### example 1：HelloWorld smart contract

```
from boa.blockchain.vm.Ont.Storage import GetContext, Put


def Main():
    context = GetContext()

    Put(context, 'hello', 'world')
  
```

### example 2：Smart contract template

```
from boa.blockchain.vm.Ont.Runtime import Log, Notify
from boa.blockchain.vm.System.ExecutionEngine import GetScriptContainer, GetExecutingScriptHash
from boa.blockchain.vm.Ont.Transaction import *
from boa.blockchain.vm.Ont.Blockchain import GetHeight, GetHeader
from boa.blockchain.vm.Ont.Action import RegisterAction
from boa.blockchain.vm.Ont.Runtime import GetTrigger, CheckWitness
from boa.blockchain.vm.Ont.TriggerType import Application, Verification
from boa.blockchain.vm.Ont.Output import GetScriptHash, GetValue, GetAssetId
from boa.blockchain.vm.Ont.Storage import GetContext, Get, Put, Delete
from boa.blockchain.vm.Ont.Header import GetTimestamp, GetNextConsensus

def Main(operation, args):
    trigger = GetTrigger()

    if trigger == Application():
        if operation == 'add':
            a = args[0]
            b = args[1]
            return Add(a, b)

        if operation == 'compare':
            a = args[0]
            b = args[1]
            return Compare(a, b)

    return False


def Add(a, b):
    return a + b


def Compare(a, b):
    if a > b:
        return a

    return b
```

### example 3：Domain service smart contract

```
from boa.blockchain.vm.Ont.Runtime import Log, Notify
from boa.blockchain.vm.System.ExecutionEngine import GetScriptContainer, GetExecutingScriptHash
from boa.blockchain.vm.Ont.Transaction import *
from boa.blockchain.vm.Ont.Blockchain import GetHeight, GetHeader
from boa.blockchain.vm.Ont.Action import RegisterAction
from boa.blockchain.vm.Ont.Runtime import GetTrigger, CheckWitness
from boa.blockchain.vm.Ont.TriggerType import Application, Verification
from boa.blockchain.vm.Ont.Output import GetScriptHash, GetValue, GetAssetId
from boa.blockchain.vm.Ont.Storage import GetContext, Get, Put, Delete
from boa.blockchain.vm.Ont.Header import GetTimestamp, GetNextConsensus

def Main(operation, args):
    trigger = GetTrigger()

    if trigger == Application():
        if operation == 'query':
            domain = args[0]
            return Query(domain)

        if operation == 'register':
            domain = args[0]
            owner = args[1]
            return Register(domain, owner)

        if operation == 'transfer':
            domain = args[0]
            to = args[1]
            return Transfer(domain, to)

        if operation == 'delete':
            domain = args[0]
            return Delete(domain)

    return False


def Query(domain):
    context = GetContext()
    owner = Get(context, domain);

    if owner != None:
        return False

    return owner

def Register(domain, owner):
    context = GetContext()
    occupy = Get(context, domain);
    if occupy != None:
        return False;
    Put(context, domain, owner);
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

    return True

def  Delete(domain):
    context = GetContext()
    owner = Get(context, domain)

    if owner == None:
        return False

    is_owner = CheckWitness(owner)

    if not is_owner:
        return False

    Delete(context, domain)

    return True;


```
