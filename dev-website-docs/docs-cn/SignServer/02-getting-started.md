# Getting Started

- [Operation](#operation)
  - [Configuration](#configuration)
  - [Wallet Data Directory](#wallet-data-directory)
  - [IP Address Access Control](#ip-address-access-control)
  - [IP Port Number](#ip-port-number)
  - [ABI File Directory](#abi-file-directory)
  - [Logging](#logging)
- [Importing Pre-existing Wallet Data](#importing-existing-wallet-data)

## Operation
To quickly get the service running with all the default options, simply run the command
```
./sigsvr
```
The service will now be accessible at:
```
http://localhost:20000/cli
```

## Configuration
The service comes preconfigured with default options to get you started, however you will want to adjust these as appropriate for your specific project. All configurations are made via option parameters, for example:

```
./sigsvr --walletdir ./data/wallets --abi ./data/abi
```
Any combination of the configuration option is detailed below can be used.

### Wallet Data Directory
The location where the local wallet data will be stored by the service. The default location is `$GOPATH/src/github.com/ontio/ontology/tools/wallet_data`. If you would like to change this location, please use the `walletdir` parameter.

For example:
```
./sigsvr --walletdir ./data/wallets
```

### IP Address Access Control
The IP address which you would like the service to be accessible from. By default, the it is set to only be accessed by your local machine, set by the value `127.0.0.1`. If you would like to have this service be accessible externally, please use the `cliaddress` parameter.

For example:
```
./sigsvr --cliaddress 0.0.0.0
```

### IP Port Number
The IP port number at which you would like your service to be avaliable at. By default the port number is set to `20000`. If you would like to change this location, please use the `cliport` parameter.

For example:
```
./sigsvr --cliport 1337
```

### ABI File Directory
The location where the local ABI files used for Ontology Native Smart Contract invocations will be located. By default, the current assortment of standard ABI files are provided for you, and located at `$GOPATH/src/github.com/ontio/ontology/tools/abi`. If you would like to change this location, please use the `abi` parameter.

For example:
```
./sigsvr --abi ./data/abi
```

### Logging
Different levels of service logging available. By default, the logging level is set to Info (2). However there are seven different levels of logging available.

0. Trace
1. Debug
2. Info (default)
3. Warn
4. Error
5. Fatal
6. Max Level

For example:
```
./sigsvr --loglevel 0
```

## Importing Existing Wallet Data
You may already have a set of wallets generated offline, and would like to import them to the service. In order to do this, you can use the import command along with the `wallet` option to point to an existing `.dat` file to import wallets from. This command is separate from the service configuration options, as this will simply import wallets to the service, and not actually run the service.

For example:
```
./sigsvr import --wallet ./wallet_2018-10-31-23-59-59.dat
```

This can be useful to import wallets from an export using the services export function.
