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