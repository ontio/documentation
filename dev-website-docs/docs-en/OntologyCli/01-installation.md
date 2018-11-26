# Installation
The Ontology CLI is a part of the [core Ontology repository](https://github.com/ontio/ontology). Download the core Ontology protocol repository and install all dependencies in the proper directory `$GOPATH/src/github.com/ontio`

```
git clone https://github.com/ontio/ontology.git
```
or
```
go get github.com/ontio/ontology
```

Navigate to the local repository
```
cd $GOPATH/src/github.com/ontio
```

Install project dependencies
```
glide install
```

Build from source code
```
make all
```
