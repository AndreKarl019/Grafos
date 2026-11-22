#include <stdio.h>
#include <stdlib.h>
#include "agm.h"

int main() {
    int V = 4;
    int E = 5;

    Aresta arestas[] = {
        {0, 1, 10},
        {0, 2, 6},
        {0, 3, 5},
        {1, 3, 15},
        {2, 3, 4}
    };

    kruskal(arestas, V, E);

    printf("\n");

    int **matriz = (int **)malloc(V * sizeof(int *));
    for (int i = 0; i < V; i++) {
        matriz[i] = (int *)malloc(V * sizeof(int));
        for (int j = 0; j < V; j++) {
            matriz[i][j] = 0;
        }
    }

    for (int i = 0; i < E; i++) {
        int u = arestas[i].u;
        int v = arestas[i].v;
        int p = arestas[i].peso;
        matriz[u][v] = p;
        matriz[v][u] = p;
    }

    prim(V, matriz);

    for (int i = 0; i < V; i++) {
        free(matriz[i]);
    }
    free(matriz);

    return 0;
}