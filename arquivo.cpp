#include "arquivo.h"

FILE *abreArquivo(char *nomeArquivo, char *tipo) {
	return fopen(nomeArquivo,tipo);
}

int fechaArquivo(FILE *f) {
	return fclose(f);
}

int leLinha(FILE *f, char *linha){        
	
    if (!feof(f)) {          		
		fscanf(f,"%s",linha);
		return 1;
    } else {		
		return 0;
	}     
    
}

int escreveLinha(FILE *f,char *linha) {
	
	if (fprintf(f,"%s\n",linha))
		return 1;
	else
		return 0;
}

