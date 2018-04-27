wget https://raw.githubusercontent.com/ontio/ontology/master/docs/specifications/features.md -O ../pages/doc_en/ontology_features_en.md
sed "/---/, /---/d" ../pages/doc_en/ontology_features_en.md > tmp
echo "---
sidebar : ont_doc_en
permalink : ontology_features_en.html
folder : doc_en
---" | cat - tmp > temp
sed -E "s/^(\[English|English|\[中文|中文).*$/\[English\](\.\/ontology_features_en.html) \/ 中文 /g" temp > tmp && cat tmp >temp 
cat temp > ../pages/doc_en/ontology_features_en.md

wget https://raw.githubusercontent.com/ontio/ontology/master/docs/specifications/features_CN.md -O ../pages/doc_zh/ontology_features_zh.md
sed "/---/, /---/d" ../pages/doc_zh/ontology_features_zh.md > tmp
echo "---
sidebar : ont_doc_zh
permalink : ontology_features_zh.html
folder : doc_zh
---" | cat - tmp > temp
sed -E "s/^(\[English|English|\[中文|中文).*$/English \/ \[中文\](\.\/ontology_features_zh.html) /g" temp > tmp && cat tmp >temp 
cat temp > ../pages/doc_zh/ontology_features_zh.md