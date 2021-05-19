//
// Created by pja on 28/02/2019.
//
#include <stdio.h>
#include "estado.h"
#include "lerficheiro.h"
#include "stack.h"
#include "regras.h"
#include <stdlib.h>

// exemplo de uma função para imprimir o estado (Tabuleiro)
void printa(ESTADO e)
{
    char c = ' ';
    
    for (int i = 0; i < 8; i++) {
        printf("                                            %d ",i+1);
        for (int j = 0; j < 8; j++) {
            switch (e.grelha[i][j]) {
                case VALOR_O: {
                    c = 'O';
                    break;
                }
                case VALOR_X: {
                    c = 'X';
                    break;
                }
                case VAZIA: {
                    c = '-';
                    break;
                }
                case JOGAVEL: {
                    c = '.';
                    break;
                }
                case SUGESTAO: {
                    c = '?';
                    break;
                }
            }

            printf("%c ", c);

        }
        printf("\n");
    }

}

int* pontuacao(ESTADO e){
    e = limpaponto(e);
    int* array_score = malloc(2 * sizeof(int));
    array_score[0] = 0;
    array_score[1] = 0;

    for (int a = 0; a < 8; a++){
        for (int b = 0; b < 8; b++){
            switch (e.grelha[a][b]) {
                case VALOR_O: {
                    array_score[0]++;
                    break;
                }
                case VALOR_X: {
                    array_score[1]++;
                    break;
                }
            }            
        }
    }

    return array_score;
}

ESTADO limpaponto(ESTADO e){
    for (int a = 0; a < 8; a++){
        for (int b = 0; b < 8; b++){
            if (e.grelha[a][b] == JOGAVEL || e.grelha[a][b] == SUGESTAO) e.grelha[a][b] = VAZIA;           
        }
    }

    return e;
}

int tab_cheio(ESTADO e){
    e = limpaponto(e);
    int v = 0;
    for (int a = 0; a < 8; a++){
        for (int b = 0; b < 8; b++){
            if (e.grelha[a][b] == VAZIA) v = 1;                
        }
    }
    return v;
}

char maiorscore(int* score){
    char c;
    if(score[0] < score[1]) c = 'X';
    else if(score[0] > score[1]) c = 'O';
    else c = 'E';

    return c;
}

int tem_jogadas(ESTADO e){
    e = limpaponto(e);
    int* len = malloc(8*sizeof(int));
    int v = 0;
    for(int i=0; i < 8; i++){
        for(int j=0; j < 8; j++){
            len = tem_vizinho(e,i,j);
            if((validBool(len) == 0) && (e.grelha[i][j] == VAZIA) && (e.grelha[i][j] != JOGAVEL)){
                v = 1;
            }
        }
    }

    return v;
}

int proximo_tem_jogadas(ESTADO e, int t){
    e = limpaponto(e);
    int v = 0;
    int* len = malloc(8*sizeof(int));
    
    if(t==1) v = 1;
    else {
        v = 0;
        for(int i=0; i < 8; i++){
            for(int j=0; j < 8; j++){
                len = tem_vizinho(e,i,j);
                if((validBool(len) == 0) && (e.grelha[i][j] == VAZIA) && (e.grelha[i][j] != JOGAVEL)){
                    v = 1;
                }
            }
        }
    }

    return v;

}