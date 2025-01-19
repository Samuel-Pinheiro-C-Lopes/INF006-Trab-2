#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define tam_max_linha (1000)
#define tam_max_cadeia (255)
#define tam_max_casas_num (5)

#define FIM_LINHA (-21)
#define TERMINADOR_NULO (-22)
#define NUMERO (-33)
#define PONTO (-34)

typedef struct linhaSaida LinhaSaida;
typedef struct le LE;
typedef struct li LI;
typedef struct itemListaInt ItemListaInt;
typedef struct cabecoteListaFloat CabecoteListaFloat;
typedef struct itemListaFloat ItemListaFloat;

struct LinhaSaida{
    LE *inicioLE;
    char linha[tam_max_linha];
};

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

struct itemListaFloat{
    float valor;
    ItemListaFloat *proximo;
};

typedef struct{
    ItemListaInt *primeiro;
    int quantidadeItens;
}CabecoteListaInt;

struct cabecoteListaFloat{
    ItemListaFloat *primeiro;
    int quantidadeItens;
};

// inicializar
LE* inicializarLE(int valor);
LI* inicializarLI(int valor);
ItemListaFloat* inicializarItemListaFloat(float valor);
CabecoteListaInt* inicializarListaInt();
CabecoteListaFloat* inicializarListaFloat();
// adicionar
void adicionarLE(int valor, LE **le);
void adicionarLi(float valor, LE **le);
void adicionarItemListaInt(CabecoteListaInt **cabecote, int valor);
void adicionarItemListaIntOrdenado(CabecoteListaInt *cabecote, int valor);
void adicionarItemListaFloatOrdenado(CabecoteListaFloat *cabecote, float valor);
// leitura
int* leituraLe(char *linha, int *tamArray, int *contLinha);
float* leituraLi(char *linha, int *tamArray, int *contLinha);
void lerArquivo(LinhaSaida *saida, FILE *entrada);
// cadeia
int converterStrPraInt(char *string);
float cadeiaParaFloat(char* cadeia);
char* obterSubCadeia(char *cadeia, char separador);
int checarCharFloat(char c);
int proximosOuFimNaCadeia(char *cadeia, char *separadores); 
char proximoCharNaCadeiaIntervalo(char *cadeia, char *separadores, int intervalo);

int main(){
   
   // testes
    char teste[10] = "0";
    float res = cadeiaParaFloat(teste);
    printf("\nt: %f\n", res);
   // testes
    return 1;
}


// Sumário: Lê todas as listas presentes no arquivo de entrada, atribuindo e 
// completando a linha de saída com base nisso
// Parâmetros: <cbct: cabeçote das listas a ser preenchido> e <entrada: arquivo de entrada>
// Retorna: <void>
void lerArquivo(LinhaSaida *saida, FILE *entrada){
    // linha a ser lida
    static char linha[tam_max_linha];

    int contLinha;
    int tamVetor = 0; 
    int i; // contador

    // indexadores do início de LI e LE
    LI *inicioLI;
    LE *inicioLE;

    // vetores para valores ordenados de LI e LE
    float *arrayLI;
    int *arrayLE;


    // enquanto houver linhas a serem lidas no arquivo de entrada
    while (fgets(linha, tam_max_linha, entrada) != NULL){
        contLinha = 3;
        // LE
        arrayLE = leituraLe(linha, &tamVetor, &contLinha);

        // atribui cada um, já ordenados
        inicioLE = inicializarLE(arrayLE[0]);
        for (i = 1; i < tamVetor; i++)
            adicionarLE(arrayLE[i], inicioLE);

        // LI
        arrayLI = leituraLi(linha, &tamVetor, &contLinha);

        // atribui cada um, já ordenados
        inicioLI = inicializarLI(arrayLI[0]);
        for (i = 1; i < tamVetor; i++)
            adicionarLi(arrayLI[i], inicioLE);

        // ASSOCIAR LI COM LE

        // SUBSCREVER CADEIA CORRESPONDENTE E ATRIBUIR LINHA DE SAÍDA
    }
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
    return li;
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

// Sumário: inicializa um cabeçote de lista float
// Parâmetros: <void>
// Retorna: <CabecoteListaFloat*: ponteiro do novo cabeçote>
CabecoteListaFloat* inicializarListaFloat(){
    CabecoteListaFloat *novoCbct = (CabecoteListaFloat *) malloc(sizeof(CabecoteListaFloat));
    novoCbct->primeiro = NULL;
    novoCbct->quantidadeItens = 0;
    return novoCbct;
}

// Sumário: inicializa um item de lista float com base um uma chave 
// Parâmetros: <valor: chave do novo item a ser inicializado>
// Retorna: <ItemListaFloat*: ponteiro do novo item da lista>
ItemListaFloat* inicializarItemListaFloat(float valor){
    ItemListaFloat *novoItem = (ItemListaFloat *) malloc(sizeof(ItemListaFloat));
    novoItem->proximo = NULL;
    novoItem->valor = valor;
    return novoItem;
}

// Sumário: inicializa um item de lista inteiro com base em uma chave
// Parâmetros: <valor: chave do novo item a ser inicializado>
// Retorna: <ItemListaInt*: ponteiro do novo item da lista>
ItemListaInt* inicializarItemListaInt(int valor){
    ItemListaInt *novoItem = (ItemListaInt *) malloc(sizeof(ItemListaInt));
    novoItem->proximo = NULL;
    novoItem->valor = valor;
    return novoItem;
}

// Sumário: insere um item de lista float em sua posição correta - crescente
// Parâmetros: <cabecote: cabecote da lista a ser inserida> e <valor: chave do novo item
// a ser inserido>
// Retorna: <void>
void adicionarItemListaFloatOrdenado(CabecoteListaFloat *cabecote, float valor){
    ItemListaFloat *novoItem = inicializarItemListaFloat(valor);
    ItemListaFloat *atual;

    // atribuir logo no início
    if (cabecote->primeiro == NULL || cabecote->primeiro->valor > novoItem->valor){
        novoItem->proximo = cabecote->primeiro;
        cabecote->primeiro = novoItem;
    }
    // meio ou final
    else{
        atual = cabecote->primeiro;
        // encontra posição correta
        while (atual->proximo != NULL && atual->proximo->valor < novoItem->valor)
            atual = atual->proximo;

        // insere
        novoItem->proximo = atual->proximo;
        atual->proximo = novoItem;
    }
}

// Sumário: insere um item de lista int em sua posição correta - crescente
// Parâmetros: <cabecote: cabecote da lista a ser inserida> e <valor: chave do novo item
// a ser inserido>
// Retorna: <void>
void adicionarItemListaIntOrdenado(CabecoteListaInt *cabecote, int valor){
    ItemListaInt *novoItem = inicializarItemListaInt(valor);
    ItemListaInt *atual;

    // atribuir logo no início
    if (cabecote->primeiro == NULL || cabecote->primeiro->valor > novoItem->valor){
        novoItem->proximo = cabecote->primeiro;
        cabecote->primeiro = novoItem;
    }
    // meio ou final
    else{
        atual = cabecote->primeiro;
        // encontra posição correta
        while (atual->proximo != NULL && atual->proximo->valor < novoItem->valor)
            atual = atual->proximo;

        // insere
        novoItem->proximo = atual->proximo;
        atual->proximo = novoItem;
    }
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
float* leituraLi(char *linha, int *tamVetor, int *contLinha){ 
    // CABEÇOTE

    CabecoteListaFloat* listaFloat = inicializarListaFloat();
    *(tamVetor) = 0;

    while (linha[*contLinha] != '\0'){
        *contLinha += proximosOuFimNaCadeia(&linha[*contLinha], " ");
        switch(proximoCharNaCadeiaIntervalo(&linha[*contLinha], "\n", 1))
        {
            case ('\0'): 
            case ('\n'): break; // interrompe atribuições
                     // insere                       // converte       // obtém substring
            default: {
                adicionarItemListaFloatOrdenado(listaFloat, cadeiaParaFloat(obterSubCadeia(&linha[*contLinha + 1], ' ')));
                *(tamVetor) += 1;
            }
        }
    }

    // VETOR

    float *vetor = (float *) malloc(sizeof(float) * (*(tamVetor)));

    {
        float *atualVetor = vetor;
        ItemListaFloat *atualLista = listaFloat->primeiro;
        while (atualLista != NULL) {
            *(atualVetor) = atualLista->valor;
            atualLista = atualLista->proximo;
            atualVetor += sizeof(float);
        }
    }

    free(listaFloat);
    return vetor;
}

int* leituraLe(char *linha, int *tamArray, int *contLinha){
    //Essa função deve ser chamada por linha lida do arquivo. Ela pega todos os LE's e retorna um array com todos eles na ordem que chegaram.
    // Essa função recebe a linha e o ponteiro de um inteiro como parâmetro. Nesse ponteiro, ficará a informação do tamanho do array.
    int iCont, jCont;
    CabecoteListaInt *lista = inicializarListaInt();

    for(*(contLinha) = 3; linha[*(contLinha)] != 'L'; (*contLinha)++){
        jCont = 0;
        char *novoNumero = malloc(sizeof(char) * tam_max_casas_num);
        while(linha[*(contLinha)] != ' '){
            novoNumero[jCont] = linha[*(contLinha)];
            *(contLinha) += 1;
            jCont++; 
        }
        // adicionarItemListaInt(&lista, converterStrPraInt(novoNumero));
        adicionarItemListaIntOrdenado(lista, converterStrPraInt(novoNumero));
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


// Sumário: converte um texto para seu equivalente numérico em ponto flutuante
// Parâmetros: <cadeia: indexador da cadeia a ser convertida>
// Returns: <float: decimal resultante>
float cadeiaParaFloat(char* cadeia){
    // propriedades
    float numero = (float) 0;
    int negativo = 0;
    int base = 10;

    // se for negativo
    if (*cadeia == '-')
    {
        negativo = 1; 
        cadeia += sizeof(char);
    }

    // enquanto  não encontrar o final da linha ou ponto decimal
    while (checarCharFloat(*(cadeia)) == NUMERO){
        numero *= (float) 10; // incrementa o número de algarismos e ordem de grandeza
        numero += (float) *(cadeia) - 48;  // atribui o novo algarismo em sua casa atual
        cadeia += sizeof(char); // incrementa o indexador
    }

    // se houver parte fracionária
    if (checarCharFloat(*(cadeia)) == PONTO)
    {
        cadeia += sizeof(char);
        // enquanto o indexador apontar para um número
        while(checarCharFloat(*(cadeia)) == NUMERO){
            numero += ((float) (*(cadeia) - 48) / base);
            base *= 10;
            cadeia += sizeof(char);
        }
    }

    // sinal negativo
    if (negativo)
        numero *= -1;

    return numero; // resultado
}

// Sumário: checa se o caracter corresponde a algum 
// de interesse para avaliação de ponto flutuante - número ou ponto
// Parâmetros: <c: caractere a ser avaliado>
// Retorno: <int: resultado, se é NUMERO, PONTO ou 0 caso seja inválido>
int checarCharFloat(char c) {
    if (c > 47 && c < 58)
        return NUMERO;
    else if (c == '.')
        return PONTO;
    else 
        return 0;
}

// Sumário: busca pela posição em uma cadeia da primeira ocorrência do final e de um ou mais 
// caracteres de separação
// Parâmetros: <cadeia: cadeia de caracteres de entrada> e <separadores: caracteres de busca>
// Returna: <int: índice de posição da ocorrência> 
int proximosOuFimNaCadeia(char *cadeia, char *separadores){
    // contadores
    int i, k;

    // busca a próxima primeira ocorrência de um dos separadores na cadeia de entrada
    for (i = 1; cadeia[i] != '\0'; i++)
    {
        for (k = 0; separadores[k] != '\0'; k++)
            if (cadeia[i] == separadores[k])
                goto fim;
    }
    
    // retorna o índice
    fim: return i;
}


// Sumário: busca em uma cadeia a primeira ocorrência de um ou mais 
// caracteres de separação em um intervalo, retornando essa ocorrência
// Parâmetros: <cadeia: cadeia de caracteres de entrada>, <separadores: caracteres de busca> e
// <intervalo: quantos caracteres contando com o atual devem ser lidos a partir do indexador>
// Returna: <char: caracter da ocorrência encontrada> 
char proximoCharNaCadeiaIntervalo(char *cadeia, char *separadores, int intervalo){
    // contadores
    int i, k;

    // busca a próxima ocorrência de um dos separadores nos <intervalo> primeiros
    // caracteres
    for (i = 0; cadeia[i] != '\0' && i < intervalo; i++)
        for (k = i; separadores[k] != '\0'; k++)
            if (cadeia[i] == separadores[k])
                goto fim; // finaliza

    // retorna primeira ocorrência entre os separadores,
    // o char na posição final do intervalo ou '\0' se chegar
    //  no final da linha
    fim: return cadeia[i];
}