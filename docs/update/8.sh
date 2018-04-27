wget https://raw.githubusercontent.com/ontio/documentation/master/ontology-API/ontrpcapi.md -O ../pages/doc_en/ontrpcapi_en.md
sed "/---/, /---/d" ../pages/doc_en/ontrpcapi_en.md > tmp
echo "---
sidebar : ont_doc_en
permalink : ontrpcapi_en.html
folder : doc_en
---" | cat - tmp > temp
sed -E "s/^(\[English|English|\[中文|中文).*$/English \/ \[中文\](\.\/ontrpcapi_zh.html) /g" temp > tmp && cat tmp >temp 
cat temp > ../pages/doc_en/ontrpcapi_en.md


wget https://raw.githubusercontent.com/ontio/documentation/master/ontology-API/ontrpcapi.md -O ../pages/doc_zh/ontrpcapi_zh.md
sed "/---/, /---/d" ../pages/doc_zh/ontrpcapi_zh.md > tmp
echo "---
sidebar : ont_doc_zh
permalink : ontrpcapi_zh.html
folder : doc_zh
---" | cat - tmp > temp
sed -E "s/^(\[English|English|\[中文|中文).*$/\[English\](\.\/ontrpcapi_en.html) \/ 中文 /g" temp > tmp && cat tmp >temp 
cat temp > ../pages/doc_zh/ontrpcapi_zh.md
