
### 설치파일 다운로드

Go언어 기반의 온톨로지 CLI을 사용하여 프로그램을 설치할 수 있는 2가지 방법입니다.
- [여기](https://github.com/ontio/ontology/releases) 를 클릭한 후 온톨로지 CLI를 다운로드 받아주세요.
- `curl` 사용하여 최신 CLI를 받아주세요.

  ```shell
  curl https://dev.ont.io/ontology_install | sh
  ```

### 소스 코드로 컴파일

그 외, 소스코드를 사용하여 온톨로지 CLI를 컴파일 할 수 있습니다.

1. 소스 코드 얻기：

   ```shell
   go get github.com/ontio/ontology
   ```

2. `glide` 를 먼저 다운로드 받아주세요.

   ```shell
   cd $GOPATH/src/github.com/ontio/ontology
   glide install
   ```

3. 소스코드 컴파일：

   ```shell
   make all
   ```
   컴파일 성공 후 두 개의 실행가능 프로그램이 생성됩니다.

   - ontology: Ontology CLI
   - sigsvr：시그니처 서버
