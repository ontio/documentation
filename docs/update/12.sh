wget https://raw.githubusercontent.com/ontio/ontology-DID/master/docs/cn/ONTID_protocol_spec_cn.md -O ../pages/doc_zh/ONTID_protocol_spec_zh.md
sed "/---/, /---/d" ../pages/doc_zh/ONTID_protocol_spec_zh.md > tmp
echo "---
sidebar : ont_doc_zh
permalink : ONTID_protocol_spec_zh.html
folder : doc_zh
---" | cat - tmp > temp
sed -E "s/^(\[English|English|\[中文|中文).*$/\[English\](\.\/ONTID_protocol_spec_en.html) \/ 中文 /g" temp > tmp && cat tmp >temp 
cat temp > ../pages/doc_zh/ONTID_protocol_spec_zh.md

wget https://raw.githubusercontent.com/ontio/ontology-DID/master/docs/en/ONTID_protocol_spec.md -O ../pages/doc_en/ONTID_protocol_spec_en.md
sed "/---/, /---/d" ../pages/doc_en/ONTID_protocol_spec_en.md > tmp
echo "---
sidebar : ont_doc_en
permalink : ONTID_protocol_spec_en.html
folder : doc_en
---" | cat - tmp > temp
sed -E "s/^(\[English|English|\[中文|中文).*$/English \/ \[中文\](\.\/ONTID_protocol_spec_zh.html) /g" temp > tmp && cat tmp >temp 
cat temp > ../pages/doc_en/ONTID_protocol_spec_en.md