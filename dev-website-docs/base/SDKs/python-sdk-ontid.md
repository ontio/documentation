
<!-- TOC -->

- [소개](#소개)
- [준비](#준비)
- [RPC 인터페이스 함수 리스트](#RPC_인터페이스_함수_리스트)
- [월렛 기능 목록](#월렛_기능_목록)
  - [디지털 계정](#디지털_계정)
  - [디지털 신분](#디지털_신분)
- [자산 기능 목록](#자산_기능_목록)
  - [기본 숫자 애셋](#기본_숫자_애셋)
- [신원 기능 목록](#신원_기능_목록)
  - [ONT ID](#ont-id)
- [기부금](#기부금)
- [이름 지정](#이름지정)
  - [개요](#개요)
  - [피해야 할 이름](#피해야_할_이름)
  - [네밍 협약](#네이밍_협약)
  - [Guido의 권장 사항에 나온 지침](#Guido의_권장_사항에_나온_지침)
- [사이트](#사이트)
- [라이센스](#라이센스)

<!-- /TOC -->


## 소개
온톨로지 Python SDK 기능은 RPC 인터페이스, 지갑, 자산 및 ID의 네 부분으로 구성됩니다. RPC 인터페이스의 경우 트랜잭션 쿼리 및 전송을 포함하여 온톨로지 블록체인과 상호 작용해야합니다. 지갑의 경우 지갑파일을 관리하고 자산 계정 및 ID의 암호화 된 프라이빗키 키를 저장합니다. 자산 기능은 ONT / ONG 양도, 계좌 잔액 확인, ONT / ONG 철회 등의 작업을 수행 할 수 있습니다. ID의 기능은 ONT ID를 등록하고 DDO 객체를 가져 오기위한 요청을 보낼 수 있습니다. 이 네 가지 부분 외에도 SDK는 스마트 컨트랙트 작성, 배포 및 호출을 지원합니다.

## 준비

설치에는 Python 3.7 이상의 환경이 필요합니다.

```bash
pip install ontology-python-sdk
```

## RPC 인터페이스 기능 목록


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

## 월렛 기능 목록

지갑 기능에는 디지털 계정, 디지털 신분 그리고 kestore인터페이스 이렇게 3부분이 포함됩니다. 니모닉과 kestore인터페이스는 지원 될 예정입니다.

### 디지털 계정

 |      | Main   Function                                                                           |
 | :--- | :---------------------------------------------------------------------------------------- |
 | 1    | import_account(label: str, encrypted_pri_key: str, pwd: str, base58_addr: str, salt: str) |
 | 2    | create_account(label: str, pwd: str, salt: str, priv_key: bytes, account_flag: bool)      |
 | 3    | create_account_from_private_key(label: str, pwd: str, private_key: bytes)                 |
 | 4    | get_account(address: str, pwd: str)                                                       |
 | 5    | get_accounts()                                                                            |
 | 6    | get_default_account()                                                                     |
 | 7    | set_default_account_by_address(b58_address: str)                                          |
 | 8    | set_default_account_by_index(index: int)                                                  |
 | 9    | get_default_account_address()                                                             |

### 디지털 계정

 |      | Main   Function                                                                        |
 | :--- | :------------------------------------------------------------------------------------- |
 | 1    | import_identity(label: str, encrypted_pri_key: str, pwd: str, salt: str, address: str) |
 | 2    | create_identity(label: str, pwd: str, salt: str, private_key: bytes)                   |
 | 3    | create_identity_from_private_key(label: str, pwd: str, private_key: bytes)             |

## 자산 기능 목록

자산에는 네이티브 디지털 자산 과 Nep-5 스마트 컨트랙트 디지털 자산이 포함됩니다. Nep-5 스마트 컨트랙트는 지원 될 예정입니다.

### 네이티브 디지털 자산

 |      | Main   Function                                                                                                                                |
 | :--- | :--------------------------------------------------------------------------------------------------------------------------------------------- |
 | 1    | new_transfer_transaction(asset: str, from_address: str, to_address: str, amount: int, payer: str, gas_limit: int, gas_price: int)              |
 | 2    | query_balance(asset: str, addr: str)                                                                                                           |
 | 3    | query_allowance(asset: str, b58_from_address: str, b58_to_address: str)                                                                        |
 | 4    | query_name(asset: str)                                                                                                                         |
 | 5    | query_symbol(asset: str)                                                                                                                       |
 | 6    | query_decimals(asset: str)                                                                                                                     |
 | 7    | send_withdraw_ong_transaction(claimer: Account, recv_addr: str, amount: int, payer: Account, gas_limit: int, gas_price: int)                   |
 | 8    | send_approve(asset: str, sender: Account, recv_addr: str, amount: int, payer: Account, gas_limit: int, gas_price: int)                         |
 | 9    | send_transfer_from(asset: str, sender: Account, from_address: str, recv_addr: str, amount: int,payer: Account, gas_limit: int, gas_price: int) |

## 신분 기능 목록 

### ONT ID

 |      | Main   Function                                                                                                                         |
 | :--- | :-------------------------------------------------------------------------------------------------------------------------------------- |
 | 1    | new_registry_ont_id_transaction(ont_id: str, pubkey: str, payer: str, gas_limit: int, gas_price: int)                                    |
 | 2    | new_add_attribute_transaction(ont_id: str, pubkey: str, attris: list, payer: str, gas_limit: int, gas_price: int)                       |
 | 3    | new_remove_attribute_transaction(ont_id: str, pubkey: bytearray, path: str, payer: str, gas_limit: int, gas_price: int)                 |
 | 4    | new_add_public_key_transaction(ont_id: str, pubkey_or_recovery: bytes, new_pubkey: bytes, payer: str,gas_limit: int, gas_price: int)        |
 | 5    | new_remove_public_key_transaction(ont_id: str, pubkey_or_recovery: bytes, remove_pubkey: bytes, payer: str, gas_limit: int, gas_price: int) |
 | 6    | new_add_recovery_transaction(ont_id: str, pubkey: bytes, recovery: str, payer: str, gas_limit: int,gas_price: int)                      |
 | 7    | new_get_ddo_transaction(ont_id: str)                                                                                                    |
 | 8    | parse_ddo(ont_id: str, ddo: str)                                                                                                        |

## 기부금

온톨로지 프로젝트에 패치를 제공할 수 있나요?

네! 서명하신 커밒으로 풀 요청을 열어주세요.

패치를 전자 메일로 개발자 메일 링리스트에 보낼 수도 있습니다. 온톨로지 메일 링리스트 또는 포럼에 가입하신 후 알려주세요.

어떠한 방식이였든, 패치에 서명하지 않았을 경우 패치를 수락하지 않습니다. 이는 각 커밋이 끝날 때 "서명:이름<이메일>"이라는 줄을 추가한다는 것을 의미합니다. 아울러 코드를 작성했고 오픈 소스 패치로 전달할 권리가 있음을 나타냅니다.

또한, 좋은 커밋 메시지를 작성해주세요. 좋은 커밋 메시지는 다음과 같습니다. 

헤더 라인 : 커밋을 한 줄로 설명합니다 (명령형 사용).

커밋 메시지 본문은 몇 줄의 텍스트로 더 자세하게 설명하고 고정 된 문제 등에 대한 배경 정보를 제공합니다.

커밋 메시지 본문은 여러 단락이 될 수 있으므로 적절한 줄 바꿈과 대략 74 자 정도의 줄을 유지하십시오. 이와같이 할 경우 "git log"가 들여쓰기 되어도 멋지게 표시됩니다.

자신이 하는 일을 설명하는 것과는 대조적으로 자신의 솔루션을 설명하고 자신이 하고 있는 일을하는 이유 또한 확인하십시오. 리뷰어와 미래에 패치를 읽을 수는 있지만 특정 솔루션이 구현 된 이유를 이해하지 못 할 수도 있습니다.

작성자: 누구든 읽을 수 있음

사인:이름 <youremail@yourhost.com>

## 네이밍

참여하려면 [구글 파이썬 스타일 가이드](https://github.com/google/styleguide/blob/gh-pages/pyguide.md)를 읽어 보시기 바랍니다.

### 개요

`모듈이름`,
`페키지 이름`,
`클래스이름`,
`방법이름`,
`예외이름`,
`함수이름`,
`일정한 글로벌 이름`,
`글로벌 이름`,
`대체이름`,
`파라미터 함수 이름`,
`로컬 이름`.

함수 이름, 변수 이름 및 파일 이름의 설명 적이어야합니다; 약어는 삼가합니다. 특히, 프로젝트 외부의 독자들에게 모호하거나 익숙하지 않은 약어 사용을 삼가해주세요.

항상`.py`으로 파일이름을 사용하고 -를 사용하지 마세요.

### 피할 이름

- 카운터 또는 반복자를 제외한 단일 문자 이름. try / except 문에서 "e"를 예외 식별자로 사용할 수 있습니다.
- 모든 패키지 / 모듈 이름에서 대시 (`-`)
- `__double_leading_and_trailing_underscore__` 이름들 (파이썬으로 씀)

### 네이밍 규칙

- "내부"는 모듈 내부 또는 보호 또는 클래스 내의 개인을 뜻합니다.

- 밑줄 하나를 (`_`)을 붙이면 모듈 변수와 함수를 보호 할 수 있습니다 (`from module import *`에는 포함되지 않습니다). 인스턴스 변수 또는 메소드에 두 개의 밑줄 (`__`aka dunder)을 붙이면 변수 또는 메소드가 클래스에 비공개로 만들어 지지만 (네이밍 맹글링을 사용하여) 가독성과 테스트 가능성에 영향을 미치므로 실제적인 사용을 권장하지 않습니다.

- 관련 클래스와 최상위 함수를 함께 모듈에 배치합니다. Java와 달리 모듈 당 하나의 클래스로 제한 할 필요가 없습니다.

클래스 이름에는 CapWords를 사용하고 모듈 이름에는 \ _with \ _under.py를 낮추십시오. ** CapWords.py라는 이름의 오래된 모듈이 있지만, 모듈이 클래스 이름을 따서 네이밍 될 때 혼란 스럽기 때문에 현재 권장하지 않습니다. ** ( "wait - import import StringIO`** 또는`StringIO import에서 작성 했나요? StringIO`? ")`

-`test`로 시작하는 * unittest * 메소드 이름에 밑줄이 나타날 수 있습니다. 이름의 논리적 구성 요소는 CapWords를 사용하더라 가능한 패턴은`test <methodUnderTest> _ <state>`하나로 사용합니다; 예)`testPop_EmptyStack`. 네임 테스트 방법에 단 하나의 정답은 없습니다.

### Guido의 권장 사항에서 나온 지침

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


## 사이트

* https://ont.io/

## 라이센스

온톨로지 라이브러리 (즉, cmd 디렉토리 외부의 모든 코드)는 GNU 약소한 일반 공중 사용 허가서 v3.0에 따라 사용이 허가되며, 라이센스 파일의 저장소에도 포함되어 있습니다.

