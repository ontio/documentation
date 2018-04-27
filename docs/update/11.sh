wget https://raw.githubusercontent.com/ontio/ontology-DID/master/README_cn.md -O ../pages/doc_zh/ontology_DID_zh.md
sed "/---/, /---/d" ../pages/doc_zh/ontology_DID_zh.md > tmp
echo "---
sidebar : ont_doc_zh
permalink : ontology_DID_zh.html
folder : doc_zh
---" | cat - tmp > temp
sed -E "s/^(\[English|English|\[中文|中文).*$/\[English\](\.\/ontology_DID_en.html) \/ 中文 /g" temp > tmp && cat tmp >temp 
cat temp > ../pages/doc_zh/ontology_DID_zh.md

wget https://raw.githubusercontent.com/ontio/ontology-DID/master/README.md -O ../pages/doc_en/ontology_DID_en.md
sed "/---/, /---/d" ../pages/doc_en/ontology_DID_en.md > tmp
echo "---
sidebar : ont_doc_en
permalink : ontology_DID_en.html
folder : doc_en
---" | cat - tmp > temp
sed -E "s/^(\[English|English|\[中文|中文).*$/English \/ \[中文\](\.\/ontology_DID_zh.html) /g" temp > tmp && cat tmp >temp 
cat temp > ../pages/doc_en/ontology_DID_en.md