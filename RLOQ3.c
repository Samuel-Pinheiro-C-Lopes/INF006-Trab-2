#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define tam_max_linha (1000)
#define tam_max_casas_num (5)

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

// inicializar
LE* inicializarLE(int valor);
LI* inicializarLI(int valor);
void adicionarLE(int valor, LE **le);
void adicionarLi(float valor, LE **le);
CabecoteListaInt* inicializarListaInt();
void adicionarItemListaInt(CabecoteListaInt **cabecote, int valor);
int converterStrPraInt(char *string);
int* leituraLe(char *linha, int *tamArray);

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

LI* inicializarLI(int valor){
    LI *li = (LI *) malloc(sizeof(LI));
    li->proximo = NULL;
    li->valor = valor;
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

int converterStrPraInt(char *string){
    int iCont = 0;
    int qtdCasas, base = 1;
    int sinal = 1;
    int valor = 0;

    if(string[0] == '-'){
        sinal = -1;
        iCont++;
    }

    qtdCasas = iCont;
    while(qtdCasas + 1< strlen(string)){
        qtdCasas++;
        base *= 10;
    }

    while(iCont < strlen(string)){
        valor += base * (string[iCont] - '0');
        base /= 10;
        iCont++;
    }

    return valor * sinal;
}

int* leituraLe(char *linha, int *tamArray){
    //Essa função deve ser chamada por linha lida do arquivo. Ela pega todos os LE's e retorna um array com todos eles na ordem que chegaram.
    // Essa função recebe a linha e o ponteiro de um inteiro como parâmetro. Nesse ponteiro, ficará a informação do tamanho do array.
    int iCont, jCont;
    CabecoteListaInt *lista = inicializarListaInt();

    for(iCont = 3; linha[iCont] != 'L'; iCont++){
        jCont = 0;
        char *novoNumero = malloc(sizeof(char) * tam_max_casas_num);
        while(linha[iCont] != ' '){
            novoNumero[jCont] = linha[iCont];
            iCont++;
            jCont++; 
        }
        adicionarItemListaInt(&lista, converterStrPraInt(novoNumero));
    }

    int *listaInt = malloc(sizeof(int) * lista->quantidadeItens);
    ItemListaInt *aux = lista->primeiro;

    for(iCont = 0; iCont < lista->quantidadeItens;iCont++){
        listaInt[iCont] = aux->valor;
        aux = aux->proximo;
    }

    *tamArray = lista->quantidadeItens;
    return listaInt;
}