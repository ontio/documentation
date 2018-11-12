
## Versions of SmartX

[SmartX](https://smartx.ont.io) is the officially released version that provides the most advanced features and stable development experience.  

[SmartX beta](https://smartxbeta.ont.io) is the beta released version that includes the newest features. But there may be some bugs existed, which will be fixed in the SmartX community edition first. 

[SmartX debug](http://smartxdebug.ont.io) is the open-source community edition. Login function has been removed for more convenient development. 



## Debug procedure

#### Step1 - Create a python project

Select the python language and blank template. Copy the code in [OEP4Sample.py](https://github.com/tonyclarking/python-template/blob/master/OEP4Sample/OEP4Sample.py](https://github.com/tonyclarking/python-template/blob/master/OEP4Sample/OEP4Sample.py)
) to editor.

![step 1.png](https://upload-images.jianshu.io/upload_images/150344-cc24c675bc9a3267.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

![step 1.png](https://upload-images.jianshu.io/upload_images/150344-cdb9c5585a074881.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

#### Step2 - Compile

Clicking the "Compile" button to compile the smart contract. ABI and AVM will be generated and Opcode will be displayed at the bottom.

![step2.png](https://upload-images.jianshu.io/upload_images/150344-807d1c9add5be98f.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

#### Step3 - Set a breakpoint

Clicking on the left side of the line number, a red breakpoint will appear.

![step3.png](https://upload-images.jianshu.io/upload_images/150344-82b13a0a1c8372db.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

#### Step4 - Debug run

Firstly, Select run function, choose the type of the parameters, and fill in the parameters.

Secondly, click the "Debug Run" button.

![step4.png](https://upload-images.jianshu.io/upload_images/150344-f890c3707e48fea4.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

After clicking the "Debug Run" button, "Debug run" will be "Waiting".

#### Step5 - Use the debug panel

Use the navigation panel to debug.

![debug panel.png](https://upload-images.jianshu.io/upload_images/150344-6b73326a3e5388e4.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

From the left to the right: 

Continue(jump to the next breakpoint), Debug Stop, Step Over Line, Step Over Opcode, Clear (clear the window)

## Debug panel

The panel displays basic information about the current smart contract.

![5.png](https://upload-images.jianshu.io/upload_images/150344-34922a573030a17a.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

From the left to the right:

Logs: display execution result

Evaluation Stack: temporarily store the data it is currently executing 

Alt Stack: store all variables. The locals read variables from alt stack

History: display the history of execution of OP code

Locals: display local variables associated with the current context.

Storage:  the database of the smart contract


## Change parameters in console

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
