#ifndef GRAFO_MATRIZ_H
#define GRAFO_MATRIZ_H

#define LIMITE 10

typedef struct {
    int adjacencia[LIMITE][LIMITE];
    int num_vertices;
} GrafoMatriz;

GrafoMatriz * criar_grafo_matriz(int n);
void inserir_aresta_matriz(GrafoMatriz *grafo, int u, int v);
void remover_aresta_matriz(GrafoMatriz *grafo, int u, int v);
void exibir_matriz(GrafoMatriz *grafo);
int sao_adjacentes_matriz(GrafoMatriz *grafo, int u, int v);
int grau_matriz(GrafoMatriz *grafo, int u);
void liberar_grafo_matriz(GrafoMatriz *grafo);

#endif