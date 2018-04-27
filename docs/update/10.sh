wget https://raw.githubusercontent.com/ontio/documentation/master/vbft-intro/vbft-intro-CN.md -O ../pages/doc_zh/vbft_intro_zh.md
sed "/---/, /---/d" ../pages/doc_zh/vbft_intro_zh.md > tmp
echo "---
sidebar : ont_doc_zh
permalink : vbft_intro_zh.html
folder : doc_zh
---" | cat - tmp > temp
sed -E "s/^(\[English|English|\[中文|中文).*$/\[English\](\.\/vbft_intro_en.html) \/ 中文 /g" temp > tmp && cat tmp >temp 
cat temp > ../pages/doc_zh/vbft_intro_zh.md


wget https://raw.githubusercontent.com/ontio/documentation/master/vbft-intro/vbft-intro.md -O ../pages/doc_en/vbft_intro_en.md
sed "/---/, /---/d" ../pages/doc_en/vbft_intro_en.md > tmp
echo "---
sidebar : ont_doc_en
permalink : vbft_intro_en.html
folder : doc_en
---" | cat - tmp > temp
sed -E "s/^(\[English|English|\[中文|中文).*$/English \/ \[中文\](\.\/vbft_intro_zh.html) /g" temp > tmp && cat tmp >temp 
cat temp > ../pages/doc_en/vbft_intro_en.md