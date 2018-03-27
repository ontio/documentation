char * concat(char * a, char * b){
	int lena = arrayLen(a);
	int lenb = arrayLen(b);
	char * res = (char *)malloc((lena + lenb)*sizeof(char));
	for (int i = 0 ;i < lena ;i++){
		res[i] = a[i];
	}

	for (int j = 0; j < lenb ;j++){
		res[lenb + j] = b[j];
	}
	return res;
}
