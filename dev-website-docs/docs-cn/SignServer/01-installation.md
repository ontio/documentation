# Installation
The signature service is a part of the [core Ontology repository](https://github.com/ontio/ontology). Download the core Ontology protocol repository and install all dependencies in the proper directory `$GOPATH/src/github.com/ontio`

```
git clone https://github.com/ontio/ontology.git
```
or
```
go get github.com/ontio/ontology
```

Navigate to the local repository
```
$GOPATH/src/github.com/ontio
```

Install project dependencies
```
glide install
```

Build SigSvr from source code
```
make tools
```

Navigate into the tools directory
```
cd tools
```
