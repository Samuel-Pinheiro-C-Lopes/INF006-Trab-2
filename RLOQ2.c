#include <stdio.h>
#include <stdlib.h>

typedef struct itemPilha ItemPilha;
typedef struct itemFila ItemFila;

typedef struct {
    ItemPilha *topo;
}Pilha;

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