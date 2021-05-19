#ifndef PROJ_STACK_H
#define PROJ_STACK_H
#include "estado.h"

//Declaracao do nodo da lista-ligada
struct Node {
	ESTADO e;
	struct Node* next;
};
struct Node* top;

void push(ESTADO e);
int isEmpty();
ESTADO peek();
void pop();
void display();
void clean();

#endif //TESTES STACK H 