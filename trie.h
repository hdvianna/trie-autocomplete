
#ifndef TRIE /*Caso o biblioteca não tenha sido compilada*/
	
	#define TRIE

	#include <stdlib.h>
    #include <ctype.h>
    #include <string.h>

	#ifndef TRUE
		#define TRUE 1
	#endif
	#ifndef FALSE
		#define FALSE 0
	#endif
	
	#define MAX 27 /*Maximo de letras no alfabeto*/	
	#define MAXPRE 50

	
	typedef struct sitem {
		char *palavra;
		int tag;
	} titem;
	
	typedef struct sNodo pNodo;
	struct sNodo { /*Um nodo que armazenará um prefixo da arvore*/				
		titem item;
		pNodo *prefixo[MAX];
	};	

	pNodo *inicializa();
	int insere(pNodo *raiz, char chave[], int tag);
	int consulta(pNodo *raiz, char chave[]);
	int remove(pNodo *raiz, char chave[]);

	pNodo *pegaNodo(pNodo *raiz, char prechave[]);
	
	void mkSelecao(pNodo *subraiz, int *quant);
	titem *selecao(pNodo *subraiz, int *quant);

#endif
	
	
	
	



	
