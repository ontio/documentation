sed "/---/, /---/d" ./pages/doc_en/ontology_ddxf_en.md > tmp
echo "---
sidebar : ont_doc_en
permalink : ontology_ddxf_en.html
folder : doc_zh
---" | cat - tmp > temp
sed -E "s/^(\[English|English|\[中文|中文).*$/\[English\](\.\/ontology_ddxf_zh.html) \/ 中文 /g" temp > tmp && cat tmp >temp
cat temp > ./pages/doc_en/ontology_ddxf_en.md
