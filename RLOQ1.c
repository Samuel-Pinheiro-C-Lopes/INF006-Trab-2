
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define tam_max_linha (1000)
#define NAO_E_LISTA (-11) 

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
};


CbctListas* iniciarCbctListas();
Lista* iniciarLista();
ItemLista* iniciarItemLista(int valor);
void inserirItemLista(Lista *lista, int valor);
void inserirLista(CbctListas *cbct, Lista *novaLista);
int lerLista(Lista* novaLista, char entrada[], int* countLinha);
char* obterSubCadeia(char *cadeia, char separador);
int cadeiaParaInteiro(char* cadeia);
int proximosNaCadeia(char *cadeia, char* separadores);

int main(){
    // cabeçote das listas, será usado ao longo do tempo de execução da aplicação 
    CbctListas* cbct = iniciarCbctListas();

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

// Summary: insere uma lista a uma lista de listas na sua posição certa, considerando a soma dos
// elementos dela
// Parameters: <cbct: cabeçote da lista de listas> e <novaLista: nova lista a ser inserida>
// Returns: <void>
void inserirLista(CbctListas *cbct, Lista *novaLista){
    // se a novaLista tiver a soma inferior às outras
    if (cbct->inicio->soma > novaLista->soma){
        // insere
        novaLista->prox = cbct->inicio;
        cbct->inicio = novaLista;
    }

    // lista atual
    Lista *atualLista = cbct->inicio;

    // encontra a posição correta, final da lista de listas ou posição na qual
    // a soma do próximo é maior
    while (atualLista->prox != NULL )
        if (atualLista->prox->soma < novaLista->soma)
            atualLista = atualLista->prox;

    // insere
    novaLista->prox = atualLista->prox;
    atualLista->prox = novaLista;
}

// Summary: adiciona um item de lista a uma lista em sua posição correta, ordenada crescentemente
// Parameters: <lista: cabeçote da lista cujo elemento deve ser inserido> e <novoValor: chave do
// novo elemento da lista>
// retorno: <void>
void inserirItemLista(Lista *lista, int novoValor){
    // declara e inicializa o item
    ItemLista* item = iniciarItemLista(novoValor);

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
        while(atual->prox != NULL)
            if (atual->prox->valor < novoValor)
                atual = atual->prox;

        // insere
        item->prox = atual->prox;
        atual->prox = item->prox;
    }
}

// Summary: Lê todas as listas presentes no arquivo de entrada, atribuindo-as ao cabeçote
// Parameters: <cbct: cabeçote das listas a ser preenchido> e <entrada: arquivo de entrada>
// Returns: <void>
void lerTodasListas(CbctListas* cbct, FILE *entrada){
    // linha a ser lida
    static char linha[tam_max_linha];
    int countLinha;

    Lista* novaLista = iniciarLista();

    // enquanto houver linhas a serem lidas no arquivo de entrada
    while (fgets(linha, tam_max_linha, entrada) != NULL){
        countLinha = 0;
        // enquanto houverem listas na linha, leia a lista e atribua
        while (lerLista(novaLista, linha, &countLinha) != NAO_E_LISTA) {
            // insere a nova lista em sua posição correta
            inserirLista(cbct, novaLista);
            // nova lista
            novaLista = iniciarLista();
        }
    }

    // libera lista alocada excedentemente
    free(novaLista);
}


int lerLista(Lista* lista, char linha[], int *countLinha){ 

    return 1;
}

// Sumário: busca pela posição em uma cadeia da primeira ocorrência de um ou mais 
// caracteres de separação
// Parâmetros: <cadeia: cadeia de caracteres de entrada> e <separadores: caracteres de busca>
// Returna: <int: índice de posição da ocorrência ou -1 caso não haja> 
int proximosNaCadeia(char *cadeia, char* separadores){
    // contadores
    int i, k;

    // busca a primeira ocorrência de um dos separadores na cadeia de entrada
    for (i = 0; cadeia[i] != '\0'; i++)
    {
        printf("%d", i);
        for (k = 0; separadores[k] != '\0'; k++)
            if (cadeia[i] == separadores[k])
                return i;
    }
    
    return -1;
}

// Summary: obtém uma cadeia de caracteres como entrada tal como um separador, retorna
// endereço para uma subcadeia contendo o início até o separador - sem o incluir
// Parameters: <cadeia: cadeia de caracteres de entrada> e <separador: caracter de separação>
// Returns: <char *: endereço da variável estática "subcadeia", contendo a subcadeia lida>
char* obterSubCadeia(char *cadeia, char separador){
    // subcadeia
    static char subcadeia[tam_max_linha];
    int i; // contador

    // copia até sentinelas - tamanho máximo, separador e fim de linha
    for (i = 0; cadeia[i] != separador && cadeia[i] != '\0' && i < tam_max_linha - 1; i += sizeof(char))
        subcadeia[i] = cadeia[i];

    // final da subcadeia
    subcadeia[++i] = '\n';

    // endereço da subcadeia
    return &subcadeia;
}

// Summary: converte um texto para seu equivalente numérico inteiro
// Parameters: <cadeia: indexador da cadeia a ser convertida>
// Returns: <int: numero resultante>
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
    while (*cadeia != '\0')
    {
        inteiro *= 10; // incrementa o número de algarismos e ordem de grandeza
        inteiro += *cadeia - 48;  // atribui o novo algarismo em sua casa atual
        cadeia += sizeof(char); // incrementa o indexador
    }

    if (negativo)
        inteiro *= -1;

    return inteiro; // resultado
}


/*
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
