#ifndef DIJKSTRA_H
#define DIJKSTRA_H

typedef struct No{
    int vertice;
    int peso;
    struct No *proximo;
} No;

typedef struct{
    No **lista;
    int num_vertices;
} GrafoLista;

int dijkstra(GrafoLista *g, int origem, int *dist, int *pred);
GrafoLista *criar_grafo(int n);
void adicionar_aresta(GrafoLista *g, int u, int v, int p);
void adicionar_arco(GrafoLista *g, int u, int v, int p);
void imprimir_grafo(GrafoLista *g);




#endif