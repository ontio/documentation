
本体客户端 `Ontology CLI` 提供了丰富的功能，在这一部分，我们将手把手地教你使用客户端。

### 命令

目前支持的命令如下表所示，你可以在需要的时候使用 `help` 命令在终端中查看。

```shell
ontology help
```

|     命令     |               描述               |
| :----------: | :------------------------------: |
|   account    |             账户管理             |
|     info     |           获取链上信息           |
|    asset     |             资产管理             |
|   contract   |        部署与调用智能合约        |
|    import    |       从文件中导入区块数据       |
|    export    |       将区块数据导出到文件       |
|   buildtx    |             构造交易             |
|    sigtx     |             签署交易             |
| multisigaddr |           生成多签地址           |
|  multisigtx  |           签署多签交易           |
|    sendtx    |        发送序列化后的交易        |
|    showtx    | 以 JSON 格式显示序列化交易的信息 |
|   help, h    |           显示帮助信息           |

### 参数

目前支持的命令行参数如下表所示，你可以在需要的时候使用 `help` 命令在终端中查看。

```shell
ontology help
```

<table cellspacing=0 border=1>
    <tr>
        <td align="center" style=min-width:50px>参数</td>
        <td align="center" style=min-width:50px>选项</td>
        <td align="center" style=min-width:50px>描述</td>
    </tr>
    <tr>
        <td style=min-width:50px rowspan="5">系统参数</td>
    </tr>
    <tr>
        <td align="center" style=min-width:50px>--config</td>
        <td align="center" style=min-width:50px>指定客户端的创世区块配置文件路径（默认为主网创世区块的配置）</td>
    </tr>
    <tr>
        <td align="center" style=min-width:50px>--loglevel</td>
        <td align="center" style=min-width:50px>设置输出的日志级别（0-Trace，1-Debug，2-Info，3-Warn， 4-Error，5-Fatal，6-MaxLevel，默认为默2）</td>
    </tr>
    <tr>
        <td align="center" style=min-width:50px>--disable-event-log</td>
        <td align="center" style=min-width:50px>用于关闭智能合约执行时输出的事件日志以提升节点的交易执行性能（默认开启）</td>
    </tr>
    <tr>
        <td align="center" style=min-width:50px>--data-dir</td>
        <td align="center" style=min-width:50px>指定区块数据的存放目录（默认为 ./Chain）</td>
    </tr>
    <tr>
        <td style=min-width:50px rowspan="4">账户参数</td>
    </tr>
    <tr>
        <td align="center" style=min-width:50px>--wallet, -w</td>
        <td align="center" style=min-width:50px>指定客户端钱包文件的路径（默认为 ./wallet.dat）</td>
    </tr>
    <tr>
        <td align="center" style=min-width:50px>--account, -a</td>
        <td align="center" style=min-width:50px>指定客户端的账户地址（默认为钱包默认账户）</td>
    </tr>
    <tr>
        <td align="center" style=min-width:50px>--password, -p</td>
        <td align="center" style=min-width:50px>指定客户端启动的账户密码</td>
    </tr>
         <td style=min-width:50px rowspan="3">共识参数</td>
    <tr>
        <td align="center" style=min-width:50px>--enable-consensus</td>
        <td align="center" style=min-width:50px>用于启动网络共识（默认关闭）</td>
    </tr>
    <tr>
        <td align="center" style=min-width:50px>--max-tx-in-block</td>
        <td align="center" style=min-width:50px>用于设置区块最大的交易数量（默认为50000）</td>
    </tr>
    <tr>
        <td style=min-width:50px rowspan="5">点对点网络参数</td>
    </tr>
    <tr>
        <td align="center" style=min-width:50px>--networkid</td>
        <td align="center" style=min-width:50px>用于指定网络编号</td>
    </tr>
    <tr>
        <td align="center" style=min-width:50px>--nodeport</td>
        <td align="center" style=min-width:50px>用于指定P2P网络端口号（默认为20338）</td>
    </tr>
    <tr>
        <td align="center" style=min-width:50px>--consensus-port</td>
        <td align="center" style=min-width:50px>用于指定共识网络端口号（默认为20339）</td>
    </tr>
    <tr>
        <td align="center" style=min-width:50px>--dual-port</td>
        <td align="center" style=min-width:50px>启动双网络（P2P网络和共识网络，默认关闭）</td>
    </tr>
    <tr>
        <td style=min-width:50px rowspan="3">RPC 参数</td>
    </tr>
    <tr>
        <td align="center" style=min-width:50px>--disable-rpc</td>
        <td align="center" style=min-width:50px>用于关闭节点的 RPC 服务（默认启动）</td>
    </tr>
    <tr>
        <td align="center" style=min-width:50px>--rpcport</td>
        <td align="center" style=min-width:50px>用指定 RPC 服务器绑定的端口号</td>
    </tr>
    <tr>
        <td style=min-width:50px rowspan="3">Restful 参数</td>
    </tr>
    <tr>
        <td align="center" style=min-width:50px>--rest</td>
        <td align="center" style=min-width:50px>用于启动节点的 Resrful 服务</td>
    </tr>
    <tr>
        <td align="center" style=min-width:50px>--restport</td>
        <td align="center" style=min-width:50px>指定节点 Resrful 服务绑定的端口号（默认值为20334）</td>
    </tr>
    <tr>
        <td style=min-width:50px rowspan="3">WebSocket 参数</td>
    </tr>
    <tr>
        <td align="center" style=min-width:50px>--ws</td>
        <td align="center" style=min-width:50px>用于启动节点的 WebSocket 服务</td>
    </tr>
    <tr>
        <td align="center" style=min-width:50px>--wsport</td>
        <td align="center" style=min-width:50px>用于指定节点 WebSocket 服务绑定的端口号（默认为20335）</td>
    </tr>
    <tr>
        <td style=min-width:50px rowspan="3">测试模式参数</td>
    </tr>
    <tr>
        <td align="center" style=min-width:50px>--testmode</td>
        <td align="center" style=min-width:50px>用于启动单节点的测试网络进行开发和调试（gasprice 为0）</td>
    </tr>
    <tr>
        <td align="center" style=min-width:50px>--testmode-gen-block-time</td>
        <td align="center" style=min-width:50px>用于设置测试模式下的出块时间（默认为 6 秒，最小为 2 秒）</td>
    </tr>
    <tr>
        <td style=min-width:50px rowspan="6">交易参数</td>
    </tr>
    <tr>
        <td align="center" style=min-width:50px>--gasprice</td>
        <td align="center" style=min-width:50px>用于设定当前节点交易池接受交易的最低 gasprice （默认为500，测试模式为 0）</td>
    </tr>
    <tr>
        <td align="center" style=min-width:50px>--gaslimit</td>
        <td align="center" style=min-width:50px>用于设定当前节点交易池接受交易的最低 gaslimit （默认为20000）</td>
    </tr>
    <tr>
        <td align="center" style=min-width:50px>--disable-tx-pool-pre-exec</td>
        <td align="center" style=min-width:50px>用于关闭交易池中的交易预执行校验（默认开启）</td>
    </tr>
    <tr>
        <td align="center" style=min-width:50px>--disable-sync-verify-tx</td>
        <td align="center" style=min-width:50px>用于关闭 RPC、Restful、WebSocket 的同步验证交易</td>
    </tr>
    <tr>
        <td align="center" style=min-width:50px>--disable-broadcast-net-tx</td>
        <td align="center" style=min-width:50px>用于关闭交易池的广播交易（默认开启）</td>
    </tr>
</table>

!> **注意**：
!> - 网络编号不同的节点之间无法直接互相连接形成共同的区块链网络
!> - 低于节点交易池接受交易的最低 `gasprice` 的交易将会被丢弃
!> - 记账节点需要使用 `--enable-consensus` 参数参与到网络共识
!> - 同一个网络所有节点的创世区块配置必须一致，否则会因为区块数据不兼容导致无法启动节点或同步区块数据
!> - 在命令行中输入的账户密码会被保存在系统的日志中，容易造成密码泄露，因此在生产环境中不建议使用 `--password`, `-p` 参数
!> - 默认情况下，共识网络复用 P2P 网络，因此不需要指定共识网络端口，在通过 `--dualport` 参数启动双网络后，则需要通过 `--consensus-port`
 参数单独设置共识网络端口号
