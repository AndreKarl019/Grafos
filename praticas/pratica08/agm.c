#include <stdio.h>
#include <stdlib.h>
#include "agm.h"

int find(DSU *d, int x) {
    if (d->pai[x] != x) {
        d->pai[x] = find(d, d->pai[x]);
    }
    return d->pai[x];
}

void unir(DSU *d, int x, int y) {
    int raiz_x = find(d, x);
    int raiz_y = find(d, y);

    if (raiz_x != raiz_y) {
        if (d->rank[raiz_x] < d->rank[raiz_y]) {
            d->pai[raiz_x] = raiz_y;
        } else if (d->rank[raiz_x] > d->rank[raiz_y]) {
            d->pai[raiz_y] = raiz_x;
        } else {
            d->pai[raiz_y] = raiz_x;
            d->rank[raiz_x]++;
        }
    }
}

int comparar_arestas(const void *a, const void *b) {
    Aresta *a1 = (Aresta *)a;
    Aresta *a2 = (Aresta *)b;
    return a1->peso - a2->peso;
}

void kruskal(Aresta *arestas, int V, int E) {
    qsort(arestas, E, sizeof(Aresta), comparar_arestas);

    DSU d;
    d.n = V;
    d.pai = (int *)malloc(V * sizeof(int));
    d.rank = (int *)malloc(V * sizeof(int));

    for (int i = 0; i < V; i++) {
        d.pai[i] = i;
        d.rank[i] = 0;
    }

    int custo_total = 0;
    printf("Arestas da AGM (Kruskal):\n");
    for (int i = 0; i < E; i++) {
        int u = arestas[i].u;
        int v = arestas[i].v;
        int peso = arestas[i].peso;

        if (find(&d, u) != find(&d, v)) {
            unir(&d, u, v);
            printf("%d - %d : %d\n", u, v, peso);
            custo_total += peso;
        }
    }
    printf("Custo total: %d\n", custo_total);

    free(d.pai);
    free(d.rank);
}

void prim(int V, int **matriz) {
    int *pai = (int *)malloc(V * sizeof(int));
    int *chave = (int *)malloc(V * sizeof(int));
    int *visitado = (int *)malloc(V * sizeof(int));

    for (int i = 0; i < V; i++) {
        chave[i] = 999999;
        visitado[i] = 0;
        pai[i] = -1;
    }

    chave[0] = 0;

    for (int i = 0; i < V - 1; i++) {
        int min = 999999, u = -1;
        for (int v = 0; v < V; v++) {
            if (!visitado[v] && chave[v] < min) {
                min = chave[v];
                u = v;
            }
        }

        if (u == -1) break;
        visitado[u] = 1;

        for (int v = 0; v < V; v++) {
            if (matriz[u][v] && !visitado[v] && matriz[u][v] < chave[v]) {
                pai[v] = u;
                chave[v] = matriz[u][v];
            }
        }
    }

    int custo_total = 0;
    printf("Arestas da AGM (Prim):\n");
    for (int i = 1; i < V; i++) {
        if (pai[i] != -1) {
            printf("%d - %d : %d\n", pai[i], i, matriz[pai[i]][i]);
            custo_total += matriz[pai[i]][i];
        }
    }
    printf("Custo total: %d\n", custo_total);

    free(pai);
    free(chave);
    free(visitado);
}