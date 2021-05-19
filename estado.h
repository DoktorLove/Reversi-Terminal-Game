//
// Created by pja on 27/02/2019.
//



#ifndef PROJ_ESTADO_H
#define PROJ_ESTADO_H



/**
estado.h
Definição do estado i.e. tabuleiro. Representação matricial do tabuleiro.
*/


// definição de valores possiveis no tabuleiro
typedef enum {VAZIA, JOGAVEL, VALOR_X, VALOR_O, SUGESTAO} VALOR;

// struct com as coordenadas de um ponto
typedef struct ponto {
	int coordx;
	int coordy;
} PONTO;

/**
Estrutura que armazena o estado do jogo
*/
typedef struct estado {
    VALOR peca; // peça do jogador que vai jogar!
    VALOR grelha[8][8];
    int dificuldade;
    char modo; // modo em que se está a jogar! 0-> manual, 1-> contra computador
} ESTADO;


void printa(ESTADO);

int* pontuacao(ESTADO e);

ESTADO limpaponto(ESTADO e);

int tab_cheio(ESTADO e);

char maiorscore(int* score);

int tem_jogadas(ESTADO e);

int proximo_tem_jogadas(ESTADO e, int t);

#endif //PROJ_ESTADO_H