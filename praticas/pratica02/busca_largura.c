#include "busca_largura.h"
#include "grafo_lista.h"
#include <stdlib.h>


void bfs(GrafoLista *g, int origem, int *dist, int *pred) {
    for (int i = 0; i < g->num_vertices; i++) {
        dist[i] = -1;
        pred[i] = -1;
    }

    Fila *f = (Fila *)malloc(sizeof(Fila));
    f->dados = (int *)malloc(g->num_vertices * sizeof(int));
    f->capacidade = g->num_vertices;
    f->inicio = 0;
    f->fim = 0;
    f->tamanho = 0;
    dist[origem] = 0;
    f->dados[f->fim++] = origem;
    f->tamanho++;
    while (f->tamanho > 0) {
        int u = f->dados[f->inicio++];
        f->tamanho--;

        No *n = g->lista[u];
        while (n != NULL) {
            int v = n->vertice;
            if (dist[v] == -1) { 
                dist[v] = dist[u] + 1;
                pred[v] = u;
                f->dados[f->fim++] = v;
                f->tamanho++;
            }
            n = n->proximo;
        }
    }
    free(f->dados);
    free(f);
}

int eh_bipartido(GrafoLista *g) {
    int *cor = (int *)malloc(g->num_vertices * sizeof(int));
    for (int i = 0; i < g->num_vertices; i++) {
        cor[i] = 0; // 0 indica sem cor
    }

    Fila *f = (Fila *)malloc(sizeof(Fila));
    f->dados = (int *)malloc(g->num_vertices * sizeof(int));

    for (int i = 0; i < g->num_vertices; i++) {
        if (cor[i] == 0) { 
            cor[i] = 1;
            f->inicio = 0;
            f->fim = 0;
            f->tamanho = 0;
            
            f->dados[f->fim++] = i;
            f->tamanho++;

            while (f->tamanho > 0) {
                int u = f->dados[f->inicio++];
                f->tamanho--;

                No *n = g->lista[u];
                while (n != NULL) {
                    int v = n->vertice;
                    if (cor[v] == 0) {
                        cor[v] = (cor[u] == 1) ? 2 : 1; 
                        f->dados[f->fim++] = v;
                        f->tamanho++;
                    } else if (cor[v] == cor[u]) {
                        free(cor);
                        free(f->dados);
                        free(f);
                        return 0; 
                    }
                    n = n->proximo;
                }
            }
        }
    }

    free(cor);
    free(f->dados);
    free(f);
    return 1; 
}

int contar_componentes(GrafoLista *g) {
    int *visitado = (int *)malloc(g->num_vertices * sizeof(int));
    for (int i = 0; i < g->num_vertices; i++) {
        visitado[i] = 0;
    }

    int *dist_temp = (int *)malloc(g->num_vertices * sizeof(int));
    int *pred_temp = (int *)malloc(g->num_vertices * sizeof(int));
    int componentes = 0;

    for (int i = 0; i < g->num_vertices; i++) {
        if (!visitado[i]) {
            componentes++;
            bfs(g, i, dist_temp, pred_temp);

            for (int j = 0; j < g->num_vertices; j++) {
                if (dist_temp[j] != -1) {
                    visitado[j] = 1;
                }
            }
        }
    }

    free(visitado);
    free(dist_temp);
    free(pred_temp);
    return componentes;
}