
# 설치
Signature Service는 [Ontology 핵심 저장소](https://github.com/ontio/ontology)의 한 부분입니다. 온톨로지 핵심 프로토콜 저장소를 다운로드하고 모든 의존성을 `$GOPATH/src/github.com/ontio`디렉토리에 설치하세요.

```
git clone https://github.com/ontio/ontology.git
```
또는
```
go get github.com/ontio/ontology
```

로컬 저장소로 이동
```
$GOPATH/src/github.com/ontio
```

프로젝트 의존성 설치
```
glide install
```

소스 코드로 SigSvr 구축
```
make tools
```

툴 디렉토리로 전환
```
cd tools
```
