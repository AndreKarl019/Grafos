#ifndef COBERTURA_H
#define COBERTURA_H

typedef struct {
    int u, v;
} Aresta;

int eh_cobertura(int V, int E, Aresta *arestas, int *solucao);
void cobertura_minima_bt(int V, int E, Aresta *arestas, int *melhor_solucao, int *tamanho_minimo);
void cobertura_gulosa(int V, int E, Aresta *arestas, int *solucao);

#endif