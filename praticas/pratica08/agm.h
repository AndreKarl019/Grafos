#ifndef AGM_H
#define AGM_H

typedef struct {
    int *pai, *rank;
    int n;
} DSU;

typedef struct {
    int u, v, peso;
} Aresta;

int find(DSU *d, int x);
void unir(DSU *d, int x, int y);
void kruskal(Aresta *arestas, int V, int E);
void prim(int V, int **matriz);

#endif