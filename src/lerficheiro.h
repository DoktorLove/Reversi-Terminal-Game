#ifndef PROJ_LERFICHEIRO_H
#define PROJ_LERFICHEIRO_H
#include "estado.h"

ESTADO lerESTADO(const char *file_name);

int escrESTADO(ESTADO e, const char *file_name);

ESTADO novo_jogo(VALOR v);


#endif 