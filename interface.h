

#include <stdlib.h>
#include <string.h>

#ifndef INTERFACE

	#define INTERFACE
	#define CR 13
	#define BS 8
	#define SK -32 /*Special Key*/
	#define	DEL 308
	#define SO WIN

	#if SO == WIN
		#include <conio.h>
        #include <windows.h>
	#elif SO == UNIX
		#include <curses.h>
	#endif	

	const WORD FG_LIME  = FOREGROUND_INTENSITY | FOREGROUND_GREEN;
	const WORD FG_WHITE = FOREGROUND_INTENSITY | FOREGROUND_BLUE |
                        FOREGROUND_RED| FOREGROUND_GREEN;
	const WORD FG_BLACK = 0;
	const WORD BG_LIME  = BACKGROUND_INTENSITY | BACKGROUND_GREEN;
	const WORD BG_WHITE = BACKGROUND_INTENSITY | BACKGROUND_BLUE |
                        BACKGROUND_RED| BACKGROUND_GREEN;
	const WORD BG_BLACK = 0;	

	char *newstring(unsigned int tam);
	char *getkeys(char *strbuffer, char *key, int *sk, int *erro, int *len);
	
	void clearscreen();
	void xy(int x, int y);
	void textbackground(WORD wColor);
	void textcolor(WORD wColor);		
	void seltext(WORD wColor, int x, int y, int len);	
	void screensize(int x, int y);
	int wherex();
	int wherey();	

#endif
