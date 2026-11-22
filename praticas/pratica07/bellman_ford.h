#ifndef BELLMAN_FORD_H
#define BELLMAN_FORD_H

typedef struct No{
    int dest;
    struct No *proximo;
    int peso;
} No;

typedef struct GrafoListaPonderado{
    No **lista;
    int tamanho;
} GrafoListaPonderado;



int bellman_ford(GrafoListaPonderado *g, int origem, int *dist, int *pred);

void reconstruir_ciclo_negativo(int *pred, int vertice_inicio, int tamanho);

#endif