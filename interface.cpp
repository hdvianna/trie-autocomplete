
#include "interface.h"

int __FOREGROUND = FG_WHITE;
int __BACKGROUND = BG_BLACK;

char *newstring(unsigned int tam) { /*Aloca uma região em memória para uma string*/	
	
	return (char*) malloc(sizeof(char) * tam);

}

char *getkeys(char *strbuffer, char *key, int *sk, int *erro, int *len) {
	/*Esta função pega uma tecla digita e coloca no final de uma
	string "strbuffer"*/

	*key = getche();
	*sk = 0;
	switch(*key) {
		case CR:/*Caso caracter pressionado tenha sido ENTER*/
			break;
		case BS:/*Caso caracter pressionado tenha siso o backspace*/
			if ((*len) > 0 ) {	/*apaga uma letra da string*/
				(*len)--;
				if ((*len))
					strbuffer = (char *) realloc(strbuffer,sizeof(char) * (*len));
				strbuffer[(*len)] = '\0';
			}
			break;
		case SK: /*Tecla especial*/
			*key = getche();/*Qdo uma tecla especial é lida, deve ser feita mais uma leitura do teclado*/
			
			switch(*key) {
				case 'S':/*Caso for DEL*/
					*sk = DEL;					
					break;
			}

			break;
		default:/*adiciona a letra digitada*/
			(*len)++;
			strbuffer = (char *) realloc(strbuffer,sizeof(char) * (*len));

			if (!strbuffer) 
				return 0; 
			
			strbuffer[(*len)-1] = *key;
			strbuffer[(*len)] = '\0';
	}	
	
	return strbuffer;	

}

void clearscreen() {

	#if SO == WIN
		system("cls");/*Limpa tela no dos*/
	#elif SO == UNIX
		system("clear");/*limpa tela no unix*/
	#endif

}

void xy(int x, int y) { /*Posiciona o cursor em uma posição da tela, semelhante ao gotoxy*/

	#if SO == WIN 
        COORD c;
        c.X = x;
        c.Y = y;
        SetConsoleCursorPosition (GetStdHandle(STD_OUTPUT_HANDLE), c);
	#elif SO == UNIX
		move(x, y); 
	#endif

}

void textbackground(WORD wColor) {	/*Cor de fundo do console*/
	
	__BACKGROUND = wColor;
	#if SO == WIN  
		SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE)
								, __BACKGROUND | __FOREGROUND);		
	#endif
}

void textcolor(WORD wColor) {	/*Cor da fonte*/
	
	__FOREGROUND = wColor;			
	#if SO == WIN  		
		SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), 
			__BACKGROUND | __FOREGROUND);
	#endif
}

void seltext(WORD wColor, int x, int y, int len) {	/*Faz a "seleção" do texto no console*/
	
	COORD coord; 
	DWORD cWritten;

	coord.X = x;
	coord.Y = y;

	FillConsoleOutputAttribute( 
		GetStdHandle(STD_OUTPUT_HANDLE), // alça do buffer da tela
		wColor,           // color que será preenchido
		len,			  // número de "células" preenchidas
		coord,            // coordenada inicial
		&cWritten);       // sei lá o q eh isso!
}

void screensize(int x, int y) { /*Configura o tamanho do buffer do console
								funciona apenas em sistemas NT (200, XP, etc)*/
	
	COORD coord;
	coord.X = x;
	coord.Y = y;
	
	SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), coord);

}

int wherex() { /*pega a posição do cursor em X*/
	
	#if SO == WIN  	
		CONSOLE_SCREEN_BUFFER_INFO info;
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
		return info.dwCursorPosition.X;
	#elif
		return 0
	#endif
}

int wherey() { /*pega a posição do cursor em Y*/
	
	#if SO == WIN  	
		CONSOLE_SCREEN_BUFFER_INFO info;
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
		return info.dwCursorPosition.Y - 2;
	#elif
		return 0;
	#endif
}
