
签名机是本体核心库的组成部分，你可以点击[这里](https://github.com/ontio/ontology)访问项目。你可以点击 [这里](https://github.com/ontio/ontology/releases) 下载签名机的可执行程序。此外，你也可以从源码编译本体客户端。

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
   make tools
   ```

4. 切换到 `tools` 目录，使用编译完成的签名机 `sigsvr`。

    ```shell
    cd tools
    ```
