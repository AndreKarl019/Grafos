#include <stdio.h>
#include <stdlib.h>
#include "grafo_lista.h"
#include "busca_largura.h"
#include "busca_profundidade.h"

int main() {
    int num_vertices = 7;
    GrafoLista *g = criar_grafo(num_vertices);

    adicionar_aresta(g, 0, 1);
    adicionar_aresta(g, 1, 2);
    adicionar_aresta(g, 2, 0);
    adicionar_aresta(g, 2, 3);

    adicionar_aresta(g, 4, 5);


    printf("=== TESTE DE BUSCA EM LARGURA (BFS) ===\n");
    
    int *dist = (int *)malloc(num_vertices * sizeof(int));
    int *pred = (int *)malloc(num_vertices * sizeof(int));

    bfs(g, 0, dist, pred);

    printf("Resultados da BFS (Origem: 0):\n");
    for (int i = 0; i < num_vertices; i++) {
        printf("Vertice %d -> Distancia: %d, Predecessor: %d\n", i, dist[i], pred[i]);
    }

    printf("\nComponentes (BFS): %d\n", contar_componentes(g));
    printf("eh Bipartido (BFS)? %s\n", eh_bipartido(g) ? "Sim" : "Nao");

    printf("\n=== TESTE DE BUSCA EM PROFUNDIDADE (DFS) ===\n");

    int *visitado = (int *)malloc(num_vertices * sizeof(int));
    for (int i = 0; i < num_vertices; i++) {
        visitado[i] = 0;
    }

    printf("Executando DFS recursiva a partir do vertice 0...\n");
    dfs_recursiva(g, 0, visitado);

    printf("Vertices visitados apos a DFS a partir do 0:\n");
    for (int i = 0; i < num_vertices; i++) {
        printf("Vertice %d: %s\n", i, visitado[i] ? "Visitado" : "Nao Visitado");
    }

    printf("\nTem ciclo (DFS)? %s\n", tem_ciclo(g) ? "Sim" : "Nao");

    return 0;
}