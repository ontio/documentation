wget https://raw.githubusercontent.com/ontio/documentation/master/FAQ/FAQ.md -O ../pages/doc_zh/FAQ_zh.md
sed "/---/, /---/d" ../pages/doc_zh/FAQ_zh.md > tmp
echo "---
sidebar : ont_doc_zh
permalink : FAQ_zh.html
folder : doc_zh
---" | cat - tmp > temp
sed -E "s/^(\[English|English|\[中文|中文).*$/\[English\](\.\/FAQ_en.html) \/ 中文 /g" temp > tmp && cat tmp >temp 
cat temp > ../pages/doc_zh/FAQ_zh.md

wget https://raw.githubusercontent.com/ontio/documentation/master/FAQ/FAQ.md -O ../pages/doc_en/FAQ_en.md
sed "/---/, /---/d" ../pages/doc_en/FAQ_en.md > tmp
echo "---
sidebar : ont_doc_en
permalink : FAQ_en.html
folder : doc_en
---" | cat - tmp > temp
sed -E "s/^(\[English|English|\[中文|中文).*$/English \/ \[中文\](\.\/FAQ_zh.html) /g" temp > tmp && cat tmp >temp 
cat temp > ../pages/doc_en/FAQ_en.md