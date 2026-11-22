#include <stdio.h>
#include <string.h>
#include "grafo_matriz.h"

int eh_hamiltoniano(GrafoMatriz *grafo, int *caminho){
    int visitado[grafo->num_vertices];
    memset(visitado, 0, sizeof(visitado));

    for(int i = 0; i<grafo->num_vertices; i++){
        int v = caminho[i];
        if(visitado[v]) return 0;
        visitado[v] = 1;
    }

    for(int i = 0; i<grafo->num_vertices-1; i++){
        int u = caminho[i];
        int v = caminho[i+1];
        if(grafo->adjacencia[u][v]==0) return 0;
    }

    return 1;
}

int main(){
    GrafoMatriz grafo;

    inicializar(&grafo, 6);

    inserir_aresta(&grafo,0,1);
    inserir_aresta(&grafo,0,2 );
    inserir_aresta(&grafo,1,2);
    inserir_aresta(&grafo,1,3);
    inserir_aresta(&grafo,2,3);
    inserir_aresta(&grafo,2,4);
    inserir_aresta(&grafo,3,4);
    inserir_aresta(&grafo,3,5);
    inserir_aresta(&grafo,4,5);

    int caminho[LIMITE];

    caminho[0] = 0;
    caminho[1] = 1;
    caminho[2] = 2;
    caminho[3] = 3;
    caminho[4] = 4;
    caminho[5] = 5;

    printf("O caminho A->B->C->D->E->F eh hamiltoniano? %i\n", eh_hamiltoniano(&grafo, caminho));

    return 0;
}