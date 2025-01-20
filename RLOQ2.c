#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define tam_max_linha (1000)
#define tam_max_nome (50)
#define qtd_max_nomes (50)
#define tam_max_cadeia (255)

typedef struct itemPilha ItemPilha;
typedef struct itemFila ItemFila;

typedef struct itemPilha {
    ItemPilha *abaixo;
    char *valor;
} ItemPilha;

typedef struct {
    ItemPilha *topo;
} Pilha;

typedef struct itemFila {
    ItemFila *atras;
    char *valor;
} ItemFila;

typedef struct {
    ItemFila *inicio;
    ItemFila *fim;
} Fila;

Pilha* iniciarPilha();
void inserirItemPilha(Pilha **pilha, char *valor);
char* tirarItemPilha(Pilha **pilha);
Fila* iniciarFila();
void inserirItemFila(Fila **fila, char *valor);
int tirarItemFila(Fila **fila, char *apagado);
void lerLinha(char *linha, FILE *entrada, FILE *saida);
char* toLower(char *palavra);
int checarOrdemAlfabetica(char *palavra1, char *palavra2);
char converterEspecial(char *cadeia);
void removerAcentos(char *palavra);

int main() {
    FILE *entrada = fopen("L1Q2.in", "r");
    FILE *saida = fopen("L1Q2.out", "w");
    char *linha = malloc(tam_max_linha);

    lerLinha(linha, entrada, saida);

    fclose(entrada);
    fclose(saida);
    free(linha);
    return 0;
}

Pilha* iniciarPilha() {
    Pilha *pilha = malloc(sizeof(Pilha));
    pilha->topo = NULL;
    return pilha;
}

void inserirItemPilha(Pilha **pilha, char *valor) {
    ItemPilha *novoItem = malloc(sizeof(ItemPilha));
    novoItem->abaixo = (*pilha)->topo;
    novoItem->valor = malloc(strlen(valor) + 1);
    
    int iCont;
    for(iCont = 0; iCont < strlen(valor); iCont++){
        novoItem->valor[iCont] = valor[iCont];
    }
    novoItem->valor[iCont] = '\0';
    (*pilha)->topo = novoItem;
}

char* tirarItemPilha(Pilha **pilha) {
    char *apagado = malloc(tam_max_nome);
    strcpy(apagado, (*pilha)->topo->valor);
    
    ItemPilha *itemApagado = (*pilha)->topo;
    (*pilha)->topo = (*pilha)->topo->abaixo;
    free(itemApagado->valor);
    free(itemApagado);
    return apagado;
}

Fila* iniciarFila() {
    Fila *fila = malloc(sizeof(Fila));
    fila->inicio = NULL;
    fila->fim = NULL;
    return fila;
}

void inserirItemFila(Fila **fila, char *valor) {
    ItemFila *novoItem = malloc(sizeof(ItemFila));
    novoItem->valor = malloc(strlen(valor) + 1);
    
    int iCont;
    for(iCont = 0; iCont < strlen(valor); iCont++) {
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

// Função para converter caracteres especiais (acentuados) para sem acento
char converterEspecial(char *cadeia) {
    static const char *tabelaLexica[2][42] = {
        { "á", "à", "â", "ã", "é", "è", "ê", "ẽ", "í", "ì", "î", "ĩ", 
          "ó", "ò", "ô", "õ", "ú", "ù", "û", "ũ", "ç", 
          "Á", "À", "Â", "Á", "É", "È", "Ê", "Ẽ", "Í", "Ì", "Ĩ", "Î", 
          "Ó", "Ò", "Ô", "Õ", "Ú", "Ù", "Ũ", "Û", "Ç" },
        { "a", "a", "a", "a", "e", "e", "e", "e", "i", "i", "i", "i", 
          "o", "o", "o", "o", "u", "u", "u", "u", "c", 
          "A", "A", "A", "A", "E", "E", "E", "E", "I", "I", "I", "I", 
          "O", "O", "O", "O", "U", "U", "U", "U", "C" }
    };

    int i, j;
    // Verifica se o caractere tem acento ou é uma letra especial
    for (i = 0; i < 42; i++) {
        for (j = 0; j < strlen(tabelaLexica[0][i]); j++) {
            if (cadeia[0] == tabelaLexica[0][i][j]) {
                // Se encontrou a correspondência, retorna o caractere sem acento
                return tabelaLexica[1][i][0];
            }
        }
    }
    return cadeia[0]; // Se não for acentuado, retorna o próprio caractere
}

// Função para remover acentos de uma palavra
void removerAcentos(char *palavra) {
    int i;
    for (i = 0; palavra[i] != '\0'; i++) {
        palavra[i] = converterEspecial(&palavra[i]);
    }
}

// Função para comparar duas palavras, ignorando acentos
int checarOrdemAlfabetica(char *palavra1, char *palavra2) {
    // Faz cópias das palavras para não modificar os valores originais
    char palavra1SemAcento[strlen(palavra1) + 1];
    char palavra2SemAcento[strlen(palavra2) + 1];
    
    strcpy(palavra1SemAcento, palavra1);
    strcpy(palavra2SemAcento, palavra2);

    // Remove os acentos das cópias
    removerAcentos(palavra1SemAcento);
    removerAcentos(palavra2SemAcento);

    // Compara as palavras sem acentos
    return strcmp(palavra1SemAcento, palavra2SemAcento);
}

void lerLinha(char *linha, FILE *entrada, FILE *saida) {
    char *novoNome = malloc(tam_max_nome);
    while(fgets(linha, tam_max_linha, entrada) != NULL) {
        Pilha *pilha = iniciarPilha();
        Fila *fila = iniciarFila();
        int iCont = 0, jCont, popsSeguidos = 0;

        while(linha[iCont] != '\n' && linha[iCont] != '\0') {
            jCont = 0;
            while(linha[iCont] != ' ' && linha[iCont] != '\n' && linha[iCont] != '\0') {
                novoNome[jCont] = linha[iCont];
                iCont++;
                jCont++;
            }
            novoNome[jCont] = '\0';
            
            if(pilha->topo == NULL || checarOrdemAlfabetica(novoNome, pilha->topo->valor) == 2) {
                inserirItemPilha(&pilha, novoNome);
                inserirItemFila(&fila, novoNome);
            } else {
                popsSeguidos = 0;
                while(pilha->topo != NULL && checarOrdemAlfabetica(novoNome, pilha->topo->valor) != 2) {
                    tirarItemPilha(&pilha);
                    popsSeguidos++;
                }
                char popRegistro[10];
                sprintf(popRegistro, "%dx-pop", popsSeguidos);
                inserirItemFila(&fila, popRegistro);
                inserirItemPilha(&pilha, novoNome);
                inserirItemFila(&fila, novoNome);
            }
            iCont++;
        }

        // Imprime a fila
        ItemFila *temp = fila->inicio;
        while(temp != NULL) {
            // Verifica se o valor não é um "Nx-pop" e prefixa "push-"
            if (strstr(temp->valor, "-pop") == NULL) {
                fprintf(saida, "push-%s ", temp->valor);
            } else {
                fprintf(saida, "%s ", temp->valor);
            }
            temp = temp->atras;
        }
        fprintf(saida, "\n");
        free(fila);
    }
    free(novoNome);
}
