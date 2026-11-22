#include <stdio.h>
#include <stdlib.h>
#include "grafo_matriz.h"


GrafoMatriz * criar_grafo_matriz(int n){
    GrafoMatriz *grafo = (GrafoMatriz *)calloc(n,sizeof(GrafoMatriz));
    grafo->num_vertices = n;
    return grafo;
}

void inserir_aresta_matriz(GrafoMatriz *grafo, int u, int v){
    grafo->adjacencia[u][v] = 1;
    grafo->adjacencia[v][u] = 1;
}

void remover_aresta_matriz(GrafoMatriz *grafo, int u, int v){
    grafo->adjacencia[u][v] = 0;
    grafo->adjacencia[v][u] = 0;
}

void exibir_matriz(GrafoMatriz *grafo){
    for(int i = 0; i<grafo->num_vertices;i++){
        for(int j = 0; j<grafo->num_vertices;j++){
            printf("%3i", grafo->adjacencia[i][j]);
        }
        printf("\n");
    }
}


int sao_adjacentes_matriz(GrafoMatriz *grafo, int u, int v){
    return grafo->adjacencia[u][v];
}

int grau_matriz(GrafoMatriz *grafo, int u){
    int resultado = 0;
    for(int i = 0; i<grafo->num_vertices;i++){
        if(grafo->adjacencia[u][i]==1){
            resultado++;
        }
    }
    return resultado;
}

void liberar_grafo_matriz(GrafoMatriz *grafo){
    free(grafo);
}