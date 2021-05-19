#ifndef PROJ_BOT_H
#define PROJ_BOT_H
#include "estado.h"
#include "regras.h"

ESTADO bot_novo_jogo(ESTADO e, int dif);

ESTADO bot_play(ESTADO e, VALOR bot_peca);

int menorcomp(int* comps);

int minc(ESTADO e);

ESTADO bot_facil(ESTADO e);

int heuristica(ESTADO e, VALOR bot_peca);

void copyBoard(VALOR src[][8], VALOR dest[][8]);

int minimaxVal(ESTADO e, int tam_tree, VALOR bot_peca);

PONTO minimaxDecisao(ESTADO e, VALOR bot_peca);

#endif 
