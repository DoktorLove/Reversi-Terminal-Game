#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lerficheiro.h"
#include "estado.h"
#include "stack.h"

/**
-> As funções lerESTADO, escrESTADO e novo_jogo só funcionam para tabuleiros em modo Manual
*/ 

ESTADO lerESTADO(const char *file_name){
	FILE *fich1;
	ESTADO e;
	char buffer1[256];
	int a, b, dim1 = 132, dim2 = 134;
	
	fich1 = fopen(file_name,"r");
	rewind(fich1);

	fread(buffer1, 1, dim2, fich1);

	if (buffer1[2] == 'O') e.peca = VALOR_O;
	else e.peca = VALOR_X;

	if (buffer1[0] == 'M'){ 
		e.modo = 'M';
		buffer1[dim1 - 1] = '\0';
		
		int i = 4, conta = 0;
		for (int a = 0; a < 8; a++){
			for (int b = 0; b < 8; b++){
				switch (buffer1[(conta * 2) + i]) {
	                case 'O': {
	                    e.grelha[a][b] = VALOR_O;
	                    break;
	                }
	                case 'X': {
	                    e.grelha[a][b] = VALOR_X;
	                    break;
	                }
	                case '-': {
	                    e.grelha[a][b] = VAZIA;
	                    break;
	                }
	            }
				conta++;			
			}
		}
	}
	else{ 
		e.modo = 'A';
		e.dificuldade = buffer1[4] - '0';
		buffer1[dim2 - 1] = '\0';

		int i = 6, conta = 0;
		for (int a = 0; a < 8; a++){
			for (int b = 0; b < 8; b++){
				switch (buffer1[(conta * 2) + i]) {
	                case 'O': {
	                    e.grelha[a][b] = VALOR_O;
	                    break;
	                }
	                case 'X': {
	                    e.grelha[a][b] = VALOR_X;
	                    break;
	                }
	                case '-': {
	                    e.grelha[a][b] = VAZIA;
	                    break;
	                }
	            }
				conta++;			
			}
		}

	}
	fclose(fich1);

	return e;
}

int escrESTADO(ESTADO e, const char *file_name){
	FILE *fich;
	char buffer[254];
	
	fich = fopen(file_name,"w");
	rewind(fich);

	if (e.peca == VALOR_O) buffer[2] = 'O';
	else buffer[2] = 'X';

	if (e.modo == 'M'){
		buffer[0] = 'M';
		buffer[1] = ' ';

		
		buffer[3] = '\n';	

		int i = 4, a, b, conta = 0;
		for (int a = 0; a < 8; a++){
			for (int b = 0; b < 8; b++){
				switch (e.grelha[a][b]) {
	                case VALOR_O: {
	                    buffer[(conta * 2) + i] = 'O';
	                    break;
	                }
	                case VALOR_X: {
	                    buffer[(conta * 2) + i] = 'X';
	                    break;
	                }
	                case VAZIA: {
	                    buffer[(conta * 2) + i] = '-';
	                    break;
	                }
	            }
	            buffer[(conta * 2) + i + 1] = ' ';
				conta++;			
			}
		}

		buffer[(conta * 2) + i - 1] = '\0';
		for (i = 19; i < 130; i = i + 16){
			buffer[i] = '\n';
		}
	}
	else{
		buffer[0] = 'A';
		buffer[1] = ' ';
		buffer[3] = ' ';
		buffer[4] = e.dificuldade + '0';	
		buffer[5] = '\n';

		int i = 6, a, b, conta = 0;
		for (int a = 0; a < 8; a++){
			for (int b = 0; b < 8; b++){
				switch (e.grelha[a][b]) {
	                case VALOR_O: {
	                    buffer[(conta * 2) + i] = 'O';
	                    break;
	                }
	                case VALOR_X: {
	                    buffer[(conta * 2) + i] = 'X';
	                    break;
	                }
	                case VAZIA: {
	                    buffer[(conta * 2) + i] = '-';
	                    break;
	                }
	            }
	            buffer[(conta * 2) + i + 1] = ' ';
				conta++;			
			}
		}

		buffer[(conta * 2) + i - 1] = '\0';
		for (i = 21; i < 130; i = i + 16){
			buffer[i] = '\n';
		}
	}
	rewind(fich);
	fwrite(buffer , 1 , strlen(buffer) , fich);
	fclose(fich);

	return 0;
}

/**
Função que cria um novo jogo pvp 
*/
ESTADO novo_jogo(VALOR v){
	ESTADO e;

	if (v == VALOR_O) e.peca = VALOR_O;
	else if (v == VALOR_X) e.peca = VALOR_X;
	else e.peca = VAZIA;

	e.dificuldade = 0;
	e.modo = 'M';

	for (int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j++){
			e.grelha[i][j] = VAZIA;
		}
	}
	
	e.grelha[3][3] = VALOR_O;
	e.grelha[4][4] = VALOR_O;
	e.grelha[4][3] = VALOR_X;
	e.grelha[3][4] = VALOR_X;

	return e;
}



