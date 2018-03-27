int sumArray(int * a, int * b){

	int res = 0;
	int lena = arrayLen(a);
	int lenb = arrayLen(b);

	for (int i = 0;i<lena;i++){
		res += a[i];
	}
	for (int j = 0;j<lenb;j++){
		res += b[j];
	}
	return res;
}

int concatArray(int * a, int * b){

	int lena = arrayLen(a);
	int lenb = arrayLen(b);

	int * res = (int *)malloc((lena+lenb)*sizeof(int));

	for(int i = 0; i < lena;i++){
		res[i] = a[i];
	}
	for(int j = 0; j < lenb;j++){
		res[j+lenb] = b[j];
	}
	return res;
}
