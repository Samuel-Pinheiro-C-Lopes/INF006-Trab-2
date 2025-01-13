
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define tam_max_linha (1000)
#define tam_max_nome (50)

typedef struct itemLista ItemLista;
typedef struct lista Lista;

struct itemLista{
    ItemLista *prox;
    int valor;
};

struct lista{
    Lista* prox;
    ItemLista *inicio;
    int soma;
};


Lista* iniciarLista();
void inserirItemLista(Lista *lista, int valor);
void inserirLista(Lista *lista, Lista *novaLista);
int lerLista(char *linha, FILE *entrada, Lista *lista);

int main(){

    
    return 1;
}

Lista* iniciarLista(){
    Lista *lista = (Lista*) malloc(sizeof(Lista));
    lista->soma = 0;
    lista->inicio = NULL;
    lista->prox = NULL;
    return lista;
}

void inserirItemLista(Lista *lista, int novoValor){
    // declara e inicializa o item
    ItemLista* item = (ItemLista*) malloc(sizeof(ItemLista));
    item->valor = novoValor; 

    // incrementa a soma
    lista->soma += novoValor;

    // insere na posição correta, ordenando
    ItemLista* atual = lista->inicio;

    if (atual == NULL || atual->valor > novoValor){
        // insere
        item->prox = lista->inicio;
        lista->inicio = item;

        // atualiza o cabeçote
        lista->inicio = item;
        lista->soma += item->valor;
    }
    else{
        // encontra o final ou posição correta - próximo valor é maior que o novo
        while(atual->prox != NULL && atual->prox->valor < novoValor)
            atual = atual->prox;

        // insere
        item->prox = atual->prox;
        atual->prox = item->prox;
    }
}

/*
Fila* iniciarFila() {
    Fila *fila = malloc(sizeof(Fila));
    fila->inicio = NULL;
    fila->fim = NULL;
    return fila;
}

void inserirItemFila(Fila **fila, char *valor) {
    int iCont;
    ItemFila *novoItem = malloc(sizeof(ItemFila));
    novoItem->valor = malloc(strlen(valor) + 1);

    for (iCont = 0; iCont < strlen(valor); iCont++) {
        novoItem->valor[iCont] = valor[iCont];
    }
    novoItem->valor[iCont] = '\0';

    novoItem->atras = NULL;
    if ((*fila)->inicio == NULL) {
        (*fila)->inicio = novoItem;
        (*fila)->fim = novoItem;
    } else {
        (*fila)->fim->atras = novoItem;
        (*fila)->fim = novoItem;
    }
}

int tirarItemFila(Fila **fila, char *apagado) {
    if ((*fila)->inicio == NULL) {
        return 0;
    }

    int iCont;
    for (iCont = 0; iCont < strlen((*fila)->inicio->valor); iCont++) {
        apagado[iCont] = (*fila)->inicio->valor[iCont];
    }
    apagado[iCont] = '\0';

    ItemFila *itemApagado = (*fila)->inicio;
    (*fila)->inicio = (*fila)->inicio->atras;
    free(itemApagado->valor);
    free(itemApagado);

    if ((*fila)->inicio == NULL) {
        (*fila)->fim = NULL;
    }

    return 1;
}


void lerLinha(char *linha, FILE *entrada, FILE *saida, Pilha **pilha, Fila **fila) {
    int iCont, jCont;
    char *novoNome = malloc(sizeof(char) * tam_max_nome);

    while (fgets(linha, tam_max_linha, entrada) != NULL) {
        iCont = 0;

        while (linha[iCont] != '\n' && linha[iCont] != '\0') {
            jCont = 0;

            while (linha[iCont] != ' ' && linha[iCont] != '\n' && linha[iCont] != '\0') {
                novoNome[jCont] = linha[iCont];
                iCont++;
                jCont++;
            }

            if (jCont > 0) {
                novoNome[jCont] = '\0';
                //O nome já estará pronto para ser adicionado na pilha. Aqui deverá ser feita as validações.
            }

            iCont++;
        }
    }

    free(novoNome);
}
*/
