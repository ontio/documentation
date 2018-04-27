wget https://raw.githubusercontent.com/ontio/documentation/master/smart-contract-tutorial/README_cn.md -O ../pages/doc_zh/smart_contract_tutorial_zh.md
sed "/---/, /---/d" ../pages/doc_zh/smart_contract_tutorial_zh.md > tmp
echo "---
sidebar : ont_doc_zh
permalink : smart_contract_tutorial_zh.html
folder : doc_zh
---" | cat - tmp > temp
sed -E "s/^(\[English|English|\[中文|中文).*$/\[English\](\.\/smart_contract_tutorial_en.html) \/ 中文 /g" temp > tmp && cat tmp >temp 
sed -E "s/\README\_wasm\.md/\https\:\/\/github\.com\/ontio\/documentation\/blob\/master\/smart\-contract\-tutorial\/README\_wasm\.md /g" temp > tmp && cat tmp >temp 
cat temp > ../pages/doc_zh/smart_contract_tutorial_zh.md

wget https://raw.githubusercontent.com/ontio/documentation/master/smart-contract-tutorial/README.md -O ../pages/doc_en/smart_contract_tutorial_en.md
sed "/---/, /---/d" ../pages/doc_en/smart_contract_tutorial_en.md > tmp
echo "---
sidebar : ont_doc_en
permalink : smart_contract_tutorial_en.html
folder : doc_en
---" | cat - tmp > temp
sed -E "s/^(\[English|English|\[中文|中文).*$/English \/ \[中文\](\.\/smart_contract_tutorial_zh.html) /g" temp > tmp && cat tmp >temp 
sed -E "s/\README\_wasm\.md/\https\:\/\/github\.com\/ontio\/documentation\/blob\/master\/smart\-contract\-tutorial\/README\_\wasm\.md /g" temp > tmp && cat tmp >temp 
cat temp > ../pages/doc_en/smart_contract_tutorial_en.md