#include <stdio.h>
#include <stdlib.h>
#include "bellman_ford.h"

GrafoListaPonderado* iniciarGrafoListaPonderado(int tamanho) {
    GrafoListaPonderado *g = (GrafoListaPonderado*) malloc(sizeof(GrafoListaPonderado));
    g->tamanho = tamanho;
    g->lista = (No**) malloc(tamanho * sizeof(No*));
    
    for (int i = 0; i < tamanho; i++) {
        g->lista[i] = NULL;
    }
    return g;
}

void addAresta(GrafoListaPonderado *g, int origem, int destino, int peso) {
    No *novoNo = (No*) malloc(sizeof(No));
    novoNo->dest = destino;
    novoNo->peso = peso;
    novoNo->proximo = g->lista[origem];
    g->lista[origem] = novoNo;
}

void liberarGrafo(GrafoListaPonderado *g) {
    for (int i = 0; i < g->tamanho; i++) {
        No *atual = g->lista[i];
        while (atual != NULL) {
            No *temp = atual;
            atual = atual->proximo;
            free(temp);
        }
    }
    free(g->lista);
    free(g);
}

int main() {
    int V1 = 4;
    GrafoListaPonderado *g1 = iniciarGrafoListaPonderado(V1);

    addAresta(g1, 0, 1, 4);
    addAresta(g1, 0, 2, 5);
    addAresta(g1, 1, 2, -2);
    addAresta(g1, 2, 3, 3);
    addAresta(g1, 1, 3, 2);

    int *dist1 = (int*) malloc(V1 * sizeof(int));
    int *pred1 = (int*) malloc(V1 * sizeof(int));
    int origem1 = 0;

    printf("Testando Grafo 1 (Sem ciclo negativo):\n");
    int resultado1 = bellman_ford(g1, origem1, dist1, pred1);

    if (resultado1 == 0) {
        printf("[ALERTA] Ciclo de custo negativo detectado!\n");
    } else {
        printf("Nenhum ciclo negativo encontrado. Menores distancias:\n");
        for (int i = 0; i < V1; i++) {
            printf("Vertice %d -> Distancia: %d\n", i, dist1[i]);
        }
    }

    free(dist1);
    free(pred1);
    liberarGrafo(g1);

    printf("\n----------------------------------------\n\n");

    int V2 = 4;
    GrafoListaPonderado *g2 = iniciarGrafoListaPonderado(V2);

    addAresta(g2, 0, 1, 1);
    addAresta(g2, 1, 2, -2);
    addAresta(g2, 2, 3, -1);
    addAresta(g2, 3, 1, -2);

    int *dist2 = (int*) malloc(V2 * sizeof(int));
    int *pred2 = (int*) malloc(V2 * sizeof(int));
    int origem2 = 0;

    printf("Testando Grafo 2 (Com ciclo negativo):\n");
    int resultado2 = bellman_ford(g2, origem2, dist2, pred2);

    if (resultado2 == 0) {
        printf("[ALERTA] Ciclo de custo negativo detectado no grafo!\n");
        
        int vertice_afetado = -1;
        for (int u = 0; u < V2; u++) {
            No *atual = g2->lista[u];
            while (atual != NULL) {
                int v = atual->dest;
                int peso = atual->peso;
                if (dist2[u] + peso < dist2[v]) {
                    vertice_afetado = v;
                    break;
                }
                atual = atual->proximo;
            }
            if (vertice_afetado != -1) break;
        }

        if (vertice_afetado != -1) {
            reconstruir_ciclo_negativo(pred2, vertice_afetado, V2);
        }
    } else {
        printf("Nenhum ciclo negativo encontrado. Menores distancias:\n");
        for (int i = 0; i < V2; i++) {
            printf("Vertice %d -> Distancia: %d\n", i, dist2[i]);
        }
    }

    free(dist2);
    free(pred2);
    liberarGrafo(g2);

    return 0;
}