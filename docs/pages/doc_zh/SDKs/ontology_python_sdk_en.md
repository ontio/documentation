---
title:
keywords: sample homepage
sidebar: SDKs_zh
permalink: ontology_python_sdk_en.html
folder: doc_zh/SDKs
giturl: https://github.com/ontio/ontology-python-sdk/blob/master/README.md
---

<h1 align="center">Python SDK For Ontology</h1>

<p align="center" class="version">Version 0.1.2</p>

<!-- TOC -->

- [Introduction](#introduction)
- [Preparations](#preparations)
- [RPC interface function list](#rpc-interface-function-list)
- [Wallet function list](#wallet-function-list)
  - [Digit account](#digit-account)
  - [Digit identity](#digit-identity)
- [Asset function list](#asset-function-list)
  - [Native digit asset](#native-digit-asset)
- [Identity function list](#identity-function-list)
  - [ONT ID](#ont-id)
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
Ontology Python SDK function consists of four parts, RPC interface, wallet, asset, and identity. For RPC interface, it is responsible to interact with the Ontology blockchain, including querying and sending transactions. For wallet, it manages wallet file and store the encrypted private key of the asset account and identity. The function of asset can transfer ONT/ONG, check account balance, withdraw ONT/ONG and so on. The function of identity can send request to register ONT ID and get DDO object. In addition to these four parts, SDK also support constructing, deploying, and invoking a smart contract. 

## Preparations

Installation requires a Python 3.7 or later environment.

```bash
pip install ontology-python-sdk
```

## RPC interface function list


 |      | Main   Function                                        |
 | :--- | :----------------------------------------------------- |
 | 1    | get_version()                                          |
 | 2    | get_block_by_hash (block_hash)                         |
 | 3    | get_block_by_height (block_height)                     |
 | 4    | get_block_count ()                                     |
 | 5    | get_current_block_hash ()                              |
 | 6    | get_block_hash_by_height (block_height)                |
 | 7    | get_balance (account_address)                          |
 | 8    | get_allowance (account_address)                        |
 | 9    | get_storage (contract_address, key)                    |
 | 10   | get_smart_contract_event_by_tx_hash (transaction_hash) |
 | 11   | get_smart_contract_event_by_height (block_height)      |
 | 12   | get_raw_transaction (transaction_hash)                 |
 | 13   | get_smart_contract (contract_address)                  |
 | 14   | get_merkle_proof (transaction_hash)                    |
 | 15   | send_raw_transaction (transaction)                     |
 | 16   | send_raw_transaction_pre_exec (transaction)            |
 | 17   | get_node_count ()                                      |
 | 18   | get_gas_price ()                                       |

## Wallet function list

The wallet function includes three parts, digit account, digit identity, and mnemonics and kestore interface. Mnemonics and kestore interface will be supported in the future.

### Digit account

 |      | Main   Function                                                                           |
 | :--- | :---------------------------------------------------------------------------------------- |
 | 1    | import_account(label: str, encrypted_pri_key: str, pwd: str, base58_addr: str, salt: str) |
 | 2    | create_account(label: str, pwd: str, salt: str, priv_key: bytes, account_flag: bool)      |
 | 3    | create_account_from_private_key(label: str, pwd: str, private_key: bytes)                      |
 | 4    | get_account(address: str, pwd: str)                                                       |
 | 5    | get_accounts()                                                                            |
 | 6    | get_default_account()                                                                     |
 | 7    | set_default_account_by_address(b58_address: str)                                          |
 | 8    | set_default_account_by_index(index: int)                                                  |
 | 9   | get_default_account_address()                                                             |

### Digit identity

 |      | Main   Function                                                                        |
 | :--- | :------------------------------------------------------------------------------------- |
 | 1    | import_identity(label: str, encrypted_pri_key: str, pwd: str, salt: str, address: str) |
 | 2    | create_identity(label: str, pwd: str, salt: str, private_key: bytes)                   |
 | 3    | create_identity_from_pri_key(label: str, pwd: str, private_key: bytes)                 |

## Asset function list

The asset includes native digit asset and Nep-5 smart constract digit asset. Nep-5 smart constract will be supported in the future.

### Native digit asset

 |      | Main   Function                                                                                                                             |
 | :--- | :------------------------------------------------------------------------------------------------------------------------------------------ |
 | 1    | new_transfer_transaction(asset: str, from_addr: str, to_addr: str, amount: int, payer: str, gas_limit: int, gas_price: int)                 |
 | 2    | query_balance(asset: str, addr: str)                                                                                                        |
 | 3    | query_allowance(asset: str, b58_from_address: str, b58_to_address: str)                                                                                   |
 | 4    | query_name(asset: str)                                                                                                                      |
 | 5    | query_symbol(asset: str)                                                                                                                    |
 | 6    | query_decimals(asset: str)                                                                                                                  |
 | 7    | send_withdraw_ong_transaction(claimer: Account, recv_addr: str, amount: int, payer: Account, gas_limit: int, gas_price: int)                |
 | 8    | send_approve(asset: str, sender: Account, recv_addr: str, amount: int, payer: Account, gas_limit: int, gas_price: int)                      |
 | 9    | send_transfer_from(asset: str, sender: Account, from_addr: str, recv_addr: str, amount: int,payer: Account, gas_limit: int, gas_price: int) |

## Identity function list 

### ONT ID

 |      | Main   Function                                                                                                                         |
 | :--- | :-------------------------------------------------------------------------------------------------------------------------------------- |
 | 1    | new_registry_ontid_transaction(ont_id: str, pubkey: str, payer: str, gas_limit: int, gas_price: int)                                    |
 | 2    | new_add_attribute_transaction(ont_id: str, pubkey: str, attris: list, payer: str, gas_limit: int, gas_price: int)                       |
 | 3    | new_remove_attribute_transaction(ont_id: str, pubkey: bytearray, path: str, payer: str, gas_limit: int, gas_price: int)                 |
 | 4    | new_add_pubkey_transaction(ont_id: str, pubkey_or_recovery: bytes, new_pubkey: bytes, payer: str,gas_limit: int, gas_price: int)        |
 | 5    | new_remove_pubkey_transaction(ont_id: str, pubkey_or_recovery: bytes, remove_pubkey: bytes, payer: str, gas_limit: int, gas_price: int) |
 | 6    | new_add_recovery_transaction(ont_id: str, pubkey: bytes, recovery: str, payer: str, gas_limit: int,gas_price: int)                      |
 | 7    | new_get_ddo_transaction(ont_id: str)                                                                                                    |
 | 8    | parse_ddo(ont_id: str, ddo: str)                                                                                                        |

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

Always use a `.py` filename extension. Never use dashe

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

<table rules="all" border="1" summary="Guidelines from Guido's Recommendations"
       cellspacing="2" cellpadding="2">

  <tr>
    <th>Type</th>
    <th>Public</th>
    <th>Internal</th>
  </tr>

  <tr>
    <td>Packages</td>
    <td><code>lower_with_under</code></td>
    <td></td>
  </tr>

  <tr>
    <td>Modules</td>
    <td><code>lower_with_under</code></td>
    <td><code>_lower_with_under</code></td>
  </tr>

  <tr>
    <td>Classes</td>
    <td><code>CapWords</code></td>
    <td><code>_CapWords</code></td>
  </tr>

  <tr>
    <td>Exceptions</td>
    <td><code>CapWords</code></td>
    <td></td>
  </tr>

  <tr>
    <td>Functions</td>
    <td><code>lower_with_under()</code></td>
    <td><code>_lower_with_under()</code></td>
  </tr>

  <tr>
    <td>Global/Class Constants</td>
    <td><code>CAPS_WITH_UNDER</code></td>
    <td><code>_CAPS_WITH_UNDER</code></td>
  </tr>

  <tr>
    <td>Global/Class Variables</td>
    <td><code>lower_with_under</code></td>
    <td><code>_lower_with_under</code></td>
  </tr>

  <tr>
    <td>Instance Variables</td>
    <td><code>lower_with_under</code></td>
    <td><code>_lower_with_under</code> (protected)</td>
  </tr>

  <tr>
    <td>Method Names</td>
    <td><code>lower_with_under()</code></td>
    <td><code>_lower_with_under()</code> (protected)</td>
  </tr>

  <tr>
    <td>Function/Method Parameters</td>
    <td><code>lower_with_under</code></td>
    <td></td>
  </tr>

  <tr>
    <td>Local Variables</td>
    <td><code>lower_with_under</code></td>
    <td></td>
  </tr>

</table>


## Site

* https://ont.io/

## License

The Ontology library (i.e. all code outside of the cmd directory) is licensed under the GNU Lesser General Public License v3.0, also included in our repository in the License file.
