
Cyano 是一个Chrome插件和移动端钱包。不仅实现了钱包功能，还实现了DAPI协议（[OEP-6](https://github.com/backslash47/OEPs/blob/oep-dapp-api/OEP-6/OEP-6.mediawiki) 和 [CEP1](https://github.com/ontio-cyano/CEPs/blob/master/CEP1.mediawiki)）Provider相关功能，例如SmartX部署和调用合约时通过Cyano与链交互，钱包中的DApp与钱包通信等。

DAPI是为基于Ontology开发的DAPP提供的轻量级去中心化API，支持DAPP通过chrome插件钱包、手机钱包、桌面钱包与Ontology通信。针对不同平台的DAPP需求协议略有差别，但对应的dAPI接口相似。目前支持两套协议：

* dAPI for chrome的协议是[OEP-6](https://github.com/backslash47/OEPs/blob/oep-dapp-api/OEP-6/OEP-6.mediawiki) 
* dAPI for mobile的协议是[CEP1](https://github.com/ontio-cyano/CEPs/blob/master/CEP1.mediawiki)

协议中有provider和client两个角色，分别是钱包方和DAPP。dAPI for chrome接口比较丰富，而dAPI for mobile除了支持登录和调用合约等主要接口，还支持扫描和唤醒钱包。




