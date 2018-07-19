---
title:
keywords: sample homepage
sidebar: Dapp_en
permalink: SmartX_Tutorial_en.html
folder: doc_en/Dapp
giturl: https://github.com/ontio/ontology-smartcontract/master/smart-contract-tutorial/SmartX_Tutorial.md
---

<h1 align="center">SmartX Tutorial</h1>

<p align="center" class="version">Version 1.0.0 </p>

English / [中文](./SmartX_Tutorial_zh.html)

## What is SmartX

SmartX is a one-stop IDE that can be used to compile, deploy, and invoke smart contracts. It provides a range of smart contract templates and a powerful online editor. In the future, smart contract developers will be able to trade smart contracts they write and collaborate with others to develop a smart contract.

In the future, SmartX will work like GitHub to be a distributed software project hosting platform. It will support multiple people to participate in and share a complex contract, and at the time same, implement a set of economic incentives and integrate fair governance policies to reflect the contributions of each participant, which will encourage smart contract writing, transaction, collaboration, community building, and the development of a valuable smart contract ecosystem.

## Sign Up

[SmartX website](http://smartx.ont.io/#/)

First you should create a ONT ID to manage your smart contract project. Click the "Sign Up" button in the home page to enter the registration page as figure shows.

![sign up](http://wx1.sinaimg.cn/mw690/0060lm7Tly1fstiyin8yaj319e0os78v.jpg)

After entering the password twice (the password length should be greater than 6), clicking the "Create a New ONT ID" button to sign up successfully.You need to click the "Download" button to download the ONT ID file and back up the private key.The ONT ID file stores your encrypted ONT ID and private key, and the private key is the only credential for you to recover the ONT ID account and must be properly kept.

![ONT ID file](http://wx2.sinaimg.cn/mw690/0060lm7Tly1fstj2bsv5xj30sh0icjtk.jpg)

![](http://wx4.sinaimg.cn/mw690/0060lm7Tly1fstj32gzk8j30o80iimz7.jpg)

If you already have the ONT ID, you can click the "Recover your ONT ID" button to recover the ONT ID. After entering the private key and two passwords, click the "Recovery Your ONT ID" button to get your ONT ID successfully.

![recovery](http://wx2.sinaimg.cn/mw690/0060lm7Tly1fstj5gqw3xj30np0jdmyy.jpg)

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

[>> Java SDK](https://ontio.github.io/documentation/ontology_java_sdk_smartcontract_en.html)

[>> TS SDK](https://ontio.github.io/documentation/ontology_ts_sdk_smartcontract_en.html)

![Deploy contract](https://s1.ax1x.com/2018/04/04/CpIcAe.png)

## Step 3 - Invoke a smart contract

Last, you can run the method of your contract. You can select the method you want to run, enter the correct parameter value, click the **Run** button, and invoke the smart contract. The result of the invocation will be printed in the output box.

![Invoke smart contract](https://s1.ax1x.com/2018/04/04/CpoCEF.png)

In addition to Smartx, you can use the Ontology SDK to deploy a contract. For more information, please refer to related documents.

[>> Java SDK](https://ontio.github.io/documentation/ontology_java_sdk_smartcontract_en.html)

[>> TS SDK](https://ontio.github.io/documentation/ontology_ts_sdk_smartcontract_en.html)

