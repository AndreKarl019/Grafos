#include <stdio.h>

#define MAX_VERTICES 10

typedef struct{
    int u;
    int v;
} Aresta;

int eh_cobertura(Aresta *a, int *cobertura, int m){
    for(int i = 0; i < m; i++){
        int u = a[i].u;
        int v = a[i].v;
        if(!cobertura[u] && !cobertura[v]){
            return 0;
        }
    }

    return 1;
}

int main(){
    int cobertura[MAX_VERTICES];
    Aresta arestas[MAX_VERTICES];

    // V = {A, B, C, D}, E = {{A,B}. {B,C}, {C,D}}

    arestas[0].u = 0; arestas[0].v = 1;
    arestas[1].u = 1; arestas[1].v = 2;
    arestas[2].u = 2; arestas[2].v = 3;
    /*
    C1 = {A, B, D}
    */

    cobertura[0] = 1;
    cobertura[1] = 1;
    cobertura[2] = 0;
    cobertura[3] = 1;

    int resultado = eh_cobertura(arestas, cobertura, 3);
    printf("C1 = {A, B, C} eh cobertura? %s\n", resultado ? "sim":"nao");

    //C2 = {B, D}
    cobertura[0] = 0;
    cobertura[1] = 1;
    cobertura[2] = 1;
    cobertura[3] = 0;

    
    resultado = eh_cobertura(arestas, cobertura, 3);
    printf("C2 = {B, D} eh cobertura? %s\n", resultado ? "sim":"nao");

    //C3 = {A, B}
    cobertura[0] = 1;
    cobertura[1] = 1;
    cobertura[2] = 0;
    cobertura[3] = 0;
    
    resultado = eh_cobertura(arestas, cobertura, 3);
    printf("C3 = {A, B} eh cobertura? %s\n", resultado ? "sim":"nao");


    return 0;
}