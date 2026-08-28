#include <stdio.h>
#include <stdlib.h>
#include "grafo_lista.h"

void remover_direcao(GrafoLista *lista, int u, int v){
    No *atual = lista->adj[u];
    
    while(atual->prox!=NULL){
        if(atual->prox->destino == v){
            if(atual->prox->prox==NULL){
                atual->prox = NULL;
                return;
            }else{
                atual->prox = atual->prox->prox;
                return;
            }
        }
        atual = atual->prox;
    }
}



GrafoLista * criar_grafo_lista(int n){
    GrafoLista *lista = (GrafoLista*)malloc(sizeof(GrafoLista));
    lista->n = n;

    lista->adj = (No**)calloc(n, sizeof(No*));

    for(int i = 0; i<n;i++){
        lista->adj[i] = (No*)malloc(sizeof(No));
        lista->adj[i]->destino = i;
        lista->adj[i]->prox = NULL;
    }
    return lista;
}

void inserir_aresta_lista(GrafoLista *grafo, int u, int v){
    No *conexao1 = (No*)malloc(sizeof(No));
    conexao1->destino = v;
    conexao1->prox = NULL;
    No *conexao2 = (No*)malloc(sizeof(No));
    conexao2->destino = u;
    conexao2->prox = NULL;

    if(grafo->adj[u]->prox==NULL){
        grafo->adj[u]->prox = conexao1;
    }else{
        No *proximo1 = grafo->adj[u]->prox;
        while(proximo1->prox!=NULL){
            proximo1 = proximo1->prox;
        }
        proximo1->prox = conexao1;
    }

    if(grafo->adj[v]->prox==NULL){
        grafo->adj[v]->prox = conexao2;
    }else{
        No *proximo2 = grafo->adj[v]->prox;
        while(proximo2->prox!=NULL){
            proximo2 = proximo2->prox;
        }
        proximo2->prox = conexao2;
    }
}

void remover_aresta_lista(GrafoLista *grafo, int u, int v){
    remover_direcao(grafo, u, v);
    remover_direcao(grafo, u, v);
}

int grau_lista(GrafoLista *grafo, int u){
    int resultado = 0;
    No *proximo = grafo->adj[u]->prox;
    while(proximo!=NULL){
        proximo = proximo->prox;
        resultado++;
    }
    return resultado;
}

int sao_adjacentes_lista(GrafoLista *grafo, int u, int v){
    No *proximo = grafo->adj[u]->prox;
    while(proximo!=NULL){
        if(proximo->destino==v){
            return 1;
        }
        proximo = proximo->prox;
    }
    return 0;
}

void liberar_grafo_lista(GrafoLista *grafo){
    free(grafo);
}