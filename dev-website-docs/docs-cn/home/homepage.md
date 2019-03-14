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
    <div >
      <div class="content-container" >
          <div class="row content-row">
            <div class="col-sm-4 col-xs-12">
                <p class="content-title">认识本体</p>
                  <div>
                      <div>
                          <a href="#/docs-cn/introduction/01-introduction">介绍</a>
                      </div>
                  </div>
            </div>
            <div class="col-sm-4 col-xs-12">
                <p class="content-title">本体客户端</p>
                  <div>
                      <div>
                          <a href="#/docs-cn/introduction/01-introduction">概述</a>
                      </div>
                  </div>
            </div>
            <div class="col-sm-4 col-xs-12">
                <p class="content-title">HTTP API</p>
                  <div>
                      <div>
                          <a href="#/docs-cn/ontology-cli/04-interface-specification">概述</a>
                      </div>
                  </div>
            </div>
            <div class="col-sm-4 col-xs-12">
                <p class="content-title">DApp开发指南</p>
                  <div>
                      <div>
                          <a href="#/docs-cn/QuickGuide/00-dapp_development">DApp 开发</a>
                      </div>
                  </div>
            </div>
            <div class="col-sm-4 col-xs-12">
                <p class="content-title">智能合约指南</p>
                  <div>
                      <div>
                          <a href="#/docs-cn/dApp-Integration/00-dapp_integration">智能合约指南</a>
                      </div>
                  </div>
            </div>
          </div>
      </div>
    </div>
  </body>
</html>
