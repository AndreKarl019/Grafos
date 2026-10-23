#include <stdio.h>
#include <string.h>
#include "grafo_lista_ponderado.h"
#include "menor_caminho.h"

int main()
{
    GrafoLista *grafo = criar_grafo(5);

    adicionar_aresta(grafo, 0, 1, 5);
    adicionar_aresta(grafo, 0, 2, 9);
    adicionar_aresta(grafo, 1, 3, 3);
    adicionar_aresta(grafo, 2, 3, 8);
    adicionar_aresta(grafo, 3, 4, 4);

    printf("Grafo nao orientado\n");
    imprimir_grafo(grafo);

    GrafoLista *grafo_nao_ponderado = criar_grafo(6);

    adicionar_aresta(grafo_nao_ponderado, 0, 1, 1);
    adicionar_aresta(grafo_nao_ponderado, 0, 2, 1);
    adicionar_aresta(grafo_nao_ponderado, 1, 3, 1);
    adicionar_aresta(grafo_nao_ponderado, 2, 3, 1);
    adicionar_aresta(grafo_nao_ponderado, 2, 4, 1);
    adicionar_aresta(grafo_nao_ponderado, 3, 5, 1);
    adicionar_aresta(grafo_nao_ponderado, 4, 5, 1);
    imprimir_grafo(grafo_nao_ponderado);

    printf("A distancia entre A e A eh: %i\n", bfs(grafo_nao_ponderado,0,0));
    printf("A distancia entre A e B,C eh: %i\n", bfs(grafo_nao_ponderado,0,1));
    printf("A distancia entre A e D,E eh: %i\n", bfs(grafo_nao_ponderado,0,3));
    printf("A distancia entre A e F eh: %i\n", bfs(grafo_nao_ponderado,0,5));

   return 0;
}