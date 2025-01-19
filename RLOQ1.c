
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define tam_max_linha (1000)
#define tam_max_cadeia (255)
#define NAO_E_LISTA (-11) 
#define FIM_LINHA (-21)
#define NOVA_LISTA (-22)
#define TERMINADOR_NULO (-23)

typedef struct itemLista ItemLista;
typedef struct lista Lista;
typedef struct cbctlistas CbctListas;

// item da lista
struct itemLista{
    ItemLista *prox;
    int valor;
};

// cabeçote para itens de uma lista
struct lista{
    ItemLista *inicio;
    Lista *prox;
    int soma;
};

// cabeçote para as listas
struct cbctlistas{
    Lista *inicio;
    CbctListas *prox;
    char cadeia[tam_max_linha]; // representa a string da linha de listas correspondente
};

// inicializações
CbctListas* iniciarCbctListas();
Lista* iniciarLista();
ItemLista* iniciarItemLista(int valor);
// inserções
void inserirCbctListas(CbctListas *cbctInicio, CbctListas *novoCbct);
CbctListas* novoCbctListas(CbctListas *cbctInicio);
void inserirItemListaOrdenado(Lista *lista, int valor);
void inserirListaOrdenada(CbctListas *cbct, Lista *novaLista);
void atribuirCadeiaCbct(CbctListas *cbct);
// leitura
void lerTodasListas(CbctListas* cbct, FILE *entrada);
int lerLista(Lista* novaLista, char entrada[], int* countLinha);
// utilidades cadeia
char* obterSubCadeia(char *cadeia, char separador);
int preencherCadeiaInicializada(char *cadeia, char *conteudo);
int preencherCadeia(char *cadeia, char *conteudo);
int cadeiaParaInteiro(char* cadeia);
char* InteiroParaCadeia(int inteiro);
int checarCharInteiro(char c);
// navegação cadeia
int proximosNaCadeia(char *cadeia, char* separadores); 
int proximosOuFimNaCadeia(char *cadeia, char *separadores); 
char proximoCharNaCadeiaIntervalo(char *cadeia, char *separadores, int intervalo);
// math
int exponencial(int inteiro, int expoente);
int numAlgsInteiro(int inteiro);



int main(){
    // cabeçote das listas, será usado ao longo do tempo de execução da aplicação 
    CbctListas* cbctInicio = iniciarCbctListas();

    // arquivo de testes
    FILE *entrada = fopen("L1Q1.in" ,"r");

    // execução de teste
    if (entrada == NULL) 
        return 1;
    else 
        lerTodasListas(cbctInicio, entrada);

    // leitura de teste
    // imprime no terminal da forma com que o arquivo de saída se assemelha, 
    // basta adaptar para escrever em arquivo
    for (CbctListas *cbctAtual = cbctInicio; cbctAtual != NULL; cbctAtual = cbctAtual->prox)
        printf("%s\n", cbctAtual->cadeia);

    return 1;
}

// declara, aloca e inicializa um novo item de lista
ItemLista* iniciarItemLista(int valor){
    ItemLista *itemLista = (ItemLista*) malloc(sizeof(ItemLista));
    itemLista->prox = NULL; 
    itemLista->valor = valor;
    return itemLista;
}

// declara, aloca e inicializa um novo cabeçote de listas
CbctListas* iniciarCbctListas(){
    CbctListas *listas = (CbctListas*) malloc(sizeof(CbctListas));
    listas->inicio = NULL; 
    listas->prox = NULL;
    return listas;
}

// declara, aloca a inicializa uma nova lista
Lista* iniciarLista(){
    Lista *lista = (Lista*) malloc(sizeof(Lista));
    lista->soma = 0;
    lista->inicio = NULL;
    lista->prox = NULL;
    return lista;
}

void inserirCbctListas(CbctListas *cbctInicio, CbctListas *novoCbct){
    while(cbctInicio->prox != NULL)
        cbctInicio = novoCbct;
    
    cbctInicio->prox = novoCbct;
}

CbctListas* novoCbctListas(CbctListas *cbctInicio){
    CbctListas *novoCbct = iniciarCbctListas();
    inserirCbctListas(cbctInicio, novoCbct);
    return novoCbct;
}

// Sumário: insere uma lista a uma lista de listas na sua posição certa, considerando a soma dos
// elementos dela
// Parâmetros: <cbct: cabeçote da lista de listas> e <novaLista: nova lista a ser inserida>
// Retorna: <void>
void inserirListaOrdenada(CbctListas *cbct, Lista *novaLista){
    // se a novaLista tiver a soma inferior às outras
    if (cbct->inicio == NULL || cbct->inicio->soma > novaLista->soma){
        // insere
        novaLista->prox = cbct->inicio;
        cbct->inicio = novaLista;
    }
    else {
        // lista atual
        Lista *atualLista = cbct->inicio;

        // encontra a posição correta, final da lista de listas ou posição na qual
        // a soma do próximo é maior
        while (atualLista->prox != NULL && atualLista->prox->soma < novaLista->soma)
                atualLista = atualLista->prox;

        // nesse caso, a última inserida irá persistir
        if (atualLista->prox != NULL && atualLista->prox->soma == novaLista->soma){
            // substitui
            novaLista->prox = atualLista->prox->prox;
            free(atualLista->prox);
            atualLista->prox = novaLista;
        }else{
            // insere
            novaLista->prox = atualLista->prox;
            atualLista->prox = novaLista;
        }
    }
}

// Sumário: adiciona um item de lista a uma lista em sua posição correta, ordenada crescentemente
// Parâmetros: <lista: cabeçote da lista cujo elemento deve ser inserido> e <novoValor: chave do
// novo elemento da lista>
// retorno: <void>
void inserirItemListaOrdenado(Lista *lista, int novoValor){
    // declara e inicializa o item
    ItemLista* item = iniciarItemLista(novoValor);

    // incrementa a soma
    lista->soma += novoValor;

    // insere na posição correta, ordenando
    ItemLista* atual = lista->inicio;

    if (atual == NULL || atual->valor > novoValor){
        // insere
        item->prox = lista->inicio;

        // atualiza o cabeçote
        lista->inicio = item;
    }
    else{
        // encontra o final ou posição correta - próximo valor é maior que o novo
        while(atual->prox != NULL && atual->prox->valor < novoValor)
        {
            atual = atual->prox;
        }

        // insere
        item->prox = atual->prox;
        atual->prox = item;
    }
}

// Sumário: Lê todas as listas presentes no arquivo de entrada, atribuindo-as ao cabeçote
// Parâmetros: <cbct: cabeçote das listas a ser preenchido> e <entrada: arquivo de entrada>
// Retorna: <void>
void lerTodasListas(CbctListas* cbctAtual, FILE *entrada){
    // linha a ser lida
    static char linha[tam_max_linha];
    int contLinha;
    CbctListas *cbctPreenchido;
    Lista *novaLista;
    int retorno;

    // enquanto houver linhas a serem lidas no arquivo de entrada
    while (fgets(linha, tam_max_linha, entrada) != NULL){
        retorno = NOVA_LISTA;
        cbctPreenchido = cbctAtual;
        novaLista = iniciarLista();
        contLinha = 0;
        // enquanto houverem listas na linha, leia a lista e atribua
        while(retorno == NOVA_LISTA)
        {
            retorno = lerLista(novaLista, linha, &contLinha);
            inserirListaOrdenada(cbctPreenchido, novaLista);
            novaLista = iniciarLista();
        }
        atribuirCadeiaCbct(cbctPreenchido);
        cbctAtual = novoCbctListas(cbctAtual);
    }

    // libera cabeçote excedente
    cbctPreenchido->prox = NULL;
    free(cbctAtual);
    // libera lista alocada excedentemente
    free(novaLista);
}

// Sumário: Lê uma lista de uma entrada de texto, cujos números inteiros devem ser
// espaçados em 1 entre si e a letra 's' demarca o início de outra lista. Navega pelos
// espaços.
// Parâmetros: <lista: lista a ser preenchida>, <linha: texto de entrada> e <contLinha: índice atual
// do texto de entrada
// Retorno: <int: NAO_E_LISTA se for chamado para um formato inválido ou 1 se suceder na
// inserção dos elementos>
int lerLista(Lista* lista, char linha[], int *contLinha){ 

    while (linha[*contLinha] != '\0'){
        *contLinha += proximosOuFimNaCadeia(&linha[*contLinha], " ");
        switch(proximoCharNaCadeiaIntervalo(&linha[*contLinha], "s\n", 1))
        {
            case ('\0'): goto fim; // fim string
            case ('\n'): return FIM_LINHA; // pula linha
            case ('s'): return NOVA_LISTA; // nova string
                     // insere                       // converte       // obtém substring
            default: inserirItemListaOrdenado(lista, cadeiaParaInteiro(obterSubCadeia(&linha[*contLinha + 1], ' ')));
        }
    }

    fim: return TERMINADOR_NULO;
}

// Sumário: busca pela posição em uma cadeia da primeira ocorrência de um ou mais 
// caracteres de separação
// Parâmetros: <cadeia: cadeia de caracteres de entrada> e <separadores: caracteres de busca>
// Returna: <int: índice de posição da ocorrência ou -1 caso não haja> 
int proximosNaCadeia(char *cadeia, char *separadores){
    // contadores
    int i, k;

    // busca a primeira ocorrência de um dos separadores na cadeia de entrada
    for (i = 1; cadeia[i] != '\0'; i++)
    {
        for (k = 0; separadores[k] != '\0'; k++)
            if (cadeia[i] == separadores[k])
                return i;
    }
    return -1;
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

// Sumário: converte um texto para seu equivalente numérico inteiro
// Parâmetros: <cadeia: indexador da cadeia a ser convertida>
// Retorna: <int: numero resultante>
int cadeiaParaInteiro(char* cadeia){
    // propriedades
    int inteiro = 0;
    int negativo = 0;

    // se for negativo
    if (*cadeia == '-')
    {
        negativo = 1; 
        cadeia += sizeof(char);
    }

    // enquanto  não encontrar o final da linha
    while (checarCharInteiro(*cadeia))
    {
        inteiro *= 10; // incrementa o número de algarismos e ordem de grandeza
        inteiro += *cadeia - 48;  // atribui o novo algarismo em sua casa atual
        cadeia += sizeof(char); // incrementa o indexador
    }

    if (negativo)
        inteiro *= -1;

    return inteiro; // resultado
}

int checarCharInteiro(char c){
    if (c > 47 && c < 58)
        return 1;
    else 
        return 0;
}

// Sumário: Versão segura de preencherCadeia, vai preenchendo a cadeia alvo com o conteúdo
// até que um dos indexadores aponte para um terminador nulo.
// Não funciona para cadeia de caracteres não inicializada
// Parâmetros: <cadeia: vetor de caracteres alvo a ser preenchido> e <conteudo:
// vetor de caracteres que deve preencher o alvo>
// Retorna: <int: quantos caracteres foram preenchidos>
int preencherCadeiaInicializada(char *cadeia, char *conteudo){
    int cont = 0;

    while (*(conteudo) != '\0' && *(cadeia) != '\0')
    {
        *(cadeia++) = *(conteudo++);
        cont++;
    }

    return cont;
}

// Sumário: Preenche a cadeia alvo com o conteúdo
// até o fim do conteúdo.
// Não checa pelo final da cadeia alvo, podendo tentar atribuir memória não alocada
// para a cadeia
// Parâmetros: <cadeia: vetor de caracteres alvo a ser preenchido> e <conteudo:
// vetor de caracteres que deve preencher o alvo>
// Retorna: <int: quantos caracteres foram preenchidos>
int preencherCadeia(char *cadeia, char *conteudo){
    int cont = 0;

    while (*(conteudo) != '\0')
    {
        *(cadeia++) = *(conteudo++);
        cont++;
    }

    return cont;
}

// Sumário: Obtém a quantidade de algarismos presentes em um número
// inteiro
// Parâmetros: <inteiro: número cujos algarismos devem ser contabilizados>
// Retorna: <int: quantidade de algarismos>
int numAlgsInteiro(int inteiro){
    static int numAlgs;

    if (inteiro == 0)
        return 1;
    else 
        for (numAlgs = 0; inteiro != 0; numAlgs++)
            inteiro /= 10;

    return numAlgs;
}

// Sumário: eleva um determinado número por um expoente
// Parâmetros: <inteiro: número a ser elevado, base> e <expoente>
// Retorna: <int: resultado da exponencialização>
int exponencial(int inteiro, int expoente){
    int resultado = inteiro;
    if (expoente == 0)
        return 1; // todo número ^0 é 1
    else if (expoente < 0)
        return -1; // erro
    else // eleve normalmente
        for (; expoente > 1; expoente--)
            resultado *= inteiro;

    return resultado;
}

// Sumário: Converte um inteiro para uma cadeia de caracteres
// com seu conteúdo
// Parâmetros: <inteiro: número inteiro a ser lido>
// Retorna: <char *: ponteiro para a cadeia resultante>
char* InteiroParaCadeia(int inteiro){
    static char cadeia[tam_max_cadeia];
    char *indexador = cadeia;
    int numGrandezaAtual;

    if (inteiro < 0)
    {
        *(indexador) = '-';
        inteiro *= -1;
        indexador += sizeof(char);
    }

    for (int numAlgs = numAlgsInteiro(inteiro); numAlgs > 0; numAlgs--)
    {
        numGrandezaAtual = inteiro / (exponencial(10, numAlgs - 1));
        *(indexador) = numGrandezaAtual + 48;
        inteiro -= numGrandezaAtual * exponencial(10, numAlgs - 1);
        indexador += sizeof(char);
    }
    *(indexador) = '\0';
    return cadeia;
}

// Sumário: Atribui o campo de cadeia do cabeçote de listas 
// com base nas listas presentes
// Parâmetros: <cbct: cabeçote a ter seu campo atribuído>
// Retorna: <void>
void atribuirCadeiaCbct(CbctListas *cbct){
    static char start[6] = "start"; 
    Lista *listaAtual;
    ItemLista *itemAtual;
    char *indexador = cbct->cadeia;

    // para cada lista no cabeçote
    for (listaAtual = cbct->inicio; listaAtual != NULL; listaAtual = listaAtual->prox)
    {
        // "start: "
        indexador += sizeof(char) * preencherCadeia(indexador, start);
        *(indexador++) = ' ';

        // para cada valor "<valor> "
        for (itemAtual = listaAtual->inicio; itemAtual != NULL; itemAtual = itemAtual->prox)
        {
            indexador += sizeof(char) * preencherCadeia(indexador, InteiroParaCadeia(itemAtual->valor));
            *(indexador++) = ' ';
        }
    }

    // termina a cadeia
    *(indexador++) = '\n';
    *(indexador++) = '\0';
}
