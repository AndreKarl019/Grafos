#define _POSIX_C_SOURCE 199309L
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "hamiltoniano.h"
#include "tps.h"

void gerar_grafo(int V, int **matriz) {
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (i == j) {
                matriz[i][j] = 0;
            } else if (j == (i + 1) % V || j == (i + 2) % V) {
                matriz[i][j] = (rand() % 10) + 1;
                matriz[j][i] = matriz[i][j];
            } else {
                matriz[i][j] = 0;
                matriz[j][i] = 0;
            }
        }
    }
}

int main() {
    srand(time(NULL));
    int tamanhos[] = {5, 8, 10, 12};
    int num_testes = 4;

    for (int t = 0; t < num_testes; t++) {
        int V = tamanhos[t];
        int **matriz = (int **)malloc(V * sizeof(int *));
        int **matriz_tsp = (int **)malloc(V * sizeof(int *));
        for (int i = 0; i < V; i++) {
            matriz[i] = (int *)malloc(V * sizeof(int));
            matriz_tsp[i] = (int *)malloc(V * sizeof(int));
        }

        gerar_grafo(V, matriz);
        grafo_para_tsp(V, matriz, matriz_tsp);

        struct timespec inicio, fim;
        double tempo;

        int *caminho = (int *)malloc(V * sizeof(int));
        clock_gettime(CLOCK_MONOTONIC, &inicio);
        int tem_ham = encontrar_caminho_hamiltoniano_bt(V, matriz, caminho);
        clock_gettime(CLOCK_MONOTONIC, &fim);
        tempo = (fim.tv_sec - inicio.tv_sec) + (fim.tv_nsec - inicio.tv_nsec) / 1e9;

        printf("V = %d\n", V);
        if (tem_ham) {
            printf("  Caminho Hamiltoniano encontrado. Tempo: %.9f s\n", tempo);
        } else {
            printf("  Sem Caminho Hamiltoniano. Tempo: %.9f s\n", tempo);
        }

        int *ciclo_fb = (int *)malloc(V * sizeof(int));
        clock_gettime(CLOCK_MONOTONIC, &inicio);
        int custo_fb = tsp_forca_bruta(V, matriz_tsp, ciclo_fb);
        clock_gettime(CLOCK_MONOTONIC, &fim);
        tempo = (fim.tv_sec - inicio.tv_sec) + (fim.tv_nsec - inicio.tv_nsec) / 1e9;
        printf("  TSP Força Bruta - Custo: %d | Tempo: %.9f s\n", custo_fb, tempo);

        int *ciclo_vp = (int *)malloc(V * sizeof(int));
        clock_gettime(CLOCK_MONOTONIC, &inicio);
        int custo_vp = tsp_vizinho_mais_proximo(V, matriz_tsp, ciclo_vp);
        clock_gettime(CLOCK_MONOTONIC, &fim);
        tempo = (fim.tv_sec - inicio.tv_sec) + (fim.tv_nsec - inicio.tv_nsec) / 1e9;
        printf("  TSP Vizinho Mais Próximo - Custo: %d | Tempo: %.9f s\n", custo_vp, tempo);

        int *ciclo_ins = (int *)malloc(V * sizeof(int));
        clock_gettime(CLOCK_MONOTONIC, &inicio);
        int custo_ins = tsp_insercao(V, matriz_tsp, ciclo_ins);
        clock_gettime(CLOCK_MONOTONIC, &fim);
        tempo = (fim.tv_sec - inicio.tv_sec) + (fim.tv_nsec - inicio.tv_nsec) / 1e9;
        printf("  TSP Inserção - Custo: %d | Tempo: %.9f s\n", custo_ins, tempo);
        printf("----------------------------------------\n");

        free(caminho);
        free(ciclo_fb);
        free(ciclo_vp);
        free(ciclo_ins);
        for (int i = 0; i < V; i++) {
            free(matriz[i]);
            free(matriz_tsp[i]);
        }
        free(matriz);
        free(matriz_tsp);
    }

    return 0;
}