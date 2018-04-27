wget https://raw.githubusercontent.com/ontio/documentation/master/zh-CN/tutorial_for_developer.md -O ../pages/doc_zh/tutorial_for_developer_zh.md
sed "/---/, /---/d" ../pages/doc_zh/tutorial_for_developer_zh.md > tmp
echo "---
sidebar : ont_doc_zh
permalink : tutorial_for_developer_zh.html
folder : doc_zh
---" | cat - tmp > temp
sed -E "s/^(\[English|English|\[中文|中文).*$/\[English\](\.\/tutorial_for_developer_zh.html) \/ 中文 /g" temp > tmp && cat tmp >temp  
cat temp > ../pages/doc_zh/tutorial_for_developer_zh.md

wget https://raw.githubusercontent.com/ontio/documentation/master/Ontology_Developer_Guide.md -O ../pages/doc_en/tutorial_for_developer_en.md
sed "/---/, /---/d" ../pages/doc_en/tutorial_for_developer_en.md > tmp
echo "---
sidebar : ont_doc_en
permalink : tutorial_for_developer_en.html
folder : doc_en
---" | cat - tmp > temp 
sed -E "s/^(\[English|English|\[中文|中文).*$/English \/ \[中文\](\.\/tutorial_for_developer_en.html) /g" temp > tmp && cat tmp >temp 
cat temp > ../pages/doc_en/tutorial_for_developer_en.md