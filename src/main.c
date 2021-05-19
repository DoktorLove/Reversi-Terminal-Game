#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <ncurses.h>
#include <string.h>
#include <unistd.h>
#include "estado.h"
#include "lerficheiro.h"
#include "stack.h"
#include "regras.h"
#include "bot.h"


int main()
{
    ESTADO e;
    e = novo_jogo(VAZIA);
    VALOR bot_peca = VAZIA;
    char escolha = 'a', esc, inic, nomefich[32];
    int x,y, valor, dif;
    
    while (escolha != 'b'){
        
        CICLOBOT:if(e.modo == 'A' && e.peca == bot_peca){
            e = limpaponto(e);
            e = bot_play(e, bot_peca);
            if (e.peca == VALOR_X) e.peca = VALOR_O;
            else if (e.peca == VALOR_O) e.peca = VALOR_X;
            push(e);
        }
        
        char p;
        if (e.peca == VALOR_X) p = 'X';
        else if (e.peca == VALOR_O) p = 'O';
        else p = '-';

        if(tab_cheio(e) == 0) printf("              Acabou o jogo. Ganhou o jogador com: %c\n", maiorscore(pontuacao(e)));
        else if(tem_jogadas(e)==0 && e.peca != VAZIA) {
                printf("              O jogador com %c nao tem jogadas possiveis\n", p);
                if(e.peca == VALOR_X) e.peca = VALOR_O; 
                else if (e.peca == VALOR_O) e.peca = VALOR_X;
        }
        if (proximo_tem_jogadas(e,tem_jogadas(e)) == 0 && e.peca != VAZIA) printf("              Acabou o jogo. Ganhou o jogador com: %c\n", maiorscore(pontuacao(e)));
        else if (proximo_tem_jogadas(e,tem_jogadas(e)) == 1 && e.peca != VAZIA && (e.modo == 'A') && (e.peca == bot_peca)) goto CICLOBOT; 

        printf("              E a vez do jogador com: %c | ", p);
       
        int* score = pontuacao(e);
        if(e.modo == 'M'){
            printf("Pecas X: %d | Pecas O: %d | Modo PvsP\n \n", score[1], score[0] );
        }
        else{
            printf("Pecas X: %d | Pecas O: %d | Modo PvsBOT | Dificuldade: %d\n \n", score[1], score[0], e.dificuldade);
        }
        printf("                                              1 2 3 4 5 6 7 8\n");
        printa(e);

        printf("\n");
        printf(" ");
        printf("L. Ler Ficheiro | ");
        printf("E. Escrever no Ficheiro | ");
        printf("J. Inserir coordenada | ");
        printf("S. Posicoes validas | ");
        printf("H. Sugestao | ");
        printf("N. Novo jogo PvsP | ");
        printf("A. Novo jogo PvsBOT | ");
        printf("U. Undo | ");
        printf("Q. Sair do programa\n");
        
        printf("                  ");
        scanf( " %c", &escolha );

        switch (escolha){
            case 'J' : 
                e = limpaponto(e);
                scanf("%d %d", &x, &y);
                e = validmove(e);
                if ((x > 0 && x <= 8) && (y > 0 && y <= 8) && (e.grelha[x-1][y-1] == JOGAVEL)) {
                    e = limpaponto(e);
                    if (e.peca == VALOR_O) {
                        e.grelha[x - 1][y - 1] = e.peca;
                        e = jogada(e,x-1,y-1);
                        e.peca = VALOR_X;                     
                        if(e.modo == 'M') push(e);
                    }
                    else if (e.peca == VALOR_X) {
                        e.grelha[x - 1][y - 1] = e.peca;
                        e = jogada(e,x-1,y-1);
                        e.peca = VALOR_O;
                        if(e.modo == 'M') push(e);
                    }
                    else printf("Comece um novo jogo ou carregue um ficheiro\n");
                }
                else printf("A coordenada que inseriu nao e valida\n");
                e = limpaponto(e);
                break; 
            
            case 'N' : 
                scanf(" %c", &esc); 
                VALOR nova;
                if (esc == 'O') {
                    clean();
                    nova = VALOR_O;
                    e = novo_jogo(nova);
                    push(e);
                }
                else if (esc == 'X') {
                    clean();
                    nova = VALOR_X;
                    e = novo_jogo(nova);
                    push(e);
                }
                
                break;
            
            case 'A' :
                scanf(" %c %d", &inic, &dif);
                if (inic == 'O'){ 
                    clean();
                    bot_peca = VALOR_O;
                    e = limpaponto(e);
                    e = bot_novo_jogo(e,dif);
                    e = limpaponto(e);
                    push(e);
                }
                else if(inic == 'X'){                   
                    clean();
                    bot_peca = VALOR_X;
                    e = limpaponto(e);
                    e = bot_novo_jogo(e,dif);
                    e = limpaponto(e);
                    push(e);
                }
                else printf("Inseriu uma peca errada");
                break;
            
            case 'U' : 
                pop();
                e = peek();         
                break;
            
            case 'L' : 
                scanf("%s", nomefich);
                if (strcmp(nomefich,"tabuleiro.txt")==0){
                    e = lerESTADO(nomefich);
                    clean();
                    push(e);
                    if(e.modo == 'A'){
                        if (e.peca == VALOR_X) bot_peca = VALOR_O;
                        else if (e.peca == VALOR_O) bot_peca = VALOR_X;
                    } 
                }
                else printf("Inseriu um nome de um ficheiro invalido");
                break;
            
            case 'E' : 
                scanf("%s", nomefich);
                if (strcmp(nomefich,"tabuleiro.txt")==0){    
                    e = limpaponto(e);
                    escrESTADO(e, nomefich); 
                }
                else printf("Inseriu um nome de um ficheiro invalido");
                break;
            
            case 'S' :
                e = limpaponto(e);
                e = validmove(e);
                break;

            case 'H' :
                e = limpaponto(e);
                e = sugestao(e);
                break;

            case 'Q' : exit(0);
               
            default : printf("Opcao invalida"); 
        }
        getch();
    }
    return 0;
}