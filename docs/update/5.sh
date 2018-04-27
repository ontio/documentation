wget https://raw.githubusercontent.com/ontio/ontology/master/docs/specifications/install.md -O ../pages/doc_en/ontology_install_en.md
sed "/---/, /---/d" ../pages/doc_en/ontology_install_en.md > tmp
echo "---
sidebar : ont_doc_en
permalink : ontology_install_en.html
folder : doc_en
---" | cat - tmp > temp
sed -E "s/^(\[English|English|\[中文|中文).*$/English \/ \[中文\](\.\/ontology_install_zh.html) /g" temp > tmp && cat tmp >temp 
cat temp > ../pages/doc_en/ontology_install_en.md

wget https://raw.githubusercontent.com/ontio/ontology/master/docs/specifications/install_CN.md -O ../pages/doc_zh/ontology_install_zh.md
sed "/---/, /---/d" ../pages/doc_zh/ontology_install_zh.md > tmp
echo "---
sidebar : ont_doc_zh
permalink : ontology_install_zh.html
folder : doc_zh
---" | cat - tmp > temp
sed -E "s/^(\[English|English|\[中文|中文).*$/\[English\](\.\/ontology_install_en.html) \/ 中文 /g" temp > tmp && cat tmp >temp 
cat temp > ../pages/doc_zh/ontology_install_zh.md