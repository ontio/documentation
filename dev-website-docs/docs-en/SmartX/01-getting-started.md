

## Sign In

After registration, you already have the ONT ID file. You just need to select this file and enter the password to sign in as shown in the figure.

![sign in](http://wx1.sinaimg.cn/mw690/0060lm7Tly1fstj6i5no6j30o00lcac9.jpg)

After signed in, you will enter the project list page. You can choose to open an existing smart contract project or create a new one.

![create project](http://upload-images.jianshu.io/upload_images/150344-a3d3385d889e1dd0.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

## Step 1 - Write & Compile  

we have built the [Smartx](http://smartx.ont.io) to help you with all these things.
We now support smart contracts that run in **NeoVM**.

* **For NeoVM**, please refer [SmartX](http://smartx.ont.io) to write, compile, deploy, and invoke smart contracts. 

First, you create a project and choose a language you are good at to write your smart contract.

![Select language](http://wx2.sinaimg.cn/mw690/0060lm7Tly1fstjbsyc5uj30jd0dcaai.jpg)

Then you enter the main editor page and the middle area is the contract editor. The bottom area prints the running output and the right area is the operation panel.

![Compile contract](https://s1.ax1x.com/2018/04/04/CpIdpR.png)

### Write a smart contract

Now, you can enjoy coding your smart contracts and we provide some useful contract templates for you to start writing easily.

You can check more specific [examples](https://github.com/ontio/documentation/tree/master/smart-contract-tutorial/examples) here.

### Compile a smart contract

After you finish your smart contract, you can click the **Compile** button on the operation panel to compile your code. 

If your code is correct, your smart contract will be compiled to the ABI and AVM file, and will be displayed on the operation panel.

## Step 2 - Deploy a smart contract

Next, you can deploy the smart contract on the blockchain by clicking the **Deploy** button. If you choose to deploy the contract on the TestNet, it is free, that is, no gas will be consumed. The result of the deployment will be printed in the output box. You can copy the results of the transaction hash to the Ontology blockchain browser to further confirm the success of the deployment.

In addition to Smartx, you can use the Ontology SDK to deploy a contract. For more information, please refer to related documents.


![Deploy contract](https://s1.ax1x.com/2018/04/04/CpIcAe.png)

## Step 3 - Invoke a smart contract

Last, you can run the method of your contract. You can select the method you want to run, enter the correct parameter value, click the **Run** button, and invoke the smart contract. The result of the invocation will be printed in the output box.

![Invoke smart contract](https://s1.ax1x.com/2018/04/04/CpoCEF.png)

In addition to Smartx, you can use the Ontology SDK to deploy a contract. For more information, please refer to related documents.


## Step 4 - Debug a smart contract

#### Set a breakpoint

Clicking on the left side of the line number, a red breakpoint will appear.

![step3.png](https://upload-images.jianshu.io/upload_images/150344-82b13a0a1c8372db.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

#### Debug run

Firstly, Select run function, choose the type of the parameters, and fill in the parameters.

Secondly, click the "Debug Run" button.

![step4.png](https://upload-images.jianshu.io/upload_images/150344-f890c3707e48fea4.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

After clicking the "Debug Run" button, "Debug run" will be "Waiting".

#### Use the debug panel

Use the navigation panel to debug.

![debug panel.png](https://upload-images.jianshu.io/upload_images/150344-6b73326a3e5388e4.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

From the left to the right: 

Continue(jump to the next breakpoint), Debug Stop, Step Over Line, Step Over Opcode, Clear (clear the window)

### Debug panel

The panel displays basic information about the current smart contract.

![5.png](https://upload-images.jianshu.io/upload_images/150344-34922a573030a17a.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

From the left to the right:

Logs: display execution result

Evaluation Stack: temporarily store the data it is currently executing 

Alt Stack: store all variables. The locals read variables from alt stack

History: display the history of execution of OP code

Locals: display local variables associated with the current context.

Storage:  the database of the smart contract


### Change parameters in console

#### How to change variable

Change a value in parentheses and the value of the corresponding variable will be changed.

![change locals.png](https://upload-images.jianshu.io/upload_images/150344-8c122e82a7d02d7d.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

#### How to change storage

You can add or delete any key and its corresponding value in storage console.

![change storage.png](https://upload-images.jianshu.io/upload_images/150344-52aa4be649311046.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)


#### How to use transform tool in debugging

Select a function you want to use and fill the data into space.

Function list of Tool panel

![tool panel.png](https://upload-images.jianshu.io/upload_images/150344-46e5da4eb0a4a8c1.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

```



