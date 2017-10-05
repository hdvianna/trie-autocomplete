

#include <stdio.h>

#include "interface.h"
#include "trie.h"
#include "arquivo.h"

const int  MAX_X = 80;
const int  MAX_Y = 25;
char *NOMEARQ = "palavras.txt";

void limpa(char *s) {		
	
	clearscreen(); /*Limpa a tela*/
	printf("Digite a palavra a ser pesquisada: ");	
	printf("%s",s);		
	
}

char *preenche(pNodo *raiz, char *s, char *istr) {
	
	char str[80];
	int i, q=0, tam, pos=35;	
	titem *vet;

	q=0;
	vet = selecao(raiz,&q); /*Seleciona as palavras semelhantes, e as adiciona em um vetor*/
	clearscreen(); /*Limpa a tela*/
	printf("Digite a palavra a ser pesquisada: ");
		

	if (!q)	{	
		printf("%s",s);	
		
		istr = newstring(strlen(s)); /*Caso a lista tenha um ou nenhum elemento*/
		strcpy(istr,s);

	} else {
		tam=q>MAX_Y?(MAX_Y-2):q;/*Se q > 24 então q=24 senão recebe q*/

		for (i=0;i<tam;i++) { /*Percorre o vetor escrevendo as palavras selecionadas*/
			if (i>0)
				printf("\t\t\t\t   ");
			printf("%s\n",vet[i].palavra);
		}		
		
		seltext(BG_WHITE, strlen(s) + pos, 0, (strlen(vet[0].palavra) - strlen(s)));

		if (q>MAX_Y) {
			sprintf(str,"\t\t\t\t   %i palavras da consulta foram omitidas", (q+1)-(MAX_Y-2));
			printf("\n%s",str);
			seltext(FG_WHITE, 0, MAX_Y-1, MAX_X-1); /*Muda a cor do texto da última linha*/	
		}

		istr = newstring(strlen(vet[0].palavra));
		strcpy(istr,vet[0].palavra);
	}	
	
	xy(strlen(s)+pos,0);
	
	return istr;
	
}

void salvaArquivo(char *strNome, pNodo *raiz) {	
	int q=0;	
	ARQUIVO *arq = abreArquivo(strNome,"w");
	titem *vet=selecao(raiz,&q);	

	for (int i=0;i<q;i++) /*Percorre o vetor escrevendo as palavras selecionadas*/
		escreveLinha(arq, vet[i].palavra);
	
	fechaArquivo(arq);	
	
}

int main() {

	char c='\0', op='c', *s,*istr, linha[MAXPRE]="";
	int i=0,tam, erro=0, ins=0, rem=0, tag=1, sk=0; 
	
	ARQUIVO *arq = abreArquivo(NOMEARQ,"r");	/*Abre o arquivo que contám a lista de palavras*/
	pNodo *raiz=inicializa(), *subraiz;
	
	screensize(MAX_X, MAX_Y);/*Define o tamanho da janela*/
	textcolor(FG_LIME); /*Cor do texto eh verde intenso*/

	if (arq) {
		
		while (leLinha(arq, linha)) {		
			if (linha[0])
				tag+=insere(raiz, linha, tag); /*Insere todas a palavras do arquivo na TRIE*/
		}
		
		while ((op!='f') && (op!='F')) { /*Enquanto f não for digitado*/
		
			switch(op) {
							
				case 'c':/*Continua pesquisando*/
					
					/*zera algumas variáveis*/
					c='\0';
					s=newstring(1);
					istr=newstring(1);
					s[0]='\0';
					tam=0;

					istr=preenche(raiz, s, istr);/*Escreve todas as palavras que iniciam pela substring s*/
					do { 		
					
						s=getkeys(s,&c,&sk,&erro,&tam); /*pega as palavras digitadas*/
						if ((!sk) && (c!=CR)) {																			
							subraiz=pegaNodo(raiz,s); /*pega o nodo onde se encontra a substring s*/
							istr=preenche(subraiz,s,istr); /*Escreve todas as palavra que se inicia pela substring s*/
						} else {
							switch(sk) {
								case DEL:																		
									limpa(s);
									istr = newstring(strlen(s));
									strcpy(istr,s);

									break;
							}
						}
					
					} while (c!=CR);
					
					clearscreen();
					if (istr[0]) { /*Se a palavra não for branco*/
						rem=(consulta(raiz,istr));
						ins=!rem;					
						printf("A palavra %s foi digitada, o que deseja fazer?\n",istr);
						seltext(FG_WHITE, 10, 0, strlen(istr));
						if (ins)
							printf("\n[I]nserir [C]ontinuar [F]im.");
						else
							printf("\n[R]emover [C]ontinuar [F]im.");						
					} else
						printf("Nenhuma palavra foi digitada.\n[C]ontinuar [F]im.");
					
					break;
					
				case 'i':
					if (ins) {
						if (insere(raiz,istr,tag)) { /*Insere uma palavra*/
							clearscreen();
							tag++;														
							printf("Insercao OK!\n[C]ontinuar [F]im");							
						} else
							printf("\nHouve um erro ao inserir a palavra. [C]ontinuar [F]im");
						ins = 0;					
						break;
					}
				case 'r':
					if (rem) {
						if (remove(raiz,istr)) { /*Remove uma palavra*/							
							clearscreen();
							printf("Remocao OK!\n[C]ontinuar [F]im.");							
						} else
							printf("\nHouve um erro ao remover a palavra. [C]ontinuar [F]im");
						rem = 0;
						break;
					}
				default:
					printf("\nOpcao Invalida!\nDigite outra opcao [C]ontinuar [F]im.");
			}
     op = getche();
		}
		fechaArquivo(arq);
		salvaArquivo(NOMEARQ, raiz);/*Salva as palavras no arquivo*/
		
	} else
		printf("ERRO: Arquivo '%s' nao encontrado!\n",NOMEARQ);

	return 0;

}
