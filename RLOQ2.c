#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define tam_max_linha (1000)
#define tam_max_nome (50)

typedef struct itemPilha ItemPilha;
typedef struct itemFila ItemFila;

typedef struct itemPilha{
    ItemPilha *abaixo;
    char *valor;
}ItemPilha;

typedef struct {
    ItemPilha *topo;
}Pilha;

typedef struct itemFila{
    ItemFila *atras;
    char *valor;
}ItemFila;

typedef struct{
    ItemFila *inicio;
    ItemFila *fim;
}Fila;

Pilha* iniciarPilha();
void inserirItemPilha(Pilha **pilha, char *valor);
int tirarItemPilha(Pilha **pilha, char *apagado);
void lerLinha(char *linha, FILE *entrada, FILE *saida, Pilha **pilha, Fila **fila);

int main(){

    
    return 1;
}

Pilha* iniciarPilha(){
    Pilha *pilha = malloc(sizeof(Pilha));
    pilha->topo = NULL;
    return pilha;
}

void inserirItemPilha(Pilha **pilha, char *valor){
    int iCont;

    ItemPilha *novoItem = malloc(sizeof(ItemPilha));
    novoItem->abaixo = (*pilha)->topo;
    novoItem->valor = malloc(sizeof(char) * strlen(valor));

    for(iCont = 0; iCont < strlen(valor); iCont++){
        novoItem->valor[iCont] = valor[iCont];
    }

    (*pilha)->topo = novoItem;
}

int tirarItemPilha(Pilha **pilha, char *apagado){
    //retorno 0: Erro ao apagar;
    //retorno 1 : Apagado com sucesso;
    int iCont;

    if((*pilha)->topo == NULL){
        return 0;
    }
    
    for(iCont = 0; iCont < strlen((*pilha)->topo->valor); iCont++){
        apagado[iCont] = (*pilha)->topo->valor[iCont];
    }
    apagado[strlen((*pilha)->topo->valor)] = '\0';
    
    ItemPilha *itemApagado = (*pilha)->topo;
    (*pilha)->topo = (*pilha)->topo->abaixo;
    free(itemApagado);
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
