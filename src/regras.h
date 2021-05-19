#ifndef PROJ_REGRAS_H
#define PROJ_REGRAS_H
#include "estado.h"

int* tem_vizinho(ESTADO e, int x, int y);

int acabapeca(ESTADO e, int i, int x, int y);

int validBool(int* comps);

ESTADO validmove(ESTADO e);

ESTADO sugestao(ESTADO e);

int maxc(ESTADO e);

int maiorcomp(int* comps);

ESTADO jogada(ESTADO e, int x, int y);

int acabapeca_ind(ESTADO e, int i, int x, int y);

PONTO* validmove_PONTO(ESTADO e);

int conta_pontos(PONTO* pontos);

#endif 
