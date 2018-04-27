wget https://raw.githubusercontent.com/ontio/documentation/master/zh-CN/the-first-open-letter-to-the-ontology-technology-community-cn.md -O ../pages/doc_zh/first_open_letter_zh.md
sed "/---/, /---/d" ../pages/doc_zh/first_open_letter_zh.md > tmp
echo "---
sidebar : ont_doc_zh
permalink : first_open_letter_zh.html
folder : doc_zh
---" | cat - tmp > temp
sed -E "s/^(\[English|English|\[中文|中文).*$/\[English\](\.\/first_open_letter_zh.html) \/ 中文 /g" temp > tmp && cat tmp >temp 
cat temp > ../pages/doc_zh/first_open_letter_zh.md



wget https://raw.githubusercontent.com/ontio/documentation/master/EN/the-first-open-letter-to-the-ontology-technology-community.md -O ../pages/doc_en/first_open_letter_en.md
sed "/---/, /---/d" ../pages/doc_en/first_open_letter_en.md > tmp
echo "---
sidebar : ont_doc_en
permalink : first_open_letter_en.html
folder : doc_en
---" | cat - tmp > temp
sed -E "s/^(\[English|English|\[中文|中文).*$/English \/ \[中文\](\.\/first_open_letter_en.html) /g" temp > tmp && cat tmp >temp 
cat temp > ../pages/doc_en/first_open_letter_en.md