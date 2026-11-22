#include <stdlib.h>
#include "hamiltoniano.h"

static int bt_hamiltoniano(int V, int **matriz, int pos, int *caminho, int *visitado) {
    if (pos == V) {
        return 1;
    }

    for (int v = 0; v < V; v++) {
        if (!visitado[v]) {
            if (pos == 0 || matriz[caminho[pos - 1]][v] > 0) {
                visitado[v] = 1;
                caminho[pos] = v;

                if (bt_hamiltoniano(V, matriz, pos + 1, caminho, visitado)) {
                    return 1;
                }

                visitado[v] = 0;
            }
        }
    }
    return 0;
}

int encontrar_caminho_hamiltoniano_bt(int V, int **matriz, int *caminho) {
    int *visitado = (int *)malloc(V * sizeof(int));
    for (int i = 0; i < V; i++) {
        visitado[i] = 0;
        caminho[i] = -1;
    }

    int encontrado = bt_hamiltoniano(V, matriz, 0, caminho, visitado);
    free(visitado);
    return encontrado;
}