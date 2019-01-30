

## SmartX的3个版本

[SmartX 正式版](https://smartx.ont.io)是官方正式版本，它提供了最完善的功能和最稳定的开发体验。

[SmartX 测试版](https://smartxbeta.ont.io)是测试版本，它包含了本体最新开发的功能。但其中也会存在一些bug，这些bug会在SmartX社区版中优先得到解决。

[SmartX 社区版](http://smartxdebug.ont.io)是开源社区版本。为了更好的开发体验，我们移除了登录功能，开发者可以直接进行开发。 


## Debug流程

#### 步骤1 - 创建一个Python工程
选择Python语言和空白模板, 从[OEP4Sample.py](https://github.com/tonyclarking/python-template/blob/master/OEP4Sample/OEP4Sample.py])中拷贝代码并复制到编辑器中。 

![step1.png](https://upload-images.jianshu.io/upload_images/150344-cc24c675bc9a3267.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

![step1.png](https://upload-images.jianshu.io/upload_images/150344-cdb9c5585a074881.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

#### 步骤2 - 编译

点击编译按钮编译智能合约。ABI与AVM文件会自动生成且操作码会显示在底部。

![step2.png](https://upload-images.jianshu.io/upload_images/150344-807d1c9add5be98f.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

#### 步骤3 - 设置断点

点击行数的左侧空白处，将会生成一个红色的断点。

![step3.png](https://upload-images.jianshu.io/upload_images/150344-82b13a0a1c8372db.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

#### 步骤4 - 以Debug模式运行

第一，选择要执行的函数，再选择参数的类型并填充参数值。

第二，点击“Debug run”按钮。

![step4.png](https://upload-images.jianshu.io/upload_images/150344-f890c3707e48fea4.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

点击“Debug run”按钮之后，“Debug run”的字样会显示成“Waiting”。

#### 步骤5 - 使用Debug控制面板

使用导航面板debug

![debug panel.png](https://upload-images.jianshu.io/upload_images/150344-6b73326a3e5388e4.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

从左到右: 

继续运行(跳转到下一个断点), 终止debug, 跳转到下一行, 跳转到下一个操作码, 清屏

## Debug控制面板

控制面板会显示当前合约的基础信息。

![5.png](https://upload-images.jianshu.io/upload_images/150344-34922a573030a17a.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

从左到右:

Logs: 显示合约执行的结果

Evaluation Stack: 临时存放当前合约正在使用的数据

Alt Stack: 存储所有变量。Locals将会从Alt Stack中读取本地变量

History: 显示操作码的执行记录

Locals: 显示当前合约的本地变量

Storage:  智能合约的数据库


## 用控制面板改变参数

#### 如何改变变量值

改变括号内的数值，其相对应的变量值将会改变。

![change locals.png](https://upload-images.jianshu.io/upload_images/150344-8c122e82a7d02d7d.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

#### 如何改变存储的数据值

你可以使用Storage来新增或删除任意合约数据。

![change storage.png](https://upload-images.jianshu.io/upload_images/150344-52aa4be649311046.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)


#### 如何使用转换工具

选择转换工具并填入相应的数据。

工具面板的功能列表

![tool panel.png](https://upload-images.jianshu.io/upload_images/150344-46e5da4eb0a4a8c1.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

```
