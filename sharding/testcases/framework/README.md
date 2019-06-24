## Ontology Test Framework


Ontology测试框架，用于对Ontology基础链做完整的白盒测试。

测试框架目标：

* 从开发者角度提供更好的测试工具
* 降低底层模块的测试难度
* 提高当前Ontology的测试覆盖率。
* 更丰富的单元测试
* 更细粒度的模块间集成测试
* 测试自动化

功能需求：

* P2P Simulator
  * 和当前网络模块相同的软件接口，框架中其他模块可以mock使用
  * 可以实现至少20个节点的网络节点模拟
  * 可配置peer节点的网络行为，包括容错行为的模拟
  * 可模拟P2P内部模块运行，包括NeighTable，Link等
* Ledger Simulator
  * 提供和当前账本模块相同的软件接口
  * 提供内存和leveldb两种账本实现方式
  * 可模拟Ledger内部模块运行，包括OverlayDB等
* TxPool Simulator
  * 提供当前交易池模块相同的软件接口
  * 模拟TxPool内部validator运行
* Consensus Simulator
  * 提供当前共识相同的软件接口
  * 模拟VBFT内部算法运行
* Block Sync Simulator
  * 提供当前区块同步的软件接口
  * 模拟Syncer内部与网络其他节点的消息交互
* Smart-Contract
  * 模拟分片治理场景，完成分片管理合约测试
  * 模拟通用智能合约运行环境

