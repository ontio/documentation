<h1 align="center">Python SDK For Ontology</h1>

<p align="center" class="version">Version 0.1.3</p>

<!-- TOC -->

- [Introduction](#introduction)
- [Preparations](#preparations)
- [Interface](#interface)
    - [Network](#network)
    - [Wallet](#wallet)
    - [Account](#account)
    - [Identity](#identity)
    - [AccountManager](#accountmanager)
    - [IdentityManager](#identitymanager)
    - [Asset](#asset)
    - [ABI](#abi)
    - [OEP4](#oep4)
    - [Utils](#utils)
- [Contribution](#contribution)
- [Naming](#naming)
    - [Overview](#overview)
    - [Names to Avoid](#names-to-avoid)
    - [Naming Convention](#naming-convention)
    - [Guidelines derived from Guido's Recommendations](#guidelines-derived-from-guidos-recommendations)
- [Site](#site)
- [License](#license)

<!-- /TOC -->


## Introduction

The Ontology official Python SDK is a comprehensive SDK which is based on `Python3.7`. Currently, it supports local wallet management, digital identity management, digital asset management, deployment and invoke for smart contract, the calling of OEP4, and communication with the Ontology blockchain. The future will also support more functions and applications.

## Preparations

Installation requires a Python 3.6 or later environment.

```bash
pip install ontology-python-sdk
```

## Interface

Read more in the [ontology-python-sdk API document](https://apidoc.ont.io/pythonsdk/).

### Network

This is an API set that allows you to interact with an Ontology nodes.

|       | Main Function                         |
| :---: | :------------------------------------ |
| 1     | get_version()                         |
| 2     | get_balance()                         |
| 3     | get_allowance()                       |
| 4     | get_gas_price()                       |
| 5     | get_network_id()                      |
| 6     | get_node_count()                      |
| 7     | get_block_count()                     |
| 8     | get_block_by_hash()                   |
| 9     | get_block_by_height()                 |
| 10    | get_current_block_hash()              |
| 11    | get_block_hash_by_height()            |
| 12    | get_storage()                         |
| 13    | get_smart_contract()                  |
| 14    | get_smart_contract_event_by_tx_hash() |
| 15    | get_smart_contract_event_by_height()  |

### Wallet

This is an API set that allows you to handle with wallet account in the form of `AccountData`.

|       | Main Function    |
| :---: | :--------------- |
| 1     | add_account()    |
| 2     | remove_account() |

**Note**: This package has **NOT** been audited and might potentially be unsafe. Take precautions to clear memory properly, store the private keys safely, and test transaction receiving and sending functionality properly before using in production!

### Account

This is an API set that allows you to generate Ontology accounts and sign transactions and data.

|       | Main Function                      |
| :---: | :--------------------------------- |
| 1     | export_wif()                       |
| 2     | get_signature_scheme()             |
| 3     | serialize_public_key()             |
| 4     | serialize_private_key()            |
| 5     | get_public_key_hex()               |
| 6     | get_public_key_bytes()             |
| 7     | get_private_key_from_wif()         |
| 8     | get_gcm_decoded_private_key()      |
| 9     | export_gcm_encrypted_private_key() |
| 10    | get_address_hex()                  |
| 11    | get_address_hex_reverse()          |
| 12    | get_address_base58()               |
| 13    | generate_signature()               |

**Note**: This package has **NOT** been audited and might potentially be unsafe. Take precautions to clear memory properly, store the private keys safely, and test transaction receiving and sending functionality properly before using in production!

### Identity

This is an API set that allows you to generate **Ontology Digital Identity.**

|       | Main Function                        |
| :---: | :----------------------------------- |
| 1     | parse_ddo()                          |
| 2     | send_get_ddo()                       |
| 3     | new_get_ddo_transaction()            |
| 4     | new_add_recovery_transaction()       |
| 5     | new_add_attribute_transaction()      |
| 6     | new_add_public_key_transaction()     |
| 7     | new_remove_public_key_transaction()  |
| 8     | new_registry_ont_id_transaction()    |
| 9     | new_remove_attribute_transaction()   |
| 10    | send_add_recovery_transaction()      |
| 11    | send_add_attribute_transaction()     |
| 12    | send_add_public_key_transaction()    |
| 13    | send_registry_ont_id_transaction()   |
| 14    | send_remove_public_key_transaction() |
| 15    | send_remove_attribute_transaction()  |
| 16    | send_add_public_key_by_recovery()    |
| 17    | sign_transaction()                   |
| 18    | add_sign_transaction()               |
| 19    | add_multi_sign_transaction()         |
| 20    | get_merkle_proof()                   |
| 21    | get_raw_transaction()                |
| 22    | send_raw_transaction()               |
| 23    | send_raw_transaction_pre_exec()      |

**Note**: This package has **NOT** been audited and might potentially be unsafe. Take precautions to clear memory properly, store the private keys safely, and test transaction receiving and sending functionality properly before using in production!

### AccountManager

This is an API set that allows you to manage your multiple account in an wallet file.

|       | Main Function                     |
| :---: | :-------------------------------- |
| 1     | import_account()                  |
| 2     | create_account()                  |
| 3     | create_account_from_private_key() |
| 4     | get_account()                     |
| 5     | get_accounts()                    |
| 6     | get_default_account()             |
| 7     | get_default_account_address()     |
| 8     | set_default_account_by_index()    |
| 9     | set_default_account_by_address()  |

**Note**: This package has **NOT** been audited and might potentially be unsafe. Take precautions to clear memory properly, store the private keys safely, and test transaction receiving and sending functionality properly before using in production!

### IdentityManager

This is an API set that allows you to manage your multiple identity in an wallet file.

|       | Main Function                      |
| :---: | :--------------------------------- |
| 1     | create_identity()                  |
| 2     | import_identity()                  |
| 3     | create_identity_from_private_key() |

**Note**: This package has **NOT** been audited and might potentially be unsafe. Take precautions to clear memory properly, store the private keys safely, and test transaction receiving and sending functionality properly before using in production!

### Asset

The `Asset` package allows you to interact with Ontology Native Digital Asset(ONT, ONG) easily.

|       | Main Function                   |
| :---: | :------------------------------ |
| 1     | query_name()                    |
| 2     | query_symbol()                  |
| 3     | query_balance()                 |
| 4     | query_decimals()                |
| 5     | query_allowance()               |
| 6     | query_unbound_ong()             |
| 7     | get_asset_address()             |
| 8     | new_approve_transaction()       |
| 9     | new_transfer_transaction()      |
| 10    | new_transfer_from_transaction() |
| 11    | new_withdraw_ong_transaction()  |
| 12    | send_transfer()                 |
| 13    | send_approve()                  |
| 14    | send_transfer_from()            |
| 15    | send_withdraw_ong_transaction() |

### ABI

The `ABI` package allows you to interact with a deployed smart contract easily.

|       | Main Function      |
| :---: | :----------------- |
| 1     | get_function]()    |
| 2     | get_parameter()    |
| 3     | set_params_value() |

### OEP4

The `OEP4` package allows you to interact with an deployed Ontology OEP4 smart contract easily.

|       | Main Function      |
| :---: | :----------------- |
| 1     | init()             |
| 2     | get_name()         |
| 3     | get_symbol()       |
| 4     | get_decimal()      |
| 5     | get_total_supply() |
| 6     | approve()          |
| 7     | allowance()        |
| 8     | balance_of()       |
| 9     | transfer()         |
| 10    | transfer_multi()   |
| 11    | transfer_from()    |

**Note**: This package has **NOT** been audited and might potentially be unsafe. Take precautions to clear memory properly, store the private keys safely, and test transaction receiving and sending functionality properly before using in production!

### Utils

The `Utils` package provides utility functions for `Ontology Dapps` and other `Ontology-Python-Sdk` packages.

|       | Main Function       |
| :---: | :------------------ |
| 1     | get_random_hex_str()    |
| 2     | get_asset_address() |
| 3     | get_random_bytes()  |

## Contribution

Can I contribute patches to Ontology project?

Yes! Please open a pull request with signed-off commits. We appreciate your help!

You can also send your patches as emails to the developer mailing list. Please join the Ontology mailing list or forum and talk to us about it.

Either way, if you don't sign off your patches, we will not accept them. This means adding a line that says "Signed-off-by: Name <email>" at the end of each commit, indicating that you wrote the code and have the right to pass it on as an open source patch.

Also, please write good git commit messages.  A good commit message looks like this:

Header line: explain the commit in one line (use the imperative)

Body of commit message is a few lines of text, explaining things in more detail, possibly giving some background about the issue being fixed, etc etc.

The body of the commit message can be several paragraphs, and please do proper word-wrap and keep columns shorter than about 74 characters or so. That way "git log" will show things nicely even when it's indented.

Make sure you explain your solution and why you're doing what you're doing, as opposed to describing what you're doing. Reviewers and your future self can read the patch, but might not understand why a particular solution was implemented.

Reported-by: whoever-reported-it

Signed-off-by: Your Name <youremail@yourhost.com>

## Naming

If you want to contribute, we strongly recommend you to read the [Google Python Style Guide](https://github.com/google/styleguide/blob/gh-pages/pyguide.md).

### Overview

`module_name`,
`package_name`,
`ClassName`,
`method_name`,
`ExceptionName`,
`function_name`,
`GLOBAL_CONSTANT_NAME`,
`global_var_name`,
`instance_var_name`,
`function_parameter_name`,
`local_var_name`.

Function names, variable names, and filenames should be descriptive; eschew abbreviation. In particular, do not use abbreviations that are ambiguous or unfamiliar to readers outside your project, and do not abbreviate by deleting letters within a word.

Always use a `.py` filename extension. Never use dashes.

### Names to Avoid

- single character names except for counters or iterators. You may use "e" as an exception identifier in try/except statements.
- dashes (`-`) in any package/module name
- `__double_leading_and_trailing_underscore__` names (reserved by Python)

### Naming Convention

- "Internal" means internal to a module or protected or private within a class.

- Prepending a single underscore (`_`) has some support for protecting module variables and functions (not included with `from module import *`). While prepending a double underscore (`__` aka "dunder") to an instance variable or method effectively makes the variable or method private to its class (using name mangling) we discourage its use as it impacts readability and testability and isn't *really* private.

- Place related classes and top-level functions together in a module. Unlike Java, there is no need to limit yourself to one class per module.

- Use CapWords for class names, but lower\_with\_under.py for module names. **Although there are some old modules named CapWords.py, this is now discouraged because it's confusing when the module happens to be named after a class.** ("wait -- did I write `import StringIO` or `from StringIO import StringIO`?")

- Underscores may appear in *unittest* method names starting with `test` to separate logical components of the name, even if those components use CapWords. One possible pattern is `test<MethodUnderTest>_<state>`; for example `testPop_EmptyStack` is okay. There is no One Correct Way to name test methods.

### Guidelines derived from Guido's Recommendations

| Type                       | Public               | Internal                          |
| :------------------------: | :------------------: | :-------------------------------: |
| Packages                   | `lower_with_under`   |                                   |
| Modules                    | `lower_with_under`   | _lower_with_under                 |
| Classes                    | `CapWords`           | `_CapWords`                       |
| Exceptions                 | `CapWords`           |                                   |
| Functions                  | `lower_with_under()` | `_lower_with_under()`             |
| Global/Class Constants     | `CAPS_WITH_UNDER`    | `_CAPS_WITH_UNDER`                |
| Global/Class Variables     | `lower_with_under`   | `_lower_with_under`               |
| Instance Variables         | `lower_with_under`   | `_lower_with_under` (protected)   |
| Method Names               | `lower_with_under()` | `_lower_with_under()` (protected) |
| Function/Method Parameters | `lower_with_under`   |                                   |
| Local Variables            | `lower_with_under`   |                                   |

## Site

* https://ont.io/

## License

The Ontology library (i.e. all code outside of the cmd directory) is licensed under the GNU Lesser General Public License v3.0, also included in our repository in the License file.
