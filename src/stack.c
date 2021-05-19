#include <stdio.h>
#include "estado.h"
#include "lerficheiro.h"
#include <stdlib.h>
#include <curses.h>
#include <ncurses.h>
#include "stack.h"
#include <malloc.h>
#include <stdio.h>

//funcao que insere Estados no inicio
void push(ESTADO e)
{
	//cria um nodo temporario e aloca memoria
	struct Node* temp;
	temp = (struct Node*)malloc(sizeof(struct Node));

	//verifica se a stack esta cheia "out-of-memory"
	if(!temp)
	{
		printf("\nStack sobrelotada");
		exit(1);
	}
	//introduz o estado no respetivo campo em temp
	temp -> e = e;
	//direciona o apontador top para temp
	temp -> next = top;
	//torna temp o topo da stack
	top = temp;
}

//funcao que verifica se a stack esta vazia
int isEmpty(){
	return top == NULL;
}

//funcao que indica o elemento do topo da stack
ESTADO peek(){
	//verifica se esta vazia
	if(!isEmpty(top))
		return top -> e;
	//else
		//printf("\nStack vazia");
}

//funcao que remove o elemento no topo da stack
void pop(){
	struct Node* temp;
	//verifica se esta vazia
	if(top == NULL) {
		//printf("\nStack vazia");
	} else {
		//top fica com valor de temp
		temp = top;
		//o nodo seguinte passa a ser o topo
		top = top -> next;
		//liboerta a memoria d nodo de topo
		free(temp);
	}
}

//Mostra o conteudo da stack
void display(){
	struct Node* temp;
	//verifica se esta vazia
	if(top == NULL){
		printf("\nStack vazia");
	} else {
		temp = top;
		while (temp != NULL) {
			//imprime o valor do nodo
			printf("%d->", temp -> e.peca);
			//direciona o apontador para temp
			temp = temp -> next;
		}
	}
}

void clean(){
	while(top != NULL){
		pop();
	} 
}