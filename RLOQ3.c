#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define tam_max_linha (1000)
#define tam_max_cadeia (255)
#define tam_max_casas_num (5)

#define FIM_LINHA (-21)
#define TERMINADOR_NULO (-22)

typedef struct le LE;
typedef struct li LI;
typedef struct itemListaInt ItemListaInt;
typedef struct cabecoteListaFloat CabecoteListaFloat;
typedef struct itemListaFloat ItemListaFloat;

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
ItemListaFloat* inicializarItemListaFloat(float valor);
void adicionarLE(int valor, LE **le);
void adicionarLi(float valor, LE **le);
CabecoteListaInt* inicializarListaInt();
void adicionarItemListaInt(CabecoteListaInt **cabecote, int valor);
void adicionarItemListaFloatOrdenado(CabecoteListaInt **cabecote, int valor);
int leituraLi(float* listaFloat, char *linha, int *contLinha);
int converterStrPraInt(char *string);
int* leituraLe(char *linha, int *tamArray);
float cadeiaParaFloat(char* cadeia);
char* obterSubCadeia(char *cadeia, char separador);

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

// Sumário: Lê o LI de uma entrada de texto, cujos números em ponto flutuante - decimal - 
// devem ser espaçados em 1 entre si pois navega pelos
// espaços.
// Parâmetros: <listaFloat: lista a ser preenchida>, <linha: texto de entrada> e 
// <contLinha: índice atual do texto de entrada
// Retorno: <int: FIM_LINHA ou TERMINADOR_NULO, quando terminar de ler>
int leituraLi(float* listaFloat, char *linha, int *contLinha){ 
    CabecoteListaFloat *lista = inicializarListaFloat();

    while (linha[*contLinha] != '\0'){
        *contLinha += proximosOuFimNaCadeia(&linha[*contLinha], " ");
        switch(proximoCharNaCadeiaIntervalo(&linha[*contLinha], "\n", 1))
        {
            case ('\0'): goto fim; // fim string
            case ('\n'): return FIM_LINHA; // pula linha
                     // insere                       // converte       // obtém substring
            default: adicionarItemListaFloatOrdenado(&lista, cadeiaParaFloat(obterSubCadeia(&linha[*contLinha + 1], ' ')));
        }
    }

    fim: return TERMINADOR_NULO;
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


// Sumário: obtém uma cadeia de caracteres como entrada tal como um separador, retorna
// endereço para uma subcadeia contendo o início até o separador - sem o incluir
// Parâmetros: <cadeia: cadeia de caracteres de entrada> e <separador: caracter de separação>
// Retorna: <char *: endereço da variável estática "subcadeia", contendo a subcadeia lida>
char * obterSubCadeia(char *cadeia, char separador){
    // subcadeia
    static char subcadeia[tam_max_cadeia];
    int i; // contador

    // copia até sentinelas - tamanho máximo, separador e fim de linha
    for (i = 0; cadeia[i] != separador && cadeia[i] != '\0' && cadeia[i] != '\n' && i < tam_max_linha - 1; i += sizeof(char))
        subcadeia[i] = cadeia[i];

    // final da subcadeia
    subcadeia[i] = '\0';

    // endereço da subcadeia
    return subcadeia;
}
