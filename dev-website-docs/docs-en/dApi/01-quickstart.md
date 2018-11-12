## How to use 
ontology-dapi can be used as CommonJS/ES6 module or directly referencing in web page html. 

### Install CommonJS/ES module
```
npm install ontology-dapi
```

### Import CommonJS
```
var client = require('ontology-dapi').client;
```

### Import ES6 module
```
import { client } from 'ontology-dapi';
```

### Web require
The browser.js file under the '/lib' folder needs to be referenced from the page:
```
<script src="./lib/browser.js"></script>
```

The use of the code is required under the global namespace of Ont.
```
var client = dApi.client;
```

### Initialisation
dApp needs to register itself as a client with the ontology-dapi library to enable the communication.

```
import { client } from 'ontology-dapi';

client.registerClient({});
```

## Usage

Examples of usage can be found in [EXAMPLES.md](EXAMPLES.md) or in a [demo app](https://github.com/OntologyCommunityDevelopers/ontology-dapi-demo)
