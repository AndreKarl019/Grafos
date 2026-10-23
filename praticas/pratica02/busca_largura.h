#ifndef BUSCA_LARGURA_H
#define BUSCA_LARGURA_H
#include "grafo_lista.h"

// Fila (FIFO) para BFS
typedef struct {
    int *dados;
    int capacidade, inicio, fim, tamanho;
} Fila;


void bfs(GrafoLista *g, int origem, int *dist, int *pred);
int eh_bipartido(GrafoLista *g);
int contar_componentes(GrafoLista *g);


#endif