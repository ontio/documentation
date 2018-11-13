# 贡献

If you happen to find any issues, or have any cool ideas for the next amazing feature for Solo chain, please head over to the [Github](https://github.com/punicasuite/solo-chain) repo, and help us make Solo chain even better.

如果您碰巧发现任何问题，或者对 Solo Chain 的后续功能有任何想法，请到 [Github 项目库](https://github.com/punicasuite/solo-chain) 中提出，这将帮助我们创造一个更好的 Solo Chain。

## 开发步骤

如果要以开发者模式下运行 Solo Chain，你可以：

- 从GitGub获取完整的源码 `git clone git@github.com：punicasuite/solo-chain.git`
- 安装依赖项 `yarn install`
- 编译安装程序 `yarn dev`

这将安装并编译所有必需的依赖项和源代码，并启在 `localhost：9080` 启动服务。当你对 `./src` 文件夹中的代码库进行更改时，应用程序将以热重载的方式进行刷新。

If you have any issues getting setup, please reach out in the Github issues, or directly on Discord.

如果你在安装时遇到任何问题，都可以在 Github 的 issue 中提出，或者直接在 Discord 上联系。

## 贡献指南

Please open a pull request with signed-off commits. We appreciate your help! You can also send your codes as emails to the developer mailing list. You're welcomed to join the Ontology mailing list or developer forum.

Please provide detailed submission information when you want to contribute code for this project. The format is as follows:

Header line: explain the commit in one line (use the imperative).

Body of commit message is a few lines of text, explaining things in more detail, possibly giving some background about the issue being fixed, etc.

The body of the commit message can be several paragraphs, and please do proper word-wrap and keep columns shorter than about 74 characters or so. That way "git log" will show things nicely even when it's indented.

Make sure you explain your solution and why you're doing what you're doing, as opposed to describing what you're doing. Reviewers and your future self can read the patch, but might not understand why a particular solution was implemented.

Reported-by: whoever-reported-it Signed-off-by: Your Name youremail@yourhost.com
