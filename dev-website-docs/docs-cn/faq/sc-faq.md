

#### 1. 什么是Native合约，Native合约有哪些方法可以调用？
    
    Native合约是ONT，ONG合约及其它主链治理合约。可调用方法可在[源码](https://github.com/ontio/ontology/tree/master/smartcontract/service/native)中获得。

    Native合约的[Hash地址](https://github.com/ontio/ontology/blob/master/smartcontract/service/native/utils/params.go)。
    
    [ONT与ONG合约方法](https://github.com/ontio/ontology/blob/master/smartcontract/service/native/ont/utils.go)。
    
    [ONTID合约方法](https://github.com/ontio/ontology/blob/master/smartcontract/service/native/ontid/init.go)。
    
    [Param合约方法](https://github.com/ontio/ontology/blob/master/smartcontract/service/native/global_params/global_params.go)。
    
    [Auth合约方法](https://github.com/ontio/ontology/blob/master/smartcontract/service/native/auth/auth.go)。
    
    [Governance合约方法](https://github.com/ontio/ontology/blob/master/smartcontract/service/native/governance/governance.go)。

#### 2. 什么是跨合约调用，跨合约调用时的注意点？

    跨合约调用是指在A合约调用B合约的方法。跨合约调用分为两种：
    ```
    1、普通合约之间的相互调用；
    
    2、跨Native合约的调用。
    ```

    区别在于:
    
    第一种应该使用[```ontology.interop.System.App.py```](https://github.com/ontio/ontology-python-compiler/blob/master/ontology/interop/System/App.py)中的```DynamicAppCall```或是```RegisterAppCall```方法，参数构造时可使用```state```方法或是直接使用```[]```；
    
    第二种应该使用[```ontology.interop.Ontology.Native```](https://github.com/ontio/ontology-python-compiler/blob/master/ontology/interop/Ontology/Native.py)中的```Invoke```方法，参数构造时必须使用```ontology.builtins```中的```state```方法。

    具体可参照[python-template中的模板](https://github.com/ONT-Avocados/python-template/blob/master/DynamicCallContract/DynamicCallContract_compiler2.0.py)。
   
#### 3. 合约Hash也是对应一个账户吗？有私钥吗？
    
    合约Hash也是对应一个帐户的。方式是把合约的Hash当作大端地址即为其自身帐户，常用于DAPP合约作为资金托管帐户。

    有，不过合约的帐户的私钥是不可知的。
    
    3.1 什么是大小端地址？什么是Base58地址？
        
    大端地址与小端地址与Base58地址是一一对应的关系。

    举例来说，某合约的Hash是：996a2e5905752b88e6fdb337dbb9852889efe2fa，则合约帐户的大端地址为其Hash，其小端地址为：fae2ef892885b9db37b3fde6882b7505592e6a99，其Base58地址(通常以大写的```A```开头)为AeeSSDwLehqHqmcf8eHbciXAsGzVk93X4w。
    
    3.2 转换工具有哪些？
        
    [SmartX](https://smartx.ont.io/#/)上面创建你的项目之后，在编译、布署一栏有一个工具选项。可以进行转换。
    同时，这里也有一个非常好用的[网址](https://peterlinx.github.io/DataTransformationTools/)可以进行格式转换！！！
    
    3.3 即然合约帐户的私钥不可知，那该如何把资产转出合约呢？
        
    请参照下面关于```CheckWitness```的功能。
    
    3.4 怎样在合约内部拿到合约帐户的地址？
        
    编译器里提供了库函数，即[```ontology.interop.System.ExecutionEngine```](https://github.com/ontio/ontology-python-compiler/blob/master/ontology/interop/System/ExecutionEngine.py)中的```GetExecutingScriptHash()```方法，返回值却为合约Hash的反序，或合约帐户的小端地。在合约内部可直接用来作为地址来使用，构造转账交易。

#### 4. 关于交易回滚？
    
    交易回滚一般是在合约执行时，当不满足执行条件时，被调用的函数自动抛出错误或异常，在此次调用中所有被改变的状态回滚到被调用之前的状态，即链上状态不会改变。在[编译器1.0](https://github.com/ontio/neo-boa)中，使用```raise Exception("error msg")```。
    在[编译器2.0](https://github.com/ontio/ontology-python-compiler)中，可使用```raise Exception("error msg")``` 或```assert(condition)```。推荐使用编译器2.0的```assert()```方法。其特点为如果被调用的函数抛错，不会产生手续费。

#### 5. Ontology智能合约存在不存在像Ethereum合约那样的修饰符```payable```类似的回调机制？
    
    不存在。必须通过帐户主动调用合约函数来触发合约函数的执行。

#### 6. 怎样能像Ethereum合约那样在合约内部拿到```msg.sender```及```msg.value```这种值？
    
    调用帐户在主动调用合约函数时，需要把自已的帐户地址及转账资产的大小以参数的形式传入合约。在合约内部使用```CheckWitness```对调用帐户进行验签，及进行资产额度的合法性判断。

#### 7.  支持的数据类型有哪些以及用法？

    数据类型有```ByteArray```, ```Integer(uint255)```, ```String```, ```List```, ```Map``` 。

    ```ByteArray```常用于地址参数。

    ```Integer```常用于值，如帐户余额、 索引值、状态值等等。

    ```String```常用于推送消息至全网的```Notify```中的关键字、```Map```中的关键字。

    ```List```常用于存放一列的数据，其元素的类型可以相同， 也可以不同，存取时常使用[```ontology.interop.System.Runtime```](https://github.com/ontio/ontology-python-compiler/blob/master/ontology/interop/System/Runtime.py)中的```Serialize()```与```Deserialize()```。
    支持```append()```操作，不久将支持```remove()```操作。

    ```Map```常用于存入一个带有键值的数据表，存取时常使用[```ontology.interop.System.Runtime```](https://github.com/ontio/ontology-python-compiler/blob/master/ontology/interop/System/Runtime.py)中的```Serialize()```与```Deserialize()```。根据不存在的键值取```Map```中不存在的值是不合法的，会直接抛错。

#### 8. Ontology合约中有私有函数或公有函数的区分吗？

    我们可以将```Main()```中包括的函数看作公有函数，对于一本合约，我们只能调用```Main()```中包含的那些函数，建议函数名以小写字母开头。
    对于未被包含在```Main()```中的函数，可以视为私有函数，建议以下划线```_```开头，这些函数，只能被本合约中的其他函数调用，我们不可能在合约下部直接调用这些未包含在```Main()```中的函数。
    换句话说，```Main()```是调用合约函数的入口。


#### 9.  什么是合约迁移？
    
    Ontology合约是支持合约迁移的功能的，方法是使用[```ontology.interop.Ontology.Contract```](https://github.com/ontio/ontology-python-compiler/blob/master/ontology/interop/Ontology/Contract.py)中的```Migrate()```方法。
    其结果表现为旧合约失效，新合约生效，但旧合约的数据会全部被迁移到新合约中。
    注意调用该函数的手续费会受到新合约规模大小以及旧合约里的状态数据量有关。

#### 10. 合约内部，转账ONT, ONG,与OEP4时，数量应该怎么填写？
    
    ONT没有精度，即最小单位为1，如果要转2个ONT，使用```Invoke()```，调用时应该写：
    ```
    ONTAddress = bytearray(b'\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x01')
    param = state(fromAcct, toAcct, 2)
    res = Invoke(0, ONTAddress, "transfer", [param])
    # make sure transfer ONT succeed
    assert(res)
    ```

    ONG精度为9，即最小单位为1*10^(-9)，如果要转3.12个ONG，使用```Invoke()```，调用时应该写：
    ```
    ONGAddress = bytearray(b'\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x02')
    param = state(fromAcct, toAcct, 3120000000)
    res = Invoke(0, ONGAddress, "transfer", [param])
    # make sure transfer ONG succeed
    assert(res)
    ```

    假设某OEP4代币MST精度为12，如果要转1.234567891234，可使用```DynamicAppCall```或是```RegisterAppCall```方法。以前者为例：
    ```
    # Suppose the contract hash of OEP4 is b55f2af8d0d8d2bd3d398ced3b3559caa894b536
    OEP4ReversedContractHash = Base58ToAddress(ALm9fJfhgNrwt4TM6bmmqvQbZs3hugi3et)
    param = [fromAcct, toAcct, 1234567891234]
    res = DynamicAppCall(OEP4ReversedContractHash, "transfer", param)
    # make sure transfer MST succeed
    assert(res)
    ```

#### 11. 合约内数据可见性，如何做到对某些人不可见且可信?
    
    11.1 将原始数据```originData```加盐值```salt```进行哈希，保存好原始数据及盐值及哈希结果```hash```。
    
    11.2 将哈希结果```hash```，保存到链上。
    
    11.3 原始数据已产生且不可见阶段。
    
    11.4 等需要公开数据时，提供原始数据```originData```及盐值```salt```，可对```hash```进行验证。

#### 12. 如何对合约帐户内的ONT产生的ONG解绑？
    
    详见[unboundWithdrawONG_compiler2.0.py](https://github.com/ONT-Avocados/python-template/blob/master/UnboundWithdrawONG/unboundWithdrawONG_compiler2.0.py)。
    
#### 13. 合约内如何验证帐户签名？
    
    使用[```ontology.interop.System.Runtime```](https://github.com/ontio/ontology-python-compiler/blob/master/ontology/interop/System/Runtime.py)```CheckWitness```方法。
    ```CheckWitness(fromAcct)```有两个功能：

    1. 验证当前的函数调用者是不是```fromAcct```,若是（验证签名），则验证通过。

    2. 检查当前函数调用者是不是一个合约A，若是合约A，且是从合约A发起的去执行函数，则验证通过(验证```fromAcct```是不是[```GetCallingScriptHash()```](https://github.com/ontio/ontology-python-compiler/blob/master/ontology/interop/System/ExecutionEngine.py)的返回值)。 


#### 14. 执行与预执行的区别是什么？

    执行与预执行的对象是合约函数。
    
    执行是指会改变合约中的状态，根据逻辑运算的复杂度、改变合约中状态的次数以及被改变状态所占存储的大小收取燃料费。

    预执行是指查询链上合约中的状态，不会收取燃料费。

#### 15. 交易落账时间
    
    本地```TestMode```即```http://127.0.0.1```Solo模式下，一般要6秒落帐，不经过共识，出块时间为6秒。

    测试网```polaris```即```http://polaris1.ont.io```模式下，正常落帐时间为1秒。有交易时的出块速度为1秒，无交易时的出块速度为30秒。

    主网```dappnode```即```http://dappnode1.ont.io```模式下，正常落帐时间为1秒。有交易时的出块速度为1秒，无交易时的出块速度为30秒。

#### 16. 本地节点CLI测试时，我看到了帐户下面的ONT，但怎样产生ONG阿？
    
    16.1 查看钱包里第一个帐户的ONT, ONG余额：
    ```
    ontology.exe asset balance 1
    ```
    
    16.2 产生ONG的方式，要进行ONT的转账，然后解绑，再提取ONG。注：下面的1含义为钱包中的第一个帐户。
    ```
    ontology.exe asset transfer --from=1 --to=1 --amount=100000000 --asset=ont

    ontology.exe asset unboundong 1

    ontology.exe asset withdrawong 1

    ```


#### 17. 关于地址，Base58地址，ByteArray地址，大端地址，小端地址，还有反序，好烦人，怎么办？
    
    通常以大```A```开头的地址是Base58地址。小端地址是指Base58地址对应的ByteArray的Hex形式。
    我们使用sdk调用合约函数时，当构造交易时，需要把Base58地址转为小端地址的形式。
    小端地址和大端地址互为反序，我们很少会用到，这里给出两个用到的场景：

    18.1 需要直接向合约帐户转帐(不通过调用合约函数)。我们需要把合约Hash当作合约帐户的大端地址，构造交易转账。
    
    18.2 当进行动态合约的调用```DynamicAppCall```时，其中的被调用合约的地址参数应该是合约Hash的反序，即被调用合约的小端地址。


#### 18. 合约=逻辑+状态,如何写逻辑，如何存取改状态？
    
    18.1 关于逻辑部分，可以参考[编译器2.0](https://github.com/ontio/ontology-python-compiler)，或直接参考[合约模版](https://github.com/ONT-Avocados/python-template)。
    
    18.2 关于存取状态，
        
        
    18.2.1 存状态，使用```Put(GetContext(), theKey, theValue)```，此操作会更改链上合约内的状态，即将```theKey```对应的值更改为```theValue```。
    
    18.2.2 取状态，使用```value = Get(GetContext(), theKey)```，此操作会查询链上合约内```theKey```对应的状态值。



#### 19.  开发合约=>编译合约=>部署合约=>调用合约=>测试合约的流程与工具有哪些？

    19.1 开发合约：

    19.1.1 智能合约中使用的函数可以在[编译器1.0](https://github.com/ontio/neo-boa)和[编译器2.0](https://github.com/ontio/ontology-python-compiler)找到引用接口，推荐使用2.0编译器。

    19.1.2. 可以使用的函数也可以在[SmartX](https://smartx.ont.io/)上面得到提示。注：SmartX是一种在线合约开发、编译、布署网站。[这里](https://ontio.github.io/documentation/SmartX_Tutorial_en.html)是SmartX使用教程。
    
    19.2 合约编译:

    19.2.1 使用本地编译器编译

    19.2.2 通过[SmartX](https://smartx.ont.io/)编译，推荐使用SmartX。

    19.3 合约布署：
    
    19.3.1 可以通过SmartX，连上cyano wallet(Ontology的cyano wallet是一种谷歌浏览器钱包，可以用Ethereum的MetaMask来类比)，然后指定网络(或IP地址)，可将合约布署到本地网、或测试网、或主网。

    19.3.2 在启动节点的情况下，可以[通过[Cli](https://github.com/ontio/ontology/blob/master/docs/specifications/cli_user_guide_CN.md#5-%E6%99%BA%E8%83%BD%E5%90%88%E7%BA%A6)，将合约布署到本地、测试网或主网。

    19.4 合约测试：

    19.4.1 SmartX上可以进行运行、调试合约内的函数。

    19.4.2 可以通过Cli运行、调试合约函数。

    19.4.3 可以以通过go/java/ts/python sdk 来测试合约，sdk中包含一些OEP4 OEP5 OEP8调用的相关例子可供参考。详细信息，请在[官方github帐号](https://github.com/ontio)下面找到对应的sdk查看。


#### 20.  OEP4, OEP5, OEP8协议的区别？
    
    如果你对```ERC20```，```ERC721```以及```ERC1155```熟悉，那么```OEP4```对应于```ERC20```，```OEP5```对应于```ERC721```，```OEP8```对应于```ERC1155```。

    如果对Ethereum中的这三种协议不熟悉的话， 简单来说，

    OEP4是同质化资产的协议，资产之间互不区分。

    OEP5是非同质化资产的协议，每个资产是唯一的，不同资产是互相区分的。

    OEP8相当于OEP4与OEP5的结合体，即包含不同种类的资产，每种资产的数量是多个的，每种资产内部是同质的，不同资产是不同质的。

    [此处](https://github.com/ontio/OEPs/tree/master/OEPS)有更详细的协议介绍，[此处](https://github.com/ONT-Avocados/python-template)有协议实现的合约模版。

#### 21.  暂时目前```for i in range```不支持，但是支持```for i in list```。
    ```
    # Below wrong 
    i = 0
    for i in range(10):
        Notify([i])
    # Below corret
    L = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
    for i in L:
        Notify([i])
    ```

#### 22.  debug合约所需的测试节点怎么产生，即调试合约的本地测试节点？

    可以在[```runtime.go```](https://github.com/ontio/ontology/blob/master/smartcontract/service/neovm/runtime.go)中，增加打印信息来调试被调用的合约函数，观察合约函数执行到哪一步出了问题。


#### 23.  测试合约时，如何对执行的notify或是预执行的数据解析？
    
    23.1 解析```Notify```，以OEP4的```transferMulti```为例：
    
        ```
        ontology.exe info status d8e5863a54f368ad950d0993d38eb504c7eddafdd39dcc81d5676887fe35 b1cf
        Transaction states:
        {
        "TxHash": "d8e5863a54f368ad950d0993d38eb504c7eddafdd39dcc81d5676887fe35b1cf",
        "State": 1,
        "GasConsumed": 13509000,  // 执行合约函数所消耗的ONG即0.013509
        "Notify": [
            {
                "ContractAddress": "3310277e27a0ed749a3525ca2f898ebcd7d6631e",
                "States": [
                    "7472616e73666572", // transfer的HexString
                    "616f2a4a38396ff203ea01e6c070ae421bb8ce2d",  // fromAcct(AQf4Mzu1YJrhz9f3aRkkwSm9n3qhXGSh4p)的小端地址
                    "aa6e06c79f864152ab7f3139074aad822ffea855",  // toAcct(AXK2KtCfcJnSMyRzSwTuwTKgNrtx5aXfFX)的小端地址
                    "00e40b5402"  // amount=10000000000的HexNumber的反序
                ]
            },
            {
                "ContractAddress": "3310277e27a0ed749a3525ca2f898ebcd7d6631e",
                "States": [
                    "7472616e73666572",
                    "616f2a4a38396ff203ea01e6c070ae421bb8ce2d",
                    "aa6e06c79f864152ab7f3139074aad822ffea855",   // toAcct(AVXf5w8WD2y6jV1Lzi36oSKYNif1C7Surc)的小端地址
                    "00e40b5402"
                ]
            },
            {
                "ContractAddress": "3310277e27a0ed749a3525ca2f898ebcd7d6631e",
                "States": [
                    "7472616e73666572",
                    "616f2a4a38396ff203ea01e6c070ae421bb8ce2d",
                    "aa6e06c79f864152ab7f3139074aad822ffea855",    // toAcct(ANTPeXCffDZCaCXxY9u2UdssB2EYpP4BMh)的小端地址
                    "00e40b5402"
                ]
            },
            {
                "ContractAddress": "0200000000000000000000000000000000000000",
                "States": [
                    "transfer",
                    "AQf4Mzu1YJrhz9f3aRkkwSm9n3qhXGSh4p",
                    "AFmseVrdL9f9oyCzZefL9tG6UbviEH9ugK",
                    13509000
                ]
            }
        ]
        }
        ``` 

    23.2 解析预执行返回的数据：
    
    23.2.1 合约返回的是数字：将预执行的结果(若为空或```00```则为零)进行反序(每一个字节作为一个单位进行反序)，然后作为十六进制数字转换为十进制，即为我们想要得到的数据。

    23.2.2 合约返回的是字符串：将预执行的结果作为十六进制字符串，转换为字符串，即为我们想要的字符串。

    23.2.3 合约返回的是地址：将预执行的结果作为小端地址，转换为Base58地址，即为我们想要得到的地址。

    23.2.4 合约返回的是布尔：将预执行的结果转为数字后，若为零则```False```，若为1则```True```。

    23.2.5 合约返回的是List: 将预执行的结果，依次取出，按照以上基本数据类型进行解析，即得到想要的结果。

#### 24.  如何像Ethereum合约上面那样做权限管理？
    
    [这里]()给出了权限管理的合约模版。

#### 25.  合约内没有定时器，需要外部触发。

    合约内没有定时器，但提供了获取当前时间戳的函数，即[```ontology.interop.System.Runtime```](https://github.com/ontio/ontology-python-compiler/blob/master/ontology/interop/System/Runtime.py)中的```GetTime()```函数，返回值的单位为秒。
    因需要在合约外部进行触发，比如后台添加一个定时调用合约函数的功能，为防止误操作，最好在合约被调用函数内部，通过获取到的当前时间戳对调用该函数的时间进行规范处理。

#### 26.  在线转换数据工具有两个，所有版本的sdk都支持了数据类型的转换。

    工具一：[DataTransformationTools](https://peterlinx.github.io/DataTransformationTools/)。
    
    工具二：[SmartX](https://smartx.ont.io/#/)右上方区域中的Tools或工具选项。
