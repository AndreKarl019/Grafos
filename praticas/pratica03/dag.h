#ifndef DAG_H
#define DAG_H

typedef struct No {
    int destino;
    struct No *proximo;
} No;

typedef struct GrafoLista {
    int num_vertices;
    No **listas; 
} GrafoLista;

GrafoLista* criar_grafo(int num_vertices);
void inserir_aresta(GrafoLista *g, int origem, int destino);
void imprimir_grafo(GrafoLista *g);

int eh_dag(GrafoLista *g);
int* ordenacao_topologica_kahn(GrafoLista *g, int *tamanho);
int* ordenacao_topologica_dfs(GrafoLista *g, int *tamanho);

#endif 