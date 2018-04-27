wget https://raw.githubusercontent.com/ontio/ontology-DID/master/docs/cn/claim_spec_cn.md -O ../pages/doc_zh/claim_spec_zh.md
sed "/---/, /---/d" ../pages/doc_zh/verification_provider_specification_zh.md > tmp
echo "---
sidebar : ont_doc_zh
permalink : verification_provider_specification_zh.html
folder : doc_zh
---" | cat - tmp > temp
sed -E "s/^(\[English|English|\[中文|中文).*$/\[English\](\.\/verification_provider_specification_en.html) \/ 中文 /g" temp > tmp && cat tmp >temp 
cat temp > ../pages/doc_zh/verification_provider_specification_zh.md

wget https://raw.githubusercontent.com/ontio/ontology-DID/master/docs/en/claim_spec.md -O ../pages/doc_en/claim_spec_en.md
sed "/---/, /---/d" ../pages/doc_en/verification_provider_specification_en.md > tmp
echo "---
sidebar : ont_doc_en
permalink : verification_provider_specification_en.html
folder : doc_en
---" | cat - tmp > temp
sed -E "s/^(\[English|English|\[中文|中文).*$/English \/ \[中文\](\.\/verification_provider_specification_zh.html) /g" temp > tmp && cat tmp >temp 
cat temp > ../pages/doc_en/verification_provider_specification_en.md