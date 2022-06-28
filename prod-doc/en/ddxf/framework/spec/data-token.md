# Data token specification

在执行交易时，RP 为该资源生成一个 DToken（以智能合约的形式实现），包含对该资源 [`ONT ID`](../../../ontid/framework/README.md) 的引用、该 DToken 持有者的的 ONT ID 以及有效期等。DToken 可以是同质化 Token，例如，对房产的众筹分割。也可以是非同质化 Token，如一对一的数据交割。

DToken 的标准格式如下（在实际数据和资源使用过程中定义的DToken，根据需要添加其它属性），

```
type DToken struct {
  Name //该 DToken 的名字
  Symbol //该 DToken 的符号
  Amount //该 DToken 的数量
  ResourceID //对应资源的引用，该资源的 ONT ID
  RealContractDigest //双方经由 ONT Sign 签订的电子合同存证信息
  Expires //资源权力的有效期
  Exchange //该 DToken 可以流转的次数，设为 0 即表示不可流转
  Status //该 DToken 的使用状态，表示是否可使用。也可使用计数器方式 
}
```

DToken 的初始持有者即为 RC，随后该 DToken 可被(签发交易)流转给其他人。RP 在 DToken 时可以生成设定其流转次数限制，每次流转时该次数递减，流转次数为 0 即表示不可流转。 

DToken 的使用状态初始置于 “未使用” 状态（即使剩余流转次数为 0）。当持有者要从 RP 处获取 链外资源权限时，需要先将 DToken 的状态置为 “使用”。处于该状态的 DToken 不能够再进行流转转移。当资源可以被多次 “使用” 时，可以将使用状态设置成计数方式，初始值为可允许的次数。当持有者要从 RP 处获取链外资源权限时，需要先将 DToken 的使用状态计数减一。计数值不能小于零，某 一计数值下的 DToken 只能使用一次。 

RP 接收到链外资源获取请求后，为了防止作恶，RP 将验证访问者 RC 是否为 DToken 的当前 持有者，并检查 DToken 的使用状态是否可用等，然后再向其提供对应资源的权利。例如，可以使用 DToken 和 RC 签名形成 JWT 进行访问数据。

