
#include <stdio.h>

#ifndef ARQUIVO /*Caso o biblioteca não tenha sido compilada*/
		
	#define ARQUIVO FILE

	ARQUIVO *abreArquivo(char *nomeArquivo, char *tipo);
	int leLinha(ARQUIVO *f, char *linha);
	int escreveLinha(ARQUIVO *f,char *linha);
	int fechaArquivo(ARQUIVO *f);

#endif