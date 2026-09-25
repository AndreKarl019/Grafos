#include <stdio.h>
#include <stdlib.h>
#include "dag.h"

void imprimir_ordem(const char *algoritmo, int *resultado, int tamanho) {
    if (resultado == NULL) {
        printf("[%s] Erro: O grafo contem um ciclo! Nao eh possivel ordenar.\n", algoritmo);
    } else {
        printf("[%s] Ordenacao Topologica: ", algoritmo);
        for (int i = 0; i < tamanho; i++) {
            printf("%d ", resultado[i]);
        }
        printf("\n");
    }
}

int main() {
    printf(" Testando com um DAG\n");
    GrafoLista *dag = criar_grafo(6);
    inserir_aresta(dag, 5, 2);
    inserir_aresta(dag, 5, 0);
    inserir_aresta(dag, 4, 0);
    inserir_aresta(dag, 4, 1);
    inserir_aresta(dag, 2, 3);
    inserir_aresta(dag, 3, 1);

    printf("\nLista de Adjacencia do DAG:\n");
    imprimir_grafo(dag);

    printf("\nVerificacao de DAG: %s\n", eh_dag(dag) ? "Eh um DAG" : "Nao eh um DAG");

    int tam_kahn = 0;
    int *res_kahn = ordenacao_topologica_kahn(dag, &tam_kahn);
    imprimir_ordem("Kahn", res_kahn, tam_kahn);
    free(res_kahn);

    int tam_dfs = 0;
    int *res_dfs = ordenacao_topologica_dfs(dag, &tam_dfs);
    imprimir_ordem("DFS", res_dfs, tam_dfs);
    free(res_dfs);


    printf("\n\nTestando grafo com Ciclo \n");

    GrafoLista *com_ciclo = criar_grafo(3);
    inserir_aresta(com_ciclo, 0, 1);
    inserir_aresta(com_ciclo, 1, 2);
    inserir_aresta(com_ciclo, 2, 0);

    printf("\nLista de Adjacencia do Grafo Ciclico:\n");
    imprimir_grafo(com_ciclo);

    printf("\nVerificacao de DAG: %s\n", eh_dag(com_ciclo) ? "Eh um DAG" : "Nao eh um DAG");

    res_kahn = ordenacao_topologica_kahn(com_ciclo, &tam_kahn);
    imprimir_ordem("Kahn", res_kahn, tam_kahn);

    res_dfs = ordenacao_topologica_dfs(com_ciclo, &tam_dfs);
    imprimir_ordem("DFS", res_dfs, tam_dfs);


    return 0;
}