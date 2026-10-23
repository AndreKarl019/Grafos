#include <stdio.h>
#include "dijkstra.h"

int main(){
    GrafoLista *g = criar_grafo(6);
    adicionar_aresta(g, 0,1,4);
    adicionar_aresta(g, 0,2,2);
    adicionar_aresta(g, 1,2,1);
    adicionar_aresta(g, 1,3,5);
    adicionar_aresta(g, 1,4,4);
    adicionar_aresta(g, 2,3,8);
    adicionar_aresta(g, 2,4,10);
    adicionar_aresta(g, 3,5,1);
    adicionar_aresta(g, 3,4,2);
    adicionar_aresta(g, 4,5,3);

    int dist[6];
    int pred[6];

    int menor = dijkstra(g,0,dist,pred);

    printf("O menor caminho entre A e F eh: %i e ele percorre por:", menor);
    int aux = 5;
    printf("%i", aux);
    while(aux!=0){
        printf(" < %i", pred[aux]);
        aux = pred[aux];
    }

    return 0;
}