
### 下载 

Chrome web store 下载 https://chrome.google.com/webstore/detail/ontology-web-wallet/dkdedlpgdmmkkfjabffeganieamfklkm . 


### 手动创建

To build manually see the steps below. Or you can download pre-build plugin for Chrome from Release page.

### 依赖工具

* Node
* Yarn (https://yarnpkg.com/lang/en/docs/install/)

### Developing and Running

Execute these commands in the project's root directory:

Setup:

#### 安装 yarn
For faster building process and development experience install Yarn

```
npm install --global yarn
```

#### 下载
```
git clone 'https://github.com/backslash47/ontology-plugin-wallet.git'
```

#### Start the extension in watch mode
This will watch for file changes and build the distribution every time something changes. If the extension is loaded as Unpacked Extension in Chrome, one could reload the extension to get the newest build.

````
yarn watch
````

#### Build
This will build the extension for installation into browsers. 

````
yarn build
````