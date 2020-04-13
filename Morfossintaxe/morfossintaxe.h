#ifndef MORFOSSINTAXE_H_INCLUDED
#define MORFOSSINTAXE_H_INCLUDED

//Estrutura da palavra
typedef struct palavra{
    char texto[100]; //palavra da frase original
    char raiz[100]; //raiz da palavra
    double percentagem; //Certeza da ferramenta em relacao a analise realizada
    int quantidade; //Quantas vezes a palavra se repete
    int tamanho; //tamanho da palavra
    struct palavra *proximo;
    struct palavra *anterior;
} Palavra;

// Categoria de palavras de acordo com sua classificação
typedef struct categoria{
    char texto[10]; //analise morfossintatica
    int qtd_palavras; //quantidade palavras
    Palavra *palavra;
    struct categoria *proximo;
    struct categoria *anterior;
} Categoria;

typedef struct frequencia{
    char variavel[100];
    int freq_abs;
    float freq_rel;
    int freq_abs_acumulada;
    float freq_rel_acumulada;
    struct frequencia *proximo;
} Frequencia;

Categoria *categoria_header;
Frequencia *frequencia_header;
int totalCategorias = 0;
int totalPalavras = 0;

void iniciar();
int insere(char* texto, char* raiz, char* categoria, double percentagem);
Palavra* meioPalavra(Palavra *comeco_el, Palavra *ultimo_el);
Categoria* acharMeio(Categoria *comeco_el, Categoria *ultimo_el);
Palavra* buscaBinariaPalavra(Palavra *p, char* texto);
Categoria* buscaBinaria(Categoria *l, char* texto);
int insereCategoria(Categoria *p_new, Categoria *p_elemento);
int inserePalavra(Palavra  *p_new, Palavra *p_palavra, Palavra **p_header);
Categoria* getResultado();
void destroi();
bool checkInput(char value[]);
int calcularFrequencias(Categoria *lista);

#endif // MORFOSSINTAXE_H_INCLUDED
