# 安装
签名服务是ontology核心库的一部分 [core Ontology repository](https://github.com/ontio/ontology). 下载Ontology核心仓库代码，安装所有的依赖在`$GOPATH/src/github.com/ontio`路径下。

```
git clone https://github.com/ontio/ontology.git
```
或
```
go get github.com/ontio/ontology
```

切换到本地仓库目录
```
$GOPATH/src/github.com/ontio
```

安装项目依赖
```
glide install
```

用源码构建签名机服务
```
make tools
```

切换到tools目录下
```
cd tools
```
