#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "cobertura.h"

void gerar_grafo_aleatorio(int V, int E, Aresta *arestas) {
    int count = 0;
    while (count < E) {
        int u = rand() % V;
        int v = rand() % V;
        if (u != v) {
            int existe = 0;
            for (int i = 0; i < count; i++) {
                if ((arestas[i].u == u && arestas[i].v == v) || (arestas[i].u == v && arestas[i].v == u)) {
                    existe = 1;
                    break;
                }
            }
            if (!existe) {
                arestas[count].u = u;
                arestas[count].v = v;
                count++;
            }
        }
    }
}

int main() {
    srand(time(NULL));
    int tamanhos[] = {5, 8, 10, 12, 15};
    int num_testes = 5;

    for (int t = 0; t < num_testes; t++) {
        int V = tamanhos[t];
        int E = V + (V / 2);
        int max_e = (V * (V - 1)) / 2;
        if (E > max_e) {
            E = max_e;
        }

        Aresta *arestas = (Aresta *)malloc(E * sizeof(Aresta));
        gerar_grafo_aleatorio(V, E, arestas);

        int *melhor_bt = (int *)malloc(V * sizeof(int));
        int tamanho_minimo = 0;

        clock_t inicio_bt = clock();
        cobertura_minima_bt(V, E, arestas, melhor_bt, &tamanho_minimo);
        clock_t fim_bt = clock();
        double tempo_bt = (double)(fim_bt - inicio_bt) / CLOCKS_PER_SEC;

        int *solucao_gulosa = (int *)malloc(V * sizeof(int));
        clock_t inicio_gulosa = clock();
        cobertura_gulosa(V, E, arestas, solucao_gulosa);
        clock_t fim_gulosa = clock();
        double tempo_gulosa = (double)(fim_gulosa - inicio_gulosa) / CLOCKS_PER_SEC;

        int tamanho_gulosa = 0;
        for (int i = 0; i < V; i++) {
            if (solucao_gulosa[i]) tamanho_gulosa++;
        }

        printf("V = %d, E = %d\n", V, E);
        printf("  Força Bruta (BT) - Tamanho: %d | Tempo: %.6f s\n", tamanho_minimo, tempo_bt);
        printf("  Gulosa          - Tamanho: %d | Tempo: %.6f s\n", tamanho_gulosa, tempo_gulosa);
        printf("----------------------------------------\n");

        free(arestas);
        free(melhor_bt);
        free(solucao_gulosa);
    }

    return 0;
}