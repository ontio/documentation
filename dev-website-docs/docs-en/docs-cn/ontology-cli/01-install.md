
### 下载安装包

基于 Go 语言，我们提供了通用的本体客户端安装程序，你可以通过下列两种方式快速获取：
- 点击 [这里](https://github.com/ontio/ontology/releases) 下载本体客户端安装程序。
- 通过 `curl` 命令获取最新的客户端。

  ```shell
  curl https://dev.ont.io/ontology_install | sh
  ```

### 使用源码编译

此外，你也可以从源码编译本体客户端。

1. 获取源码：

   ```shell
   go get github.com/ontio/ontology
   ```

2. 使用包管理工具 `glide` 获取依赖：

   ```shell
   cd $GOPATH/src/github.com/ontio/ontology
   glide install
   ```

3. 编译源码：

   ```shell
   make all
   ```
   源码成功编译后会生成两个可执行程序：

   - ontology：本体客户端。
   - sigsvr：签名服务器。

