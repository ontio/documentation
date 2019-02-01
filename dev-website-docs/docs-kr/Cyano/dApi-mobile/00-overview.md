
## dApi-mobile and dApi for chrome

dApi for mobile support interface less than dApi for chrome, for query balance or information of chain can use [explorer api](http://dev-docs.ont.io/#/docs-en/explorer/overview).

For detail please reference to :

* [dAPI-chrome](https://github.com/ontio/ontology-dapi)
* [dAPI-mobile](https://github.com/ontio-cyano/cyano-bridge)
* [dapi-universal](https://github.com/ontio-cyano/dapi-universal)

### dApi register


#### dApi for mobile
```
import { client } from 'cyanobridge'
client.registerClient();

```

#### dApi for chrome
```
import {client} from 'ontology-dapi'
client.registerClient({})

```

### getAccount or getIdentity

getAccount or getIdentity

#### dApi for mobile

```
import { client } from 'cyanobridge'

const params = {
​    dappName: 'My dapp',
​    dappIcon: '' // some url points to the dapp icon
}

try {
​    const res = await client.api.asset.getAccount(params);
    const res = await client.api.identity.getIdentity(params);
​    console.log(res)
} catch(err) {
​    console.log(err)
}

```


#### dApi for chrome
```
account = await client.api.asset.getAccount()
res = await client.api.identity.getIdentity();
```

### login



#### dApi for mobile

```
const params = {
​    type: 'account',// account or identity that will sign the message
​    dappName: 'My dapp', // dapp's name
​    dappIcon: 'http://mydapp.com/icon.png', // some url that points to the dapp's icon
​    message: 'test message', // message sent from dapp that will be signed by native client
​    expired: new Date('2019-01-01').getTime(), // expired date of login
​    callback: '' // callback url of dapp
}
let res;
try {
​    res = await client.api.message.login(params);
​    console.log(res)
}catch(err) {
​    console.log(err)
}
```

#### dApi for chrome
```
const result = await client.api.message.signMessage({ message });
```

### invoke smart contract



#### dApi for mobile

```
const scriptHash = 'cd948340ffcf11d4f5494140c93885583110f3e9';
const operation = 'test'
const args = [
​    {
​        type: 'String',
​        value: 'helloworld'
​    }
]
const gasPrice = 500;
const gasLimit = 20000;
const payer = 'AecaeSEBkt5GcBCxwz1F41TvdjX3dnKBkJ'
const config = {
​    "login": true,
​    "message": "invoke smart contract test",
​    "qrcodeUrl": "" ,
    "callback": ""
}
const params = {
          scriptHash,
          operation,
          args,
          gasPrice,
          gasLimit,
          payer,
          config
        }
try {
   const res = await client.api.smartContract.invoke(params);
   } catch(err) {
​    console.log(err)
}

```

#### dApi for chrome
```
const contract = '16edbe366d1337eb510c2ff61099424c94aeef02';
const gasLimit = 30000;
const gasPrice = 500;

parameters = [
   {
	name: "msg",
	type: "String",
	value: "hello world"
   } 
]
 params = {
            contract,
            method,
            parameters,
            gasPrice,
            gasLimit
}
await client.api.smartContract.invoke(params)

```