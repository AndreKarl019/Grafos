#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dag.h"

GrafoLista* criar_grafo(int num_vertices) {
    GrafoLista *g = (GrafoLista*) malloc(sizeof(GrafoLista));
    g->num_vertices = num_vertices;
    g->listas = (No**) malloc(num_vertices * sizeof(No*));

    for (int i = 0; i < num_vertices; i++) {
        g->listas[i] = NULL;
    }
    return g;
}


void inserir_aresta(GrafoLista *g, int origem, int destino) {
    if (origem < 0 || origem >= g->num_vertices || destino < 0 || destino >= g->num_vertices) return;

    No *novo = (No*) malloc(sizeof(No));
    novo->destino = destino;
    novo->proximo = g->listas[origem];
    g->listas[origem] = novo;
}

void imprimir_grafo(GrafoLista *g) {
    for (int i = 0; i < g->num_vertices; i++) {
        printf("Vertice %d:", i);
        No *atual = g->listas[i];
        while (atual != NULL) {
            printf(" -> %d", atual->destino);
            atual = atual->proximo;
        }
        printf("\n");
    }
}

int* ordenacao_topologica_kahn(GrafoLista *g, int *tamanho) {
    int V = g->num_vertices;
    int *grau_entrada = (int*) malloc(V * sizeof(int));
    memset(grau_entrada, 0, V * sizeof(int));

    for (int i = 0; i < V; i++) {
        No *atual = g->listas[i];
        while (atual != NULL) {
            grau_entrada[atual->destino]++;
            atual = atual->proximo;
        }
    }

    int *fila = (int*) malloc(V * sizeof(int));
    int inicio = 0, fim = 0;

    for (int i = 0; i < V; i++) {
        if (grau_entrada[i] == 0) {
            fila[fim++] = i;
        }
    }

    int *resultado = (int*) malloc(V * sizeof(int));
    int count = 0;

    while (inicio < fim) {
        int u = fila[inicio++];
        resultado[count++] = u;

        No *atual = g->listas[u];
        while (atual != NULL) {
            int v = atual->destino;
            grau_entrada[v]--;
            if (grau_entrada[v] == 0) {
                fila[fim++] = v;
            }
            atual = atual->proximo;
        }
    }

    free(grau_entrada);
    free(fila);

    if (count != V) {
        free(resultado);
        *tamanho = 0;
        return NULL;
    }

    *tamanho = count;
    return resultado;
}

static int dfs_util(GrafoLista *g, int v, int *estado, int *pilha, int *topo) {
    estado[v] = 1; 

    No *atual = g->listas[v];
    while (atual != NULL) {
        int vizinho = atual->destino;
        
        if (estado[vizinho] == 1) {
            return 0; 
        }
        
        if (estado[vizinho] == 0) {
            if (!dfs_util(g, vizinho, estado, pilha, topo)) {
                return 0;
            }
        }
        atual = atual->proximo;
    }

    estado[v] = 2; 
    pilha[(*topo)++] = v; 
    return 1;
}

int* ordenacao_topologica_dfs(GrafoLista *g, int *tamanho) {
    int V = g->num_vertices;
    int *estado = (int*) malloc(V * sizeof(int));
    memset(estado, 0, V * sizeof(int));

    int *pilha = (int*) malloc(V * sizeof(int));
    int topo = 0;

    for (int i = 0; i < V; i++) {
        if (estado[i] == 0) {
            if (!dfs_util(g, i, estado, pilha, &topo)) {
                free(estado);
                free(pilha);
                *tamanho = 0;
                return NULL;
            }
        }
    }

    int *resultado = (int*) malloc(V * sizeof(int));
    for (int i = 0; i < V; i++) {
        resultado[i] = pilha[V - 1 - i];
    }

    free(estado);
    free(pilha);
    *tamanho = V;
    return resultado;
}

int eh_dag(GrafoLista *g) {
    int tamanho = 0;
    int *ordem = ordenacao_topologica_kahn(g, &tamanho);
    
    if (ordem == NULL) {
        return 0; 
    }
    
    free(ordem);
    return 1;
}