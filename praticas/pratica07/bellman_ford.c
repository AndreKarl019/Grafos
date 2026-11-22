#include <stdio.h>
#include <stdlib.h>
#include "bellman_ford.h"

int bellman_ford(GrafoListaPonderado *g, int origem, int *dist, int *pred) {
    int V = g->tamanho;

    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX / 2; 
        pred[i] = -1;
    }
    dist[origem] = 0;

    for (int i = 0; i < V - 1; i++) {
        for (int u = 0; u < V; u++) {
            No *atual = g->lista[u];
            while (atual != NULL) {
                int v = atual->dest;
                int peso = atual->peso;

                if (dist[u] + peso < dist[v]) {
                    dist[v] = dist[u] + peso;
                    pred[v] = u;
                }
                atual = atual->proximo;
            }
        }
    }

    int vertice_ciclo = -1;
    for (int u = 0; u < V; u++) {
        No *atual = g->lista[u];
        while (atual != NULL) {
            int v = atual->dest;
            int peso = atual->peso;

            if (dist[u] + peso < dist[v]) {
                pred[v] = u;
                vertice_ciclo = v;
                return 0; 
            }
            atual = atual->proximo;
        }
    }

    return 1; 
}

void reconstruir_ciclo_negativo(int *pred, int vertice_inicio, int tamanho) {
    int atual = vertice_inicio;

    for (int i = 0; i < tamanho; i++) {
        atual = pred[atual];
    }

    int inicio_ciclo = atual;
    printf("Ciclo negativo detectado:\n");
    printf("%d", inicio_ciclo);

    atual = pred[inicio_ciclo];
    while (atual != inicio_ciclo) {
        printf(" -> %d", atual);
        atual = pred[atual];
    }
    printf(" -> %d\n", inicio_ciclo);
}