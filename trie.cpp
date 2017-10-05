#include "trie.h"

#ifndef SEL
	#define SEL
	titem *vetSelecao;
#endif

pNodo *inicializa() {/*Faz a inicialização da Árvore Trie*/
	
	pNodo *raiz = (pNodo*) calloc(1,sizeof(pNodo)); /*Cria a Raiz da árvore*/

	if (!raiz) {
		return NULL;
	}
	
	for (int i=0; i < MAX; i++)
		raiz->prefixo[i]=NULL; /*Faz o endereço de todos os filhos apontarem pra NULL*/
	
	raiz->item.tag=0;

	return raiz;

}

int insere(pNodo *raiz, char chave[], int tag) {

	pNodo *prefixo, *nodo;
	int i, j, k;
	char letra;

	prefixo = raiz;

	for (i=0; i< strlen(chave); ++i) { /*Vai inserindo prefixo por prefixo na arvore*/

        
		letra = toupper(chave[i]); /*coloca o caracter em caixa alta*/
		
		if ((letra>='A') && (letra <='Z')) 
			j=letra-'A'; /*Pega a posição onde será inserido o novo nodo*/
		else
			j=MAX-1;

		if (!prefixo->prefixo[j]) {
			nodo = (pNodo*) calloc(1,sizeof(pNodo));
			if (!nodo) /*Insere o nodo no vetor*/
				return FALSE;
			for (k=0;k<MAX;++k) /*Limpa o vetor dos filhos do nodo*/
				nodo->prefixo[k]=NULL;
			nodo->item.tag = 0;
			prefixo->prefixo[j] = nodo;
		}

		prefixo = prefixo->prefixo[j];/*caminha para o proximo nodo*/
	}

	if (prefixo->item.tag  > 0)
		return FALSE;
		
	prefixo->item.tag = tag;		
	prefixo->item.palavra = (char*) malloc(sizeof(char) * (strlen(chave)+1));/*Aloca o espaço suficiente para a cópia da string*/	
	strcpy(prefixo->item.palavra, chave); /*Copia a chave para o nodo*/		
	return TRUE;
		
}

int consulta(pNodo *raiz, char chave[]) {
	
	pNodo *prefixo;
	int i,j;
	char letra;
	
	prefixo = raiz;
	i=0;

	while (i<(strlen(chave))) {
		
		letra=toupper(chave[i]);
		
		if ((letra >='A') && (letra<='Z'))
			j = letra - 'A';/*Pega a posição onde será inserido o novo nodo*/
		else
			j = MAX - 1;

		if (!(prefixo->prefixo[j])) /*Se chegou no fim da arvore*/
			return 0;
		
		prefixo = prefixo->prefixo[j];
		i++;		
	}

	if ((prefixo->item.tag > 0) && (i == strlen(chave)))
		return prefixo->item.tag; /*Retorna o tag do item encontrado*/
	else
		return 0;

}

int remove(pNodo *raiz, char chave[]) {
	
	pNodo *prefixo;	
	int i,j;
	char letra;

	prefixo = raiz;
	i=0;

	while (i < strlen(chave)) {
		
		letra = toupper(chave[i]);
	
		if ((letra >= 'A') && (letra <= 'Z'))
			j = letra - 'A';/*Pega a posição onde será inserido o novo nodo*/
		else
			j = MAX - 1;

		if (!(prefixo->prefixo[j])) /*Não encontrou o item na arvore*/
			return FALSE;

		prefixo = prefixo->prefixo [j];/*Vai para o proximo item*/
		i++;
	}

	if (prefixo->item.tag > 0) {				
		prefixo->item.tag=0; /*Remove o item, ou seja, seta tag para zero*/
		free(prefixo->item.palavra);/*Libera a string da memória*/
		return TRUE;
	}

	return FALSE;

}


pNodo *pegaNodo(pNodo *raiz, char prechave[]) {
	
	pNodo *prefixo;	
	int i,j;
	char letra;

	prefixo = raiz;
	i=0;

	while (i < strlen(prechave)) {
		
		letra = toupper(prechave[i]);
	
		if ((letra >= 'A') && (letra <= 'Z'))
			j = letra - 'A';/*Pega a posição onde será inserido o novo nodo*/
		else
			j = MAX - 1;

		if (!(prefixo->prefixo[j])) /*Não encontrou o item na arvore*/
			return NULL;		

		prefixo = prefixo->prefixo [j];/*Vai para o proximo item*/
		i++;
	}

	return prefixo; /*Retorna o endereço do prefixo onde deve ser iniciado a pesquisa*/

}

titem *selecao(pNodo *subraiz, int *quant) {	

	mkSelecao(subraiz,quant);
	return vetSelecao; /*Retorna a selecao*/

}

void mkSelecao(pNodo *subraiz, int *quant) { /*Cria um vetor com as palavras selecionadas*/


	pNodo *prefixo;
	int i;	
	
	prefixo = subraiz;				

	if (prefixo) {
		
		if (prefixo->item.tag) {		
			
			if (!(*quant))
				vetSelecao = NULL;

			(*quant)++; /*Incrementa a quantidade de palavras encontradas*/
			vetSelecao = (titem*) realloc(vetSelecao,sizeof(titem)*(*quant)); /*aloca o espaço necessário*/
			vetSelecao[(*quant)-1].tag = prefixo->item.tag;

			vetSelecao[(*quant)-1].palavra = (char*) malloc(sizeof(char) * strlen(prefixo->item.palavra));/*Aloca o espaço suficiente para a cópia da string*/
			strcpy(vetSelecao[(*quant)-1].palavra, prefixo->item.palavra); /*Copia a chave para o nodo*/			
				
		}
				
		for (i=0;i< MAX;++i)			
			mkSelecao(prefixo->prefixo[i],quant);		
		
	}	

}
