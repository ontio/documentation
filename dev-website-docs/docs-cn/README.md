<!DOCTYPE html>
<html>
  <head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width,initial-scale=1.0">
    <title>docs_homepage</title>
<link href="https://cdn.bootcss.com/twitter-bootstrap/4.2.1/css/bootstrap.min.css" rel="stylesheet">

  </head>
  <style scoped >
  h1, h2 {
    font-weight: normal;
  }
  ul {
    /* list-style-type: none; */
    padding: 0;
    text-align: left;
  }
  li {
    display: block;
    margin: 0;

  }
  ul a {
      font-size:22px;
  font-family:SourceSansPro-Regular;
  font-weight:400;
  color:rgba(110,111,112,1);
  position: relative;
  padding-left: 10px;
  }

  li a::before {
    content: '';
    width:4px;
    height:4px;
    border-radius: 50%;
    background:#000000;
    position: absolute;
      /* display: block; */
      left: 0;
      top: 15px;
  }

  .content-title {
    font-size:22px;
    font-family:SourceSansPro-Bold;
    font-weight:bold;
    color:rgba(0,0,0,1);
    padding-bottom: 10px;
    border-bottom: 1px solid #979797;
    text-align:left;
    margin-bottom:10px;
  }

  .content-container {
    margin:40px 120px;
    padding:40px 30px;
    background:rgba(245,247,247,1);
  }

  .content-container .content-row:first-child {
    margin-bottom: 40px;
  }

  @media screen and (max-width:576px) {
     .content-container {
        margin:40px 20px;
    }
  }

  </style>
  <body>
  <h1 align="center">本体开发者中心</h1>
  <div >欢迎来到本体开发者中心。借助完善的开发者文档，你可以快速了解本体的生态、技术和工具。</div>
    <div ></br></br>
      <h4>关于本体</h4>
      <div class="content-container" style="background-color: #f4f4f4;padding: 1.2rem 1.2rem 2.4rem;margin: 2.4rem 0;" >
          <div class="row content-row">
            <div class="col-sm-4 col-xs-12">
                <p class="content-title" style="border-bottom: 1px solid #979797;">认识本体</p>
                  <div>
                      <div>
                          <a href="#/docs-cn/introduction/01-introduction">介绍</a>
                      </div>
                  </div>
                  <div>
                      <div>
                          <a href="#/docs-cn/introduction/02-VBFT">VBFT 共识</a>
                      </div>
                  </div>
                  <div>
                      <div>
                          <a href="#/docs-cn/introduction/03-smart-contract">智能合约</a>
                      </div>
                  </div>
                  <div>
                      <div>
                          <a href="#/docs-cn/introduction/01-introduction">查看全部</a>
                      </div>
                  </div></br>
            </div>
            <div class="col-sm-4 col-xs-12">
                <p class="content-title" style="border-bottom: 1px solid #979797;">本体客户端</p>
                  <div>
                      <div>
                          <a href="#/docs-cn/ontology-cli/00-overview">概述</a>
                      </div>
                  </div>
                  <div>
                      <div>
                          <a href="#/docs-cn/ontology-cli/00-overview">查看全部</a>
                      </div>
                  </div>
            </div>
            <div class="col-sm-4 col-xs-12">
                <p class="content-title" style="border-bottom: 1px solid #979797;">HTTP API</p>
                  <div>
                      <div>
                          <a href="#/docs-cn/ontology-cli/04-interface-specification">概述</a>
                      </div>
                  </div>
                  <div>
                      <div>
                          <a href="#/docs-cn/ontology-cli/04-interface-specification">查看全部</a>
                      </div>
                  </div>
            </div>
            <div class="col-sm-4 col-xs-12">
                <p class="content-title" style="border-bottom: 1px solid #979797;">DApp 开发指南</p>
                  <div>
                      <div>
                          <a href="#/docs-cn/QuickGuide/00-dapp_development">DApp 开发</a>
                      </div>
                  </div>
                  <div>
                      <div>
                          <a href="#/docs-cn/QuickGuide/00-dapp_development?id=%E4%BD%BF%E7%94%A8-dapi">DApi 使用</a>
                      </div>
                  </div>
                  <div>
                      <div>
                          <a href="#/docs-cn/QuickGuide/00-dapp_development">查看全部</a>
                      </div>
                  </div>
            </div>
            <div class="col-sm-4 col-xs-12">
                <p class="content-title" style="border-bottom: 1px solid #979797;">智能合约指南</p>
                  <div>
                      <div>
                          <a href="#/docs-cn/smartcontract/01-started">智能合约指南</a>
                      </div>
                  </div>
                  <div>
                      <div>
                          <a href="#/docs-cn/smartcontract/01-started">查看全部</a>
                      </div>
                  </div>
            </div>
            <div class="col-sm-4 col-xs-12">
                <p class="content-title" style="border-bottom: 1px solid #979797;">多链开发指南</p>
                  <div>
                      <div>
                          <a href="#/docs-cn/multichain/overview">多链开发指南</a>
                      </div>
                  </div>
                  <div>
                      <div>
                          <a href="#/docs-cn/multichain/getting-started">开始使用</a>
                      </div>
                  </div>
                  <div>
                      <div>
                          <a href="#/docs-cn/multichain/tutorials">跨链课堂</a>
                      </div>
                  </div> 
                  <div>
                      <div>
                          <a href="#/docs-cn/multichain/overview">查看全部</a>
                      </div>
                  </div>
            </div>
          </div>
      </div>
      <h4>对接指南</h4>
      <div class="content-container" style="background-color: #f4f4f4;padding: 1.2rem 1.2rem 2.4rem;margin: 2.4rem 0;">
          <div class="row content-row">
            <div class="col-sm-4 col-xs-12">
                <p class="content-title"  style="border-bottom: 1px solid #979797;">DAPP 对接指南</p>
                  <div>
                      <div>
                          <a href="#/docs-cn/dApp-Integration/00-dapp_integration">概述</a>
                      </div>
                  </div>
                  <div>
                      <div>
                          <a href="#/docs-cn/dApp-Integration/00-dapp_integration">查看全部</a>
                      </div>
                  </div></br>
            </div>
            <div class="col-sm-4 col-xs-12">
                <p class="content-title"  style="border-bottom: 1px solid #979797;">钱包对接指南</p>
                  <div>
                      <div>
                          <a href="#/docs-cn/Wallet-Integration/00-wallet_integration">概述</a>
                      </div>
                  </div>
                  <div>
                      <div>
                          <a href="#/docs-cn/Wallet-Integration/00-wallet_integration">查看全部</a>
                      </div>
                  </div>
            </div>
            <div class="col-sm-4 col-xs-12">
                <p class="content-title" style="border-bottom: 1px solid #979797;">交易所对接指南</p>
                  <div>
                      <div>
                          <a href="#/docs-cn/exchange-API/Ontology-%E4%BA%A4%E6%98%93%E6%89%80%E5%AF%B9%E6%8E%A5%E6%96%87%E6%A1%A3">概述</a>
                      </div>
                  </div>
                  <div>
                      <div>
                          <a href="#/docs-cn/exchange-API/Ontology-%E4%BA%A4%E6%98%93%E6%89%80%E5%AF%B9%E6%8E%A5%E6%96%87%E6%A1%A3">查看全部</a>
                      </div>
                  </div>
            </div>
            <div class="col-sm-4 col-xs-12">
                <p class="content-title" style="border-bottom: 1px solid #979797;">DAPP Store 对接指南</p>
                  <div>
                      <div>
                          <a href="#/docs-cn/dapps/overview">概述</a>
                      </div>
                  </div>
            </div>
            <div class="col-sm-4 col-xs-12">
                <p class="content-title" style="border-bottom: 1px solid #979797;">常见问题</p >
                <div>
                    <div>
                        <a href="#/docs-cn/faq/overview">概述</a>
                    </div>
                </div>
            </div>
          </div>
      </div>
      <h4>工具</h4>
      <div class="content-container" style="background-color: #f4f4f4;padding: 1.2rem 1.2rem 2.4rem;margin: 2.4rem 0;">
          <div class="row content-row">
            <div class="col-sm-4 col-xs-12">
                <p class="content-title"  style="border-bottom: 1px solid #979797;">SmartX</p>
                  <div>
                      <div>
                          <a href="#/docs-cn/SmartX/overview">概述</a>
                      </div>
                  </div>
                  <div>
                      <div>
                          <a href="#/docs-cn/SmartX/overview">查看全部</a>
                      </div>
                  </div>
            </div>
            <div class="col-sm-4 col-xs-12">
                <p class="content-title"  style="border-bottom: 1px solid #979797;">Cyano</p>
                  <div>
                      <div>
                          <a href="#/docs-cn/cyano/00-overview">概述</a>
                      </div>
                  </div>
                  <div>
                      <div>
                          <a href="#/docs-cn/cyano/00-overview">查看全部</a>
                      </div>
                  </div>
            </div>
            <div class="col-sm-4 col-xs-12">
                <p class="content-title"  style="border-bottom: 1px solid #979797;">Punica</p>
                  <div>
                      <div>
                          <a href="#/docs-cn/Punica/punica">概述</a>
                      </div>
                  </div>
                  <div>
                      <div>
                          <a href="#/docs-cn/Punica/punica-cli">Punica Cli</a>
                      </div>
                  </div>
                  <div>
                      <div>
                          <a href="#/docs-cn/Punica/punica-box">Punica Box</a>
                      </div>
                  </div>
                  <div>
                      <div>
                          <a href="#/docs-cn/Punica/punica">查看全部</a>
                      </div>
                  </div></br>
            </div>
            <div class="col-sm-4 col-xs-12">
                <p class="content-title"  style="border-bottom: 1px solid #979797;">SDKs</p>
                  <div>
                      <div>
                          <a href="#/docs-cn/SDKs/00-overview">概述</a>
                      </div>
                  </div>
                  <div>
                      <div>
                          <a href="#/docs-cn/SDKs/00-overview">查看全部</a>
                      </div>
                  </div>
            </div>
            <div class="col-sm-4 col-xs-12">
                <p class="content-title"  style="border-bottom: 1px solid #979797;">浏览器 API</p>
                  <div>
                      <div>
                          <a href="#/docs-cn/explorer/overview">概述</a>
                      </div>
                  </div>
                  <div>
                      <div>
                          <a href="#/docs-cn/explorer/blocks">区块</a>
                      </div>
                  </div>
                  <div>
                      <div>
                          <a href="#/docs-cn/explorer/accounts">账户</a>
                      </div>
                  </div>
                  <div>
                      <div>
                          <a href="#/docs-cn/explorer/overview">查看全部</a>
                      </div>
                  </div>
            </div>
            <div class="col-sm-4 col-xs-12">
                <p class="content-title"  style="border-bottom: 1px solid #979797;">签名机</p>
                  <div>
                      <div>
                          <a href="#/docs-cn/sigsvr/00-overview">概述</a>
                      </div>
                  </div>
                  <div>
                      <div>
                          <a href="#/docs-cn/sigsvr/01-install">安装</a>
                      </div>
                  </div>
                  <div>
                      <div>
                          <a href="#/docs-cn/sigsvr/02-getting-started">快速入门</a>
                      </div>
                  </div>
                  <div>
                      <div>
                          <a href="#/docs-cn/sigsvr/00-overview">查看全部</a>
                      </div>
                  </div>
            </div>
          </div>
      </div>
    </div>
  </body>
</html>
