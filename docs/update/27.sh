wget https://raw.githubusercontent.com/ontio/documentation/master/smart-contract-tutorial/overview.md -O ../pages/doc_zh/smart_contract_tutorial_overview_zh.md
sed "/---/, /---/d" ../pages/doc_zh/smart_contract_tutorial_overview_zh.md > tmp
echo "---
sidebar : ont_doc_zh
permalink : smart_contract_tutorial_overview_zh.html
folder : doc_zh
---" | cat - tmp > temp
sed -E "s/^(\[English|English|\[中文|中文).*$/\[English\](\.\/smart_contract_tutorial_overview_en.html) \/ 中文 /g" temp > tmp && cat tmp >temp 
cat temp > ../pages/doc_zh/smart_contract_tutorial_overview_zh.md

wget https://raw.githubusercontent.com/ontio/documentation/master/smart-contract-tutorial/overview_en.md -O ../pages/doc_en/smart_contract_tutorial_overview_en.md
sed "/---/, /---/d" ../pages/doc_en/smart_contract_tutorial_overview_en.md > tmp
echo "---
sidebar : ont_doc_en
permalink : smart_contract_tutorial_overview_en.html
folder : doc_en
---" | cat - tmp > temp
sed -E "s/^(\[English|English|\[中文|中文).*$/English \/ \[中文\](\.\/smart_contract_tutorial_overview_zh.html) /g" temp > tmp && cat tmp >temp 
cat temp > ../pages/doc_en/smart_contract_tutorial_overview_en.md