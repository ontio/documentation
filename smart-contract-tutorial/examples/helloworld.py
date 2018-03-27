from boa.blockchain.vm.Ont.Storage import GetContext, Put


def Main():
    context = GetContext()

    Put(context, 'hello', 'world')