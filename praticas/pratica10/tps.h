#ifndef TPS_H
#define TPS_H

void grafo_para_tsp(int V, int **matriz_original, int **matriz_tsp);
int tsp_forca_bruta(int V, int **matriz, int *ciclo_otimo);
int tsp_vizinho_mais_proximo(int V, int **matriz, int *ciclo);
int tsp_insercao(int V, int **matriz, int *ciclo);

#endif