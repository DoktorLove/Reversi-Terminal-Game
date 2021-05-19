#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lerficheiro.h"
#include "estado.h"
#include "stack.h"
#include "regras.h"


ESTADO bot_novo_jogo(ESTADO e, int dif){
	e.peca = VALOR_X;
	e.modo = 'A';
	e.dificuldade = dif;

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

//////////////////////////////
/** Algoritmo Bot nivel 1
*/
//////////////////////////////

int menorcomp(int* comps){
	int min_comp = 10;
	for(int l = 0; l < 8; l++){
		if((min_comp > comps[l]) && (comps[l] > 0)) min_comp = comps[l];
	}
	return min_comp;
}

int minc(ESTADO e){
	int min = 10;
	for(int m=0; m < 8; m++){
		for(int n=0; n < 8; n++){
			if((min > menorcomp(tem_vizinho(e,m,n))) && (e.grelha[m][n] == VAZIA)){
				min = menorcomp(tem_vizinho(e,m,n));				
			}
		}
	}
	return min;
}

ESTADO bot_facil(ESTADO e){
	PONTO comps[32];
	int min1 = minc(e);
	int min_comp = 0, x = -1, y = -1, count = 0;
	for(int i=0; i < 8; i++){
		for(int j=0; j < 8; j++){
			if((min_comp <= menorcomp(tem_vizinho(e,i,j))) && (menorcomp(tem_vizinho(e,i,j)) == min1) && (e.grelha[i][j] == VAZIA)){
				min_comp = menorcomp(tem_vizinho(e,i,j));
				comps[count].coordx = i;
				comps[count].coordy = j;
				count++;
			}
		}
	}
	comps[count].coordx = x;
	comps[count].coordy = y;
	int r = rand() % count;

	x = comps[r].coordx;
	y = comps[r].coordy;
	e.grelha[x][y] = SUGESTAO;

	return e;
}

//////////////////////////////
/** Algoritmo Minimax
*/
//////////////////////////////

int heuristica(ESTADO e, VALOR bot_peca){
	int pontos_bot, pontos_jog;
	int* pontos = pontuacao(e);
	
	if(bot_peca == VALOR_X){
		pontos_bot = pontos[1];
		pontos_jog = pontos[0];
	} 
	else {
		pontos_bot = pontos[0];
		pontos_jog = pontos[1];
	}

	return (pontos_bot - pontos_jog);
}

void copyBoard(VALOR src[][8], VALOR dest[][8]){
	memcpy(dest, src, 8 * 8 * sizeof(char)); 
}

int minimaxVal(ESTADO e, int tam_tree, VALOR bot_peca){
	VALOR oposto;
	int num_moves = conta_pontos(validmove_PONTO(e));
	PONTO* pontos_val = validmove_PONTO(e);
	ESTADO novo = e;
	novo.peca = e.peca;
	novo.modo = e.modo;
	novo.dificuldade = e.dificuldade;	

	if (e.peca == VALOR_X) oposto = VALOR_O;
	else if (e.peca == VALOR_O) oposto = VALOR_X;
	
	if(tam_tree == 4 || tab_cheio(e) == 0){
		// quanto maior o tam_tree melhor a qualidade o bot, mas tambem sera maior o peso do programa
		// devido à recursividade, dai a escolha de 4
		return heuristica(e, bot_peca);
	}

	if(num_moves == 0){
		e.peca = oposto;
		return(minimaxVal(e, tam_tree + 1, bot_peca));
	}
	else{
		int melhor_move = -99999;
		if(bot_peca != e.peca){
			melhor_move = 99999;
		}

		for(int i = 0; i < num_moves; i++){
			
			char temp_grelha[8][8];
			copyBoard(e.grelha,novo.grelha);
			jogada(novo, pontos_val[i].coordx, pontos_val[i].coordy);

			int valor = minimaxVal(novo, tam_tree + 1, bot_peca);

			if (bot_peca == e.peca){
				if(valor > melhor_move) melhor_move = valor;
			}
			else{
				if(valor < melhor_move) melhor_move = valor;
			}
		}

		return melhor_move;
	}

	return -1;
}


PONTO minimaxDecisao(ESTADO e, VALOR bot_peca){
	VALOR oposto;
 	int num_moves = conta_pontos(validmove_PONTO(e)), x = 0, y = 0;
	PONTO* pontos_val = validmove_PONTO(e);
	PONTO final;
	ESTADO novo = e;
	novo.peca = e.peca;
	novo.modo = e.modo;
	novo.dificuldade = e.dificuldade;	
	
	if (e.peca == VALOR_X) oposto = VALOR_O;
	else if (e.peca == VALOR_O) oposto = VALOR_X;

	if(num_moves == 0){
		final.coordx = -1;
		final.coordy = -1;
		return final;
	}
	else{
		int melhor_move = -99999;

		for (int i = 0; i < num_moves; i++){
			
			char temp_grelha[8][8];
			copyBoard(e.grelha,novo.grelha);
			jogada(novo, pontos_val[i].coordx, pontos_val[i].coordy);
			
			int valor = minimaxVal(novo, 1, bot_peca);
			
			if (valor > melhor_move){
				melhor_move = valor;
				x = pontos_val[i].coordx;
				y = pontos_val[i].coordy;
			}
		}
		
		final.coordx = x;
		final.coordy = y;
	}
	
	return final;
}

////////////////////////////////////

ESTADO bot_play(ESTADO e, VALOR bot_peca){
	PONTO dif;
	int x = -1, y = -1;
	switch(e.dificuldade){
		case 1:
			e = bot_facil(e);
			for(int i=0; i < 8; i++){
				for(int j=0; j < 8; j++){
					if(e.grelha[i][j] == SUGESTAO){
						x = i;
						y = j;
					}
				}
			}
			e = limpaponto(e);
			break;
		
		case 2:	
			e = sugestao(e);
			for(int i=0; i < 8; i++){
				for(int j=0; j < 8; j++){
					if(e.grelha[i][j] == SUGESTAO){
						x = i;
						y = j;
					}
				}
			}
			e = limpaponto(e);
			break;

		case 3:
			dif = minimaxDecisao(e, bot_peca);
			x = dif.coordx;
			y = dif.coordy;
			break;
	}
	
	if(((x < 8) && (y < 8)) && ((x >= 0) && (y >= 0))){ 
	e.grelha[x][y] = e.peca;
	e = jogada(e,x,y); 
	}

	return e;
}


