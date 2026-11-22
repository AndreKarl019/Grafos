#ifndef BUSCA_PROFUNDIDADE_H
#define BUSCA_PROFUNDIDADE_H
#include "grafo_lista.h"


typedef struct {
    int *dados;
    int topo, capacidade;
} Pilha;


void dfs_recursiva(GrafoLista *g, int u, int *visitado);
int dfs_detecta_ciclo(GrafoLista *g, int u, int *visitado, int pai);
int tem_ciclo(GrafoLista *g);

#endif