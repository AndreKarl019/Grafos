#include <stdio.h>
#include <stdlib.h>
#include "cobertura.h"

int eh_cobertura(int V, int E, Aresta *arestas, int *solucao) {
    (void)V;
    for (int i = 0; i < E; i++) {
        if (!solucao[arestas[i].u] && !solucao[arestas[i].v]) {
            return 0;
        }
    }
    return 1;
}

static void bt_aux(int V, int E, Aresta *arestas, int vertice, int *solucao_atual, int *melhor_solucao, int *tamanho_atual, int *tamanho_minimo) {
    if (*tamanho_atual >= *tamanho_minimo) {
        return;
    }

    if (vertice == V) {
        if (eh_cobertura(V, E, arestas, solucao_atual)) {
            if (*tamanho_atual < *tamanho_minimo) {
                *tamanho_minimo = *tamanho_atual;
                for (int i = 0; i < V; i++) {
                    melhor_solucao[i] = solucao_atual[i];
                }
            }
        }
        return;
    }

    solucao_atual[vertice] = 1;
    (*tamanho_atual)++;
    bt_aux(V, E, arestas, vertice + 1, solucao_atual, melhor_solucao, tamanho_atual, tamanho_minimo);
    
    solucao_atual[vertice] = 0;
    (*tamanho_atual)--;
    bt_aux(V, E, arestas, vertice + 1, solucao_atual, melhor_solucao, tamanho_atual, tamanho_minimo);
}

void cobertura_minima_bt(int V, int E, Aresta *arestas, int *melhor_solucao, int *tamanho_minimo) {
    int *solucao_atual = (int *)malloc(V * sizeof(int));
    for (int i = 0; i < V; i++) {
        solucao_atual[i] = 0;
        melhor_solucao[i] = 0;
    }
    *tamanho_minimo = V + 1;
    int tamanho_atual = 0;

    bt_aux(V, E, arestas, 0, solucao_atual, melhor_solucao, &tamanho_atual, tamanho_minimo);
    free(solucao_atual);
}

void cobertura_gulosa(int V, int E, Aresta *arestas, int *solucao) {
    for (int i = 0; i < V; i++) {
        solucao[i] = 0;
    }

    int *cobertas = (int *)malloc(E * sizeof(int));
    for (int i = 0; i < E; i++) {
        cobertas[i] = 0;
    }

    int arestas_cobertas = 0;
    int *grau = (int *)malloc(V * sizeof(int));

    while (arestas_cobertas < E) {
        for (int i = 0; i < V; i++) {
            grau[i] = 0;
        }

        for (int i = 0; i < E; i++) {
            if (!cobertas[i]) {
                if (!solucao[arestas[i].u]) grau[arestas[i].u]++;
                if (!solucao[arestas[i].v]) grau[arestas[i].v]++;
            }
        }

        int max_grau = -1;
        int escolhido = -1;
        for (int i = 0; i < V; i++) {
            if (!solucao[i] && grau[i] > max_grau) {
                max_grau = grau[i];
                escolhido = i;
            }
        }

        if (escolhido == -1) break;

        solucao[escolhido] = 1;

        for (int i = 0; i < E; i++) {
            if (!cobertas[i] && (arestas[i].u == escolhido || arestas[i].v == escolhido)) {
                cobertas[i] = 1;
                arestas_cobertas++;
            }
        }
    }

    free(cobertas);
    free(grau);
}