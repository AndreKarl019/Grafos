#include <stdio.h>
#include "grafo_lista.h"
#include "grafo_bipartido.h"

int main(){
    GrafoLista *grafo = criar_grafo(6);

    adicionar_aresta(grafo, 0, 3);
    adicionar_aresta(grafo, 0, 4);
    adicionar_aresta(grafo, 1, 4);
    adicionar_aresta(grafo, 1, 5);
    adicionar_aresta(grafo, 2, 3);
    adicionar_aresta(grafo, 2, 5);

    imprimir_grafo(grafo);

    printf("O grafo %s bipartido\n", eh_bipartido(grafo) ? "eh":"nao eh");

    Aresta arestas[6];
    arestas[0].u = 0; arestas[0].v = 3;
    arestas[1].u = 0; arestas[1].v = 4;
    arestas[2].u = 1; arestas[2].v = 4;
    arestas[3].u = 1; arestas[3].v = 5;
    arestas[4].u = 2; arestas[4].v = 3;
    arestas[5].u = 2; arestas[5].v = 5;

    printf("O grafo tem %i pares\n", emparelhamento_guloso(arestas, 6, 6));

    Aresta conexao[3];
    conexao[0].u = 0; conexao[0].v = 2;
    conexao[1].u = 0; conexao[1].v = 3;
    conexao[2].u = 1; conexao[2].v = 2;

    printf("O grafo tem %i pares\n", emparelhamento_guloso(conexao, 3, 4));

    return 0;
}