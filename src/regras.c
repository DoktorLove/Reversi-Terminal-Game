#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lerficheiro.h"
#include "estado.h"
#include "stack.h"
#include "regras.h"

int* tem_vizinho(ESTADO e, int x, int y){
	VALOR oposto;
	int* len = malloc(9*sizeof(int));
	if (e.peca == VALOR_X) oposto = VALOR_O;
	else if (e.peca == VALOR_O) oposto = VALOR_X;

	for(int j=0; j<9;j++){
		len[j] = 0;
	}

	for (int i = 0; i < 9; i++){
		if(((x >= 0) && (y >= 0)) && ((x<8) && (y<8))){
			switch(i){
				case 0:
					if((e.grelha[x][y-1] == oposto) && ((x>=0)&&(y-1>=0)&&(x<8)&&(y-1<8))){						
						if(acabapeca(e,i,x,y)>0) len[0] = acabapeca(e,i,x,y);
					}
					break;
				case 1:
					if((e.grelha[x+1][y-1] == oposto) && ((x+1>=0)&&(y-1>=0)&&(x+1<8)&&(y-1<8))){
						if(acabapeca(e,i,x,y)>0) len[1] = acabapeca(e,i,x,y);
					}
					break;
				case 2:
					if((e.grelha[x+1][y] == oposto) && ((x+1>=0)&&(y>=0)&&(x+1<8)&&(y<8))){					
						if(acabapeca(e,i,x,y)>0) len[2] = acabapeca(e,i,x,y);
					}
					break;
				case 3:
					if((e.grelha[x+1][y+1] == oposto) && ((x+1>=0)&&(y+1>=0)&&(x+1<8)&&(y+1<8))){						
						if(acabapeca(e,i,x,y)>0) len[3] = acabapeca(e,i,x,y);
					}
					break;
				case 4:
					if((e.grelha[x][y+1] == oposto) && ((x>=0)&&(y+1>=0)&&(x<8)&&(y+1<8))){						
						if(acabapeca(e,i,x,y)>0) len[4]=acabapeca(e,i,x,y) ;
					}
					break;
				case 5:
					if((e.grelha[x-1][y+1] == oposto) && ((x-1>=0)&&(y+1>=0)&&(x-1<8)&&(y+1<8))){						
						if(acabapeca(e,i,x,y)>0) len[5]=acabapeca(e,i,x,y);
					}
					break;
				case 6:
					if((e.grelha[x-1][y] == oposto) && ((x-1>=0)&&(y>=0)&&(x-1<8)&&(y<8))){						
						if(acabapeca(e,i,x,y)>0) len[6]=acabapeca(e,i,x,y);
					}
					break;
				case 7:
					if((e.grelha[x-1][y-1] == oposto) && ((x-1>=0)&&(y-1>=0)&&(x-1<8)&&(y-1<8))){						
						if(acabapeca(e,i,x,y)>0) len[7]=acabapeca(e,i,x,y);
					}
					break;
				default: len[i] = 0;
			}
		}
	}

	return len;
}

int acabapeca(ESTADO e, int i, int x, int y){
	VALOR oposto;
	int len = 0;
	if (e.peca == VALOR_X) oposto = VALOR_O;
	else if (e.peca == VALOR_O) oposto = VALOR_X;

	int aux;
	int auy;

	switch(i){
		case 0:
			aux = x; auy = y;
			if(e.grelha[aux][auy-1] == oposto){
				auy--;
				while((e.grelha[aux][auy] == oposto) && ((aux>=0) && (auy>=0) && (aux<8) && (auy<8))){
					auy--; len++; 
				}			
				if((e.grelha[aux][auy] != e.peca) || ((aux<0) || (auy<0) || (aux>=8) || (auy>=8))) len = 0;
			}
			else len = 0;
			break;
		case 1:
			aux = x; auy = y;
			if(e.grelha[aux+1][auy-1] == oposto){
				auy--; aux++;
				while((e.grelha[aux][auy] == oposto) && ((aux>=0) && (auy>=0) && (aux<8) && (auy<8))){
					auy--; aux++; len++;			
				}
				if((e.grelha[aux][auy] != e.peca) || ((aux<0) || (auy<0) || (aux>=8) || (auy>=8))) len = 0;
			}
			else len = 0;
			break;
		case 2:
			aux = x; auy = y;
			if(e.grelha[aux+1][auy] == oposto){
				aux++; 
				while((e.grelha[aux][auy] == oposto) && ((aux>=0) && (auy>=0) && (aux<8) && (auy<8))){
					aux++; len++;							
				}
				if((e.grelha[aux][auy] != e.peca) || ((aux<0) || (auy<0) || (aux>=8) || (auy>=8))) len = 0;
			}
			else len = 0;
			break;
		case 3:
			aux = x; auy = y;
			if(e.grelha[aux+1][auy+1] == oposto){
				auy++; aux++;
				while((e.grelha[aux][auy] == oposto) && ((aux>=0) && (auy>=0) && (aux<8) && (auy<8))){
					auy++; aux++; len++;			
				}
				if((e.grelha[aux][auy] != e.peca) || ((aux<0) || (auy<0) || (aux>=8) || (auy>=8))) len = 0;
			}
			else len = 0;
			break;
		case 4:
			aux = x; auy = y;
			if (e.grelha[aux][auy+1] == oposto){	
				auy++;
				while((e.grelha[aux][auy] == oposto) && ((aux>=0) && (auy>=0) && (aux<8) && (auy<8))){
					auy++; len++;								
				}
				if((e.grelha[aux][auy] != e.peca) || ((aux<0) || (auy<0) || (aux>=8) || (auy>=8))) len = 0;
			}
			else len = 0;
			break;
		case 5:
			aux = x; auy = y;
			if(e.grelha[aux-1][auy+1] == oposto){	
				auy++; aux--;
				while((e.grelha[aux][auy] == oposto) && ((aux>=0) && (auy>=0) && (aux<8) && (auy<8))){
					auy++; aux--; len++; 			
				}
				if((e.grelha[aux][auy] != e.peca) || ((aux<0) || (auy<0) || (aux>=8) || (auy>=8))) len = 0;
			}
			else len = 0;
			break;
		case 6:
			aux = x; auy = y;
			if(e.grelha[aux-1][auy] == oposto){	
				aux--;	
				while((e.grelha[aux][auy] == oposto) && ((aux>=0) && (auy>=0) && (aux<8) && (auy<8))){
					aux--; len++;				
				}
				if((e.grelha[aux][auy] != e.peca) || ((aux<0) || (auy<0) || (aux>=8) || (auy>=8))) len = 0;
			}
			else len = 0;
			break;
		case 7:
			aux = x; auy = y;
			if(e.grelha[aux-1][auy-1] == oposto){
				auy--; aux--;
				while((e.grelha[aux][auy] == oposto) && ((aux>=0) && (auy>=0) && (aux<8) && (auy<8))){
					auy--; aux--; len++;				
				}
				if((e.grelha[aux][auy] != e.peca) || ((aux<0) || (auy<0) || (aux>=8) || (auy>=8))) len = 0;
			}
			else len = 0;
			break;
		default: len = 0;
	}

	return len;
}

int validBool(int* comps){
	int val = 1; 
	for (int l = 0; l < 8; l++){
		if(comps[l] > 0) val = 0;
	}
	return val;
}

ESTADO validmove(ESTADO e){
	int* len = malloc(8*sizeof(int));
	for(int i=0; i < 8; i++){
		for(int j=0; j < 8; j++){
			len = tem_vizinho(e,i,j);
			if((validBool(len) == 0) && (e.grelha[i][j] == VAZIA) && (e.grelha[i][j] != JOGAVEL)){
				e.grelha[i][j] = JOGAVEL;
			}
		}
	}

	return e;
}

////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////

int maiorcomp(int* comps){
	int max_comp = 0;
	for(int l = 0; l < 8; l++){
		if(max_comp < comps[l]) max_comp = comps[l];
	}
	return max_comp;
}

int maxc(ESTADO e){
	int max = 0;
	for(int m=0; m < 8; m++){
		for(int n=0; n < 8; n++){
			if((max < maiorcomp(tem_vizinho(e,m,n))) && (e.grelha[m][n] == VAZIA)){
				max = maiorcomp(tem_vizinho(e,m,n));				
			}
		}
	}
	return max;
}

ESTADO sugestao(ESTADO e){
	PONTO comps[32];
	int max1 = maxc(e);
	int max_comp = 0, x = -1, y = -1, count = 0;
	for(int i=0; i < 8; i++){
		for(int j=0; j < 8; j++){
			if((max_comp <= maiorcomp(tem_vizinho(e,i,j))) && (maiorcomp(tem_vizinho(e,i,j)) == max1) && (e.grelha[i][j] == VAZIA)){
				max_comp = maiorcomp(tem_vizinho(e,i,j));
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
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

int acabapeca_ind(ESTADO e, int i, int x, int y){
	VALOR oposto;
	int len = 0;
	if (e.peca == VALOR_X) oposto = VALOR_O;
	else if (e.peca == VALOR_O) oposto = VALOR_X;

	int aux;
	int auy;

	switch(i){
		case 0:
			aux = x; auy = y;
			if(e.grelha[aux][auy-1] == oposto){
				auy--;
				while((e.grelha[aux][auy] == oposto) && ((aux>=0) && (auy>=0) && (aux<8) && (auy<8))){
					auy--; len++; 
				}			
				if((e.grelha[aux][auy] != e.peca) || ((aux<0) || (auy<0) || (aux>=8) || (auy>=8))) len = 0;
			}
			else len = 0;
			break;
		case 1:
			aux = x; auy = y;
			if(e.grelha[aux+1][auy-1] == oposto){
				auy--; aux++;
				while((e.grelha[aux][auy] == oposto) && ((aux>=0) && (auy>=0) && (aux<8) && (auy<8))){
					auy--; aux++; len++;			
				}
				if((e.grelha[aux][auy] != e.peca) || ((aux<0) || (auy<0) || (aux>=8) || (auy>=8))) len = 0;
			}
			else len = 0;
			break;
		case 2:
			aux = x; auy = y;
			if(e.grelha[aux+1][auy] == oposto){
				aux++; 
				while((e.grelha[aux][auy] == oposto) && ((aux>=0) && (auy>=0) && (aux<8) && (auy<8))){
					aux++; len++;							
				}
				if((e.grelha[aux][auy] != e.peca) || ((aux<0) || (auy<0) || (aux>=8) || (auy>=8))) len = 0;
			}
			else len = 0;
			break;
		case 3:
			aux = x; auy = y;
			if(e.grelha[aux+1][auy+1] == oposto){
				auy++; aux++;
				while((e.grelha[aux][auy] == oposto) && ((aux>=0) && (auy>=0) && (aux<8) && (auy<8))){
					auy++; aux++; len++;			
				}
				if((e.grelha[aux][auy] != e.peca) || ((aux<0) || (auy<0) || (aux>=8) || (auy>=8))) len = 0;
			}
			else len = 0;
			break;
		case 4:
			aux = x; auy = y;
			if (e.grelha[aux][auy+1] == oposto){	
				auy++;
				while((e.grelha[aux][auy] == oposto) && ((aux>=0) && (auy>=0) && (aux<8) && (auy<8))){
					auy++; len++;								
				}
				if((e.grelha[aux][auy] != e.peca) || ((aux<0) || (auy<0) || (aux>=8) || (auy>=8))) len = 0;
			}
			else len = 0;
			break;
		case 5:
			aux = x; auy = y;
			if(e.grelha[aux-1][auy+1] == oposto){	
				auy++; aux--;
				while((e.grelha[aux][auy] == oposto) && ((aux>=0) && (auy>=0) && (aux<8) && (auy<8))){
					auy++; aux--; len++;				
				}
				if((e.grelha[aux][auy] != e.peca) || ((aux<0) || (auy<0) || (aux>=8) || (auy>=8))) len = 0;
			}
			else len = 0;
			break;
		case 6:
			aux = x; auy = y;
			if(e.grelha[aux-1][auy] == oposto){	
				aux--;	
				while((e.grelha[aux][auy] == oposto) && ((aux>=0) && (auy>=0) && (aux<8) && (auy<8))){
					aux--; len++;				
				}
				if((e.grelha[aux][auy] != e.peca) || ((aux<0) || (auy<0) || (aux>=8) || (auy>=8))) len = 0;
			}
			else len = 0;
			break;
		case 7:
			aux = x; auy = y;
			if(e.grelha[aux-1][auy-1] == oposto){
				auy--; aux--;
				while((e.grelha[aux][auy] == oposto) && ((aux>=0) && (auy>=0) && (aux<8) && (auy<8))){
					auy--; aux--; len++;				
				}
				if((e.grelha[aux][auy] != e.peca) || ((aux<0) || (auy<0) || (aux>=8) || (auy>=8))) len = 0;
			}
			else len = 0;
			break;
		default: len = 0;
	}

	return len;
}

ESTADO jogada(ESTADO e, int x, int y){
	int* len = malloc(8*sizeof(int));
	for (int j=0;j<8;j++){
		len[j] = acabapeca_ind(e,j,x,y);
	}
	int aux;
	int auy;
	int compasux;
	for(int l = 0; l<8; l++){
		switch(l){
				case 0:
					if(len[l] > 0){						
						compasux = 0; aux = x; auy = y;
						while(compasux < len[l]){
							e.grelha[aux][auy-1] = e.peca;
							auy--;
							compasux++;
						}
					}
					break;
				case 1:
					if(len[l] > 0){						
						compasux = 0; aux = x; auy = y;
						while(compasux < len[l]){
							e.grelha[aux+1][auy-1] = e.peca;
							auy--; aux++;
							compasux++;
						}
					}
					break;
				case 2:
					if(len[l] > 0){						
						compasux = 0; aux = x; auy = y;
						while(compasux < len[l]){
							e.grelha[aux+1][auy] = e.peca;
							aux++; 
							compasux++;
						}
					}
					break;
				case 3:
					if(len[l] > 0){						
						compasux = 0; aux = x; auy = y;
						while(compasux < len[l]){
							e.grelha[aux+1][auy+1] = e.peca;
							auy++; aux++;
							compasux++;
						}
					}
					break;
				case 4:
					if(len[l] > 0){						
						compasux = 0; aux = x; auy = y;
						while(compasux < len[l]){
							e.grelha[aux][auy+1] = e.peca;
							auy++;
							compasux++;
						}
					}
					break;
				case 5:
					if(len[l] > 0){						
						compasux = 0; aux = x; auy = y;
						while(compasux < len[l]){
							e.grelha[aux-1][auy+1] = e.peca;
							auy++; aux--;
							compasux++;
						}
					}
					break;
				case 6:
					if(len[l] > 0){						
						compasux = 0; aux = x; auy = y;
						while(compasux < len[l]){
							e.grelha[aux-1][auy] = e.peca;
							aux--;
							compasux++;
						}
					}
					break;
				case 7:
					if(len[l] > 0){						
						compasux = 0; aux = x; auy = y;
						while(compasux < len[l]){
							e.grelha[aux-1][auy-1] = e.peca;
							aux--; auy--;
							compasux++;
						}
					}
					break;
				
		}
	}

	return e;
}

////////////////////////////////////////////////////////

////////////////////////////////////////////////////////

PONTO* validmove_PONTO(ESTADO e){
	int* len = malloc(8*sizeof(int));
	int num_pontos = 0, i, j;
	for(i=0; i < 8; i++){
		for(j=0; j < 8; j++){
			len = tem_vizinho(e,i,j);
			if((validBool(len) == 0) && (e.grelha[i][j] == VAZIA) && (e.grelha[i][j] != JOGAVEL)){
				num_pontos++;
			}
		}
	}

	PONTO* pontos = malloc((num_pontos+1)*sizeof(PONTO));
	PONTO p;
	int l = 0;
	for(i=0; i < 8; i++){
		for(j=0; j < 8; j++){
			len = tem_vizinho(e,i,j);
			if((validBool(len) == 0) && (e.grelha[i][j] == VAZIA) && (e.grelha[i][j] != JOGAVEL)){
				p.coordx = i;
				p.coordy = j;
				pontos[l] = p;
				l++;
			}
		}
	}
	p.coordx = -1;
	p.coordy = -1;
	pontos[l] = p;

	return pontos;
}

int conta_pontos(PONTO* pontos){
	int l;
	while(pontos[l].coordx != -1){
		l++;
	}
	return l;
}

