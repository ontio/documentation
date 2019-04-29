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
  <h1 align="center">Ontology Developer Guide</h1>
  <div ><a href="https://ont.io/">Ontology</a> is a new generation of high-performance public blockchains. The infrastructure is scalable, stable, and allows low-level customization for different business requirements. After the Ontology MainNet release, we have welcomed many new developers to the Ontology technical community and launched our <a href="https://developer.ont.io/">Developer Center </a>.</div>
    <div >
      <div class="content-container" style="background-color: #f4f4f4;padding: 1.2rem 1.2rem 2.4rem;margin: 2.4rem 0;" >
          <div class="row content-row">
            <div class="col-sm-4 col-xs-12">
                <p class="content-title" style="border-bottom: 1px solid #979797;">Ontology</p>
                  <div>
                      <div>
                          <a href="#/docs-en/DeveloperGuide/introduction">Introduction</a>
                      </div>
                  </div>
                  <div>
                      <div>
                          <a href="#/docs-en/DeveloperGuide/02-VBFT-introduction">VBFT Consensus</a>
                      </div>
                  </div>
                  <div>
                      <div>
                          <a href="#/docs-en/DeveloperGuide/smartcontract/00-introduction-sc">Smart Contract</a>
                      </div>
                  </div>
                  <div>
                      <div>
                          <a href="#/docs-en/DeveloperGuide/introduction">View all</a>
                      </div>
                  </div></br>
            </div>
            <div class="col-sm-4 col-xs-12">
                <p class="content-title" style="border-bottom: 1px solid #979797;">Ontology Client</p>
                  <div>
                      <div>
                          <a href="#/docs-en/OntologyCli/00-overview">Overview</a>
                      </div>
                  </div>
                  <div>
                      <div>
                          <a href="#/docs-en/OntologyCli/00-overview">View all</a>
                      </div>
                  </div>
            </div>
            <div class="col-sm-4 col-xs-12">
                <p class="content-title" style="border-bottom: 1px solid #979797;">API Reference</p>
                  <div>
                      <div>
                          <a href="#/docs-en/API/00-overview">Overview</a>
                      </div>
                  </div>
                  <div>
                      <div>
                          <a href="#/docs-en/API/00-overview">View all</a>
                      </div>
                  </div>
            </div>
            <div class="col-sm-4 col-xs-12">
                <p class="content-title" style="border-bottom: 1px solid #979797;">DApp Development Guide</p>
                  <div>
                      <div>
                          <a href="#/docs-en/QuickGuide/00-dapp_development">DApp Development</a>
                      </div>
                  </div>
                  <div>
                      <div>
                          <a href="#/docs-en/QuickGuide/06-dapi-useage">DApi Usage</a>
                      </div>
                  </div>
                  <div>
                      <div>
                          <a href="#/docs-en/QuickGuide/00-dapp_development">View all</a>
                      </div>
                  </div>
            </div>
            <div class="col-sm-4 col-xs-12">
                <p class="content-title" style="border-bottom: 1px solid #979797;">Smart Contract Guide</p>
                  <div>
                      <div>
                          <a href="#/docs-en/smartcontract/01-started">Smart Contract Guide</a>
                      </div>
                  </div>
                  <div>
                      <div>
                          <a href="#/docs-en/smartcontract/01-started">View all</a>
                      </div>
                  </div>
            </div>
          </div>
      </div>
      <div class="content-container" style="background-color: #f4f4f4;padding: 1.2rem 1.2rem 2.4rem;margin: 2.4rem 0;">
          <div class="row content-row">
            <div class="col-sm-4 col-xs-12">
                <p class="content-title"  style="border-bottom: 1px solid #979797;">DAPP Integration Guide</p>
                  <div>
                      <div>
                          <a href="#/docs-en/dApp-Integration/00-dapp_integration">Overview</a>
                      </div>
                  </div>
                  <div>
                      <div>
                          <a href="#/docs-en/dApp-Integration/00-dapp_integration">View all</a>
                      </div>
                  </div><br/>
            </div>
            <div class="col-sm-4 col-xs-12">
                <p class="content-title"  style="border-bottom: 1px solid #979797;">Wallet Integration Guide</p>
                  <div>
                      <div>
                          <a href="#/docs-en/Wallet-Integration/00-wallet_integration">Overview</a>
                      </div>
                  </div>
                  <div>
                      <div>
                          <a href="#/docs-en/Wallet-Integration/00-wallet_integration">View all</a>
                      </div>
                  </div>
            </div>
            <div class="col-sm-4 col-xs-12">
                <p class="content-title" style="border-bottom: 1px solid #979797;">Exchange Docking</p>
                  <div>
                      <div>
                          <a href="#/docs-en/exchange-API/Ontology+Exchange+Docking+Document">Overview</a>
                      </div>
                  </div>
                  <div>
                      <div>
                          <a href="#/docs-en/exchange-API/Ontology+Exchange+Docking+Document">View all</a>
                      </div>
                  </div>
            </div>
            <div class="col-sm-4 col-xs-12">
                <p class="content-title" style="border-bottom: 1px solid #979797;">DAPP Store Integration Guide</p>
                  <div>
                      <div>
                          <a href="#/docs-en/dapps/overview">Overview</a>
                      </div>
                  </div>
            </div>
          </div>
      </div>
      <div class="content-container" style="background-color: #f4f4f4;padding: 1.2rem 1.2rem 2.4rem;margin: 2.4rem 0;">
          <div class="row content-row">
            <div class="col-sm-4 col-xs-12">
                <p class="content-title"  style="border-bottom: 1px solid #979797;">SmartX</p>
                  <div>
                      <div>
                          <a href="#/docs-en/SmartX/00-overview">Overview</a>
                      </div>
                  </div>
                  <div>
                      <div>
                          <a href="#/docs-en/SmartX/01-getting-started">Getting Started</a>
                      </div>
                  </div>
            </div>
            <div class="col-sm-4 col-xs-12">
                <p class="content-title"  style="border-bottom: 1px solid #979797;">Cyano</p>
                  <div>
                      <div>
                          <a href="#/docs-en/Cyano/00-overview">Overview</a>
                      </div>
                  </div>
                  <div>
                      <div>
                          <a href="#/docs-en/Cyano/00-overview">View all</a>
                      </div>
                  </div>
            </div>
            <div class="col-sm-4 col-xs-12">
                <p class="content-title"  style="border-bottom: 1px solid #979797;">Punica</p>
                  <div>
                      <div>
                          <a href="#/docs-en/Punica/punica">Overview</a>
                      </div>
                  </div>
                  <div>
                      <div>
                          <a href="#/docs-en/Punica/punica-cli">Punica Cli</a>
                      </div>
                  </div>
                  <div>
                      <div>
                          <a href="#/docs-en/Punica/punica-box">Punica Box</a>
                      </div>
                  </div>
                  <div>
                      <div>
                          <a href="#/docs-en/Punica/punica">View all</a>
                      </div>
                  </div></br>
            </div>
            <div class="col-sm-4 col-xs-12">
                <p class="content-title"  style="border-bottom: 1px solid #979797;">SDKs</p>
                  <div>
                      <div>
                          <a href="#/docs-en/SDKs/00-overview">Overview</a>
                      </div>
                  </div>
                  <div>
                      <div>
                          <a href="#/docs-en/SDKs/00-overview">View all</a>
                      </div>
                  </div>
            </div>
            <div class="col-sm-4 col-xs-12">
                <p class="content-title"  style="border-bottom: 1px solid #979797;">Explorer API</p>
                  <div>
                      <div>
                          <a href="#/docs-en/explorer/overview">Overview</a>
                      </div>
                  </div>
                  <div>
                      <div>
                          <a href="#/docs-en/explorer/blocks">Blocks</a>
                      </div>
                  </div>
                  <div>
                      <div>
                          <a href="#/docs-en/explorer/accounts">Accounts</a>
                      </div>
                  </div>
                  <div>
                      <div>
                          <a href="#/docs-en/explorer/overview">View all</a>
                      </div>
                  </div>
            </div>
            <div class="col-sm-4 col-xs-12">
                <p class="content-title"  style="border-bottom: 1px solid #979797;">Sign Server</p>
                  <div>
                      <div>
                          <a href="#/docs-en/SignServer/00-overview">Overview</a>
                      </div>
                  </div>
                  <div>
                      <div>
                          <a href="#/docs-en/SignServer/01-installation">Installation</a>
                      </div>
                  </div>
                  <div>
                      <div>
                          <a href="#/docs-en/SignServer/02-getting-started">Getting Started</a>
                      </div>
                  </div>
                  <div>
                      <div>
                          <a href="#/docs-en/SignServer/00-overview">View all</a>
                      </div>
                  </div>
            </div>
          </div>
      </div>
    </div>
  </body>
</html>
