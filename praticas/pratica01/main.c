#include <stdio.h>
#include "grafo_lista.h"
#include "grafo_matriz.h"

int main(){
    GrafoMatriz *grafo = criar_grafo_matriz(7);
    
    //teste Matriz
    printf("Teste matriz adjacencia\n\n");


    inserir_aresta_matriz(grafo, 0, 1);
    inserir_aresta_matriz(grafo, 0, 3);
    inserir_aresta_matriz(grafo, 0, 2);
    inserir_aresta_matriz(grafo, 2, 4);
    inserir_aresta_matriz(grafo, 2, 5);
    inserir_aresta_matriz(grafo, 2, 6);
    inserir_aresta_matriz(grafo, 6, 3);
    inserir_aresta_matriz(grafo, 6, 0);

    exibir_matriz(grafo);
    printf("\n");

    for(int i = 0; i<6;i++){
        printf("O numero %i tem %i adjacencias\n", i, grau_matriz(grafo, i));
    }
    printf("\n");

    for(int i = 0;i<6;i++){
        for(int j = 0; j<6; j++){
            if(sao_adjacentes_matriz(grafo, i, j)==1){
                printf("O numero %i e o numero %i sao adjacentes\n", i, j);
            }else{
                printf("O numero %i e o numero %i nao sao adjacentes\n", i, j);
            }
        }
        printf("\n");
    }

    remover_aresta_matriz(grafo, 6, 3);
    remover_aresta_matriz(grafo, 6, 0);

    exibir_matriz(grafo);

    liberar_grafo_matriz(grafo);

    //Teste Lista adjacencia
    printf("Teste lista adjacencia\n");


    GrafoLista *lista = criar_grafo_lista(6);
    printf("Lista criada\n");
    inserir_aresta_lista(lista, 0, 1);
    inserir_aresta_lista(lista, 0, 2);
    inserir_aresta_lista(lista, 0, 3);
    inserir_aresta_lista(lista, 0, 4);
    inserir_aresta_lista(lista, 1, 2);
    inserir_aresta_lista(lista, 2, 3);
    inserir_aresta_lista(lista, 2, 5);
    inserir_aresta_lista(lista, 3, 4);
    inserir_aresta_lista(lista, 3, 5);
    printf("valores inseridos\n");

    int teste = -1;

    teste = sao_adjacentes_lista(lista, 0, 1);
    if(teste==1){
        printf("o Numero 0 e 1 sao adjacentes\n");
    }else{
        printf("o Numero 0 e 1 nao sao adjacentes\n");
    }
    teste = sao_adjacentes_lista(lista, 2, 5);
    if(teste==1){
        printf("o Numero 2 e 5 sao adjacentes\n");
    }else{
        printf("o Numero 2 e 5 nao sao adjacentes\n");
    }
    teste = sao_adjacentes_lista(lista, 1, 3);
    if(teste==1){
        printf("o Numero 1 e 3 sao adjacentes\n");
    }else{
        printf("o Numero 1 e 3 nao sao adjacentes\n");
    }
    

    remover_aresta_lista(lista, 2, 5);
    teste = sao_adjacentes_lista(lista, 2, 5);
    if(teste==1){
        printf("o Numero 2 e 5 sao adjacentes\n");
    }else{
        printf("o Numero 2 e 5 nao sao adjacentes\n");
    }

    teste = grau_lista(lista, 2);
    printf("O numero 2 tem grau %i\n", teste);
    teste = grau_lista(lista, 1);
    printf("O numero 1 tem grau %i\n", teste);
    liberar_grafo_lista(lista);





    return 0;
}