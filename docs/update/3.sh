wget https://raw.githubusercontent.com/ontio/documentation/master/zh-CN/standard_process_for_contributor.md -O ../pages/doc_zh/verification_provider_specification_zh.md
sed "/---/, /---/d" ../pages/doc_zh/verification_provider_specification_zh.md > tmp
echo "---
sidebar : ont_doc_zh
permalink : verification_provider_specification_zh.html
folder : doc_zh
---" | cat - tmp > temp
sed -E "s/^(\[English|English|\[中文|中文).*$/\[English\](\.\/verification_provider_specification_zh.html) \/ 中文 /g" temp > tmp && cat tmp >temp 
cat temp > ../pages/doc_zh/verification_provider_specification_zh.md

wget https://raw.githubusercontent.com/ontio/documentation/master/EN/Standard_process_for_community_contributions.md -O ../pages/doc_en/verification_provider_specification_en.md
sed "/---/, /---/d" ../pages/doc_en/verification_provider_specification_en.md > tmp
echo "---
sidebar : ont_doc_en
permalink : verification_provider_specification_en.html
folder : doc_en
---" | cat - tmp > temp
sed -E "s/^(\[English|English|\[中文|中文).*$/English \/ \[中文\](\.\/verification_provider_specification_en.html) /g" temp > tmp && cat tmp >temp 
cat temp > ../pages/doc_en/verification_provider_specification_en.md