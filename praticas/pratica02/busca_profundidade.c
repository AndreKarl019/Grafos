#include "busca_profundidade.h"
#include "grafo_lista.h"
#include <stdlib.h>

void dfs_recursiva(GrafoLista *g, int u, int *visitado) {
    visitado[u] = 1;

    No *n = g->lista[u];
    while (n != NULL) {
        int v = n->vertice;
        if (!visitado[v]) {
            dfs_recursiva(g, v, visitado);
        }
        n = n->proximo;
    }
}

int dfs_detecta_ciclo(GrafoLista *g, int u, int *visitado, int pai) {
    visitado[u] = 1;

    No *n = g->lista[u];
    while (n != NULL) {
        int v = n->vertice;
        if (!visitado[v]) {
            if (dfs_detecta_ciclo(g, v, visitado, u)) {
                return 1;
            }
        } else if (v != pai) {
            return 1;
        }
        n = n->proximo;
    }

    return 0;
}

int tem_ciclo(GrafoLista *g) {
    int *visitado = (int *)malloc(g->num_vertices * sizeof(int));
    for (int i = 0; i < g->num_vertices; i++) {
        visitado[i] = 0;
    }

    for (int i = 0; i < g->num_vertices; i++) {
        if (!visitado[i]) {
            if (dfs_detecta_ciclo(g, i, visitado, -1)) {
                free(visitado);
                return 1;
            }
        }
    }

    free(visitado);
    return 0;
}