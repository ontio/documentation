
Cyano는 WebExtension (a.k.a Chrome plugin) 과 모바일 월렛은 **Ontology**블록체인을 위한 dAPI([OEP-6](https://github.com/backslash47/OEPs/blob/oep-dapp-api/OEP-6/OEP-6.mediawiki) 및 [CEP1](https://github.com/ontio-cyano/CEPs/blob/master/CEP1.mediawiki)) 를 구현합니다.

DAPI는 온톨로지 기반의 라이트 탈중앙화 API입니다. 이건 크롬 플러그인 월렛, 모바일 월렛 및 데스크탑 월렛을 통해 온톨로지와 커뮤니케이션하는 dApp을 지원합니다. 서로 다른 플랫폼에 대한 dApp요구사항 프로토콜은 약간 다르지만 해당 dAPI인터페이스는 비슷합니다. 현재 지원하는 두가지는 

* Chrome용 dAPI프로토콜 [OEP-6](https://github.com/backslash47/OEPs/blob/oep-dapp-api/OEP-6/OEP-6.mediawiki)
* 모바일용 dAPI프로토콜 [CEP1](https://github.com/ontio-cyano/CEPs/blob/master/CEP1.mediawiki)

월렛과 dApp과 같은 공급자와 클라이언트의 두 가지 역할이 있습니다. 크롬 인터페이스용 dAPI는 매우 다양하고 모바일용 dAPI는 로그인 및 통화 컨트랙트와 같은 주요 인터페이스를 지원하는 것 외에도 월렛 검색 및 깨우기를 지원합니다.


