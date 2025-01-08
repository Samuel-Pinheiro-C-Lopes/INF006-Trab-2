#include <stdio.h>
#include <stdlib.h>

typedef struct pilha Pilha;
typedef struct itemPilha ItemPilha;
typedef struct fila Fila;
typedef struct itemFila ItemFila;

typedef struct{
    ItemPilha *abaixo;
    char *valor;
}ItemPilha;

typedef struct{
    ItemFila *inicio;
    ItemFila *fim;
}Fila;

typedef struct{
    ItemFila *atras;
    char *valor;
}ItemFila;