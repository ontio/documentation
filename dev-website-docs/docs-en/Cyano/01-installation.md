
### Download 

Plugin is currently distributed in Chrome web store at https://chrome.google.com/webstore/detail/ontology-web-wallet/dkdedlpgdmmkkfjabffeganieamfklkm or install by yourself from [here](https://github.com/OntologyCommunityDevelopers/cyano-wallet/releases)

cyano mobile source code is [cyano-android](https://github.com/ontio-cyano/cyano-android), [cyano-ios](https://github.com/ontio-cyano/cyano-ios)

### Manual build

To build manually see the steps below. Or you can download pre-build plugin for Chrome from Release page.

### Required Tools and Dependencies

* Node
* Yarn (https://yarnpkg.com/lang/en/docs/install/)

### Developing and Running

Execute these commands in the project's root directory:

Setup:

#### Install yarn
For faster building process and development experience install Yarn

```
npm install --global yarn
```

#### Download
```
git clone 'https://github.com/ontio/cyano-wallet.git'
```

#### Start the extension in watch mode
This will watch for file changes and build the distribution every time something changes. If the extension is loaded as Unpacked Extension in Chrome, one could reload the extension to get the newest build.

````
yarn watch
````

#### Build extension
This will build the extension for installation into browsers. 

````
yarn build
````
