#include <stdlib.h>
#include "tps.h"

void grafo_para_tsp(int V, int **matriz_original, int **matriz_tsp) {
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (i == j) {
                matriz_tsp[i][j] = 0;
            } else if (matriz_original[i][j] > 0) {
                matriz_tsp[i][j] = 1;
            } else {
                matriz_tsp[i][j] = 2;
            }
        }
    }
}

static void permutar(int V, int **matriz, int *atual, int *visitado, int pos, int custo_atual, int *melhor_custo, int *ciclo_otimo) {
    if (pos == V) {
        int custo_total = custo_atual + matriz[atual[V - 1]][atual[0]];
        if (custo_total < *melhor_custo) {
            *melhor_custo = custo_total;
            for (int i = 0; i < V; i++) {
                ciclo_otimo[i] = atual[i];
            }
        }
        return;
    }

    for (int i = 1; i < V; i++) {
        if (!visitado[i]) {
            visitado[i] = 1;
            atual[pos] = i;
            int novo_custo = custo_atual + matriz[atual[pos - 1]][i];
            if (novo_custo < *melhor_custo) {
                permutar(V, matriz, atual, visitado, pos + 1, novo_custo, melhor_custo, ciclo_otimo);
            }
            visitado[i] = 0;
        }
    }
}

int tsp_forca_bruta(int V, int **matriz, int *ciclo_otimo) {
    int *atual = (int *)malloc(V * sizeof(int));
    int *visitado = (int *)malloc(V * sizeof(int));
    for (int i = 0; i < V; i++) {
        visitado[i] = 0;
    }

    atual[0] = 0;
    visitado[0] = 1;
    int melhor_custo = 999999;

    permutar(V, matriz, atual, visitado, 1, 0, &melhor_custo, ciclo_otimo);

    free(atual);
    free(visitado);
    return melhor_custo;
}

int tsp_vizinho_mais_proximo(int V, int **matriz, int *ciclo) {
    int *visitado = (int *)malloc(V * sizeof(int));
    for (int i = 0; i < V; i++) {
        visitado[i] = 0;
    }

    int atual = 0;
    ciclo[0] = 0;
    visitado[0] = 1;
    int custo_total = 0;

    for (int i = 1; i < V; i++) {
        int proximo = -1;
        int menor_peso = 999999;
        for (int j = 0; j < V; j++) {
            if (!visitado[j] && matriz[atual][j] < menor_peso) {
                menor_peso = matriz[atual][j];
                proximo = j;
            }
        }
        visitado[proximo] = 1;
        ciclo[i] = proximo;
        custo_total += menor_peso;
        atual = proximo;
    }
    custo_total += matriz[atual][0];

    free(visitado);
    return custo_total;
}

int tsp_insercao(int V, int **matriz, int *ciclo) {
    int *na_rota = (int *)malloc(V * sizeof(int));
    for (int i = 0; i < V; i++) {
        na_rota[i] = 0;
    }

    int tamanho_rota = 0;
    ciclo[tamanho_rota++] = 0;
    na_rota[0] = 1;

    int proximo = -1;
    int menor_peso = 999999;
    for (int j = 1; j < V; j++) {
        if (matriz[0][j] < menor_peso) {
            menor_peso = matriz[0][j];
            proximo = j;
        }
    }
    ciclo[tamanho_rota++] = proximo;
    na_rota[proximo] = 1;

    while (tamanho_rota < V) {
        int melhor_v = -1;
        int melhor_pos = -1;
        int menor_aumento = 999999;

        for (int j = 0; j < V; j++) {
            if (!na_rota[j]) {
                for (int k = 0; k < tamanho_rota; k++) {
                    int u = ciclo[k];
                    int w = ciclo[(k + 1) % tamanho_rota];
                    int aumento = matriz[u][j] + matriz[j][w] - matriz[u][w];
                    if (aumento < menor_aumento) {
                        menor_aumento = aumento;
                        melhor_v = j;
                        melhor_pos = k + 1;
                    }
                }
            }
        }

        for (int k = tamanho_rota; k > melhor_pos; k--) {
            ciclo[k] = ciclo[k - 1];
        }
        ciclo[melhor_pos] = melhor_v;
        na_rota[melhor_v] = 1;
        tamanho_rota++;
    }

    int custo_total = 0;
    for (int i = 0; i < V; i++) {
        custo_total += matriz[ciclo[i]][ciclo[(i + 1) % V]];
    }

    free(na_rota);
    return custo_total;
}