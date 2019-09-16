# Trust anchor - verify claim

1. 根据协议生成二维码，通过 ontoAuth Signing server 扫码签名

   协议内容：

   ```json
   {
   	"action": "claimQuery",
   	"version": "v1",
     "id": "10ba038e-48da-487b-96e8-8d3b99b6d18a",
   	"params": {
   		"dappName": "dapp Name",
   		"dappIcon": "dapp Icon",
   		"claimTemplate": "claims:yus_chinese_id_authentication", // 需知道claimTemplate 名称
   		"expire": 1546415363,
   		"callback": "http://101.132.193.149:4027/api/v1/claim/callback"
   	}
   }
   
   ```

示例二维码

![a](../../../res/queryClaim.png)





 2. 签名之后，ontoAuth 调用接口把本地存储的claim发送到web-app

    [接口及参数说明](../../../framework/trust-anchor/restful-api.md#credential_id)

 3. web-app会向TA验证公钥, 并且会向链上查询claim状态，返回结果

    ```json
    {
        "action": "claimCallback",
    		"id": "10ba038e-48da-487b-96e8-8d3b99b6d18a",
        "error": 0,
        "desc": "SUCCESS", // 最终结果
        "version": "v1"
    }
    ```

    至此验证流程完毕