wget https://raw.githubusercontent.com/ontio/ontology-wasm/master/doc/wasmvm_introduction.md -O ../pages/doc_zh/smart_contract_tutorial_wasm_zh.md
sed "/---/, /---/d" ../pages/doc_zh/smart_contract_tutorial_wasm_zh.md > tmp
echo "---
sidebar : ont_doc_zh
permalink : smart_contract_tutorial_wasm_zh.html
folder : doc_zh
---" | cat - tmp > temp
sed -E "s/^(\[English|English|\[中文|中文).*$/\[English\](\.\/smart_contract_tutorial_wasm_en.html) \/ 中文 /g" temp > tmp && cat tmp >temp 
cat temp > ../pages/doc_zh/smart_contract_tutorial_wasm_zh.md

wget https://raw.githubusercontent.com/ontio/ontology-wasm/master/doc/wasmvm_introduction.md -O ../pages/doc_en/smart_contract_tutorial_wasm_en.md
sed "/---/, /---/d" ../pages/doc_en/smart_contract_tutorial_wasm_en.md > tmp
echo "---
sidebar : ont_doc_en
permalink : smart_contract_tutorial_wasm_en.html
folder : doc_en
---" | cat - tmp > temp
sed -E "s/^(\[English|English|\[中文|中文).*$/English \/ \[中文\](\.\/smart_contract_tutorial_wasm_zh.html) /g" temp > tmp && cat tmp >temp 
cat temp > ../pages/doc_en/smart_contract_tutorial_wasm_en.md