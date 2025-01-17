#include <stdio.h>
#include <stdlib.h>

typedef struct le LE;
typedef struct li LI;
typedef struct itemListaInt ItemListaInt;

typedef struct li{
    LI *proximo;
    float valor;
}LI;

typedef struct le{
    LE *proximo;
    LE *anterior;
    LI *li;
    int valor; 
}LE;

typedef struct itemListaInt{
    int valor;
    ItemListaInt *proximo;
}ItemListaInt;

typedef struct{
    ItemListaInt *primeiro;
    int quantidadeItens;
}CabecoteListaInt;

LE* inicializarLE(int valor);
void adicionarLE(int valor, LE **le);
void adicionarLi(float valor, LE **le);
CabecoteListaInt* inicializarListaInt();
void adicionarItemListaInt(CabecoteListaInt **cabecote, int valor);

int main(){

    return 1;
}

LE* inicializarLE(int valor){
    LE *le = malloc(sizeof(LE));
    le->valor = valor;
    le->anterior = NULL;
    le->proximo = NULL;
    le->li = NULL;
    return le;
}

void adicionarLE(int valor, LE **inicio){
    //Essa função funcionará usada inserindo os valores já ordenado anteriormente
    if((*inicio) == NULL){
        return;
    }

    LE *novoLe = inicializarLE(valor);
    LE *aux = (*inicio);

    while(aux->proximo != NULL){
        aux = aux->proximo;
    }
    aux->proximo = novoLe;
    novoLe->anterior = aux;
}

void adicionarLi(float valor, LE **le){
    //Essa função funcionará usada inserindo os valores já ordenado anteriormente
    LI *novaLi = malloc(sizeof(LI));
    novaLi->valor = valor;

    if((*le)->li == NULL){
        (*le)->li = novaLi;
        novaLi->proximo = novaLi;
        return;
    }

    LI *aux = (*le)->li;
    do{
        aux = aux->proximo;
    }while(aux->proximo != (*le)->li);

    novaLi->proximo = aux->proximo;
    aux->proximo = novaLi;
}

CabecoteListaInt* inicializarListaInt(){
    CabecoteListaInt *novaLista = malloc(sizeof(CabecoteListaInt));
    novaLista->primeiro = NULL;
    novaLista->quantidadeItens = 0;
    return novaLista;
}

void adicionarItemListaInt(CabecoteListaInt **cabecote, int valor){
    ItemListaInt *novoItemLista = malloc(sizeof(ItemListaInt));
    novoItemLista->valor = valor;
    novoItemLista->proximo = NULL;

    if((*cabecote)->primeiro == NULL){
        (*cabecote)->primeiro = novoItemLista;
        (*cabecote)->quantidadeItens = 1;
        return;
    }

    ItemListaInt *aux = (*cabecote)->primeiro;

    while(aux->proximo != NULL){
        aux = aux->proximo;
    }

    aux->proximo = novoItemLista;
    (*cabecote)->quantidadeItens++;
}