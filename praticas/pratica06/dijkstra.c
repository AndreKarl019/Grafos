#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "dijkstra.h"

GrafoLista *criar_grafo(int n){
    GrafoLista *g = (GrafoLista *)malloc(sizeof(GrafoLista));
    g->num_vertices = n;
    g->lista = (No **)malloc(sizeof(No) * n);
    for (int i = 0; i < n; i++){
        g->lista[i] = NULL;
    }
    return g;
}

int dijkstra(GrafoLista *g, int origem, int *dist, int *pred){
    int visitado[g->num_vertices];
    memset(visitado, 0, sizeof(int)*g->num_vertices);
    memset(dist, -1, sizeof(int)*g->num_vertices);
    memset(pred, 0, sizeof(int)*g->num_vertices);
    int aux = origem;
    dist[origem] = 0;
    while(visitado[g->num_vertices-1]==0){
        visitado[aux] = 1;
        No *atual = g->lista[aux];
        while(atual!=NULL){
            if((dist[atual->vertice]>dist[aux]+atual->peso)||dist[atual->vertice]==-1){
                dist[atual->vertice] = dist[aux] + atual->peso;
                pred[atual->vertice] = aux;
            }
            atual = atual->proximo;
        }
        
        for(int i = 0; i<g->num_vertices; i++){
            if((visitado[aux])||((!visitado[i]&&dist[i]<dist[aux])&&(dist[i]!=-1))){
                aux = i;
            }
        }
    }
    return dist[g->num_vertices-1];
    
}


void adicionar_aresta(GrafoLista *g, int u, int v, int p){
    No *proximo = g->lista[u];
    No *no = (No *)malloc(sizeof(No));
    no->vertice = v;
    no->peso = p;
    no->proximo = proximo;
    g->lista[u] = no;

    proximo = g->lista[v];
    no = (No *)malloc(sizeof(No));
    no->vertice = u;
    no->peso = p;
    no->proximo = proximo;
    g->lista[v] = no;
}

void adicionar_arco(GrafoLista *g, int u, int v, int p){
    No *proximo = g->lista[u];
    No *no = (No *)malloc(sizeof(No));
    no->vertice = v;
    no->peso = p;
    no->proximo = proximo;
    g->lista[u] = no;
}

void imprimir_grafo(GrafoLista *g){
    printf("\n");
    for (int i = 0; i < g->num_vertices; i++){
        printf("%i: -> ", i + 1);
        No *no = g->lista[i];
        while (no != NULL){
            printf("(%i, %i) -> ", no->vertice + 1, no->peso);
            no = no->proximo;
        }
        printf("NULL\n");
    }
    printf("\n");
}