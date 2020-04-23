#ifndef MORFOSSINTAXE_H_INCLUDED
#define MORFOSSINTAXE_H_INCLUDED

/*Estrutura da palavra*/
typedef struct palavra{
    char texto[100]; //palavra da frase original
    char raiz[100]; //raiz da palavra
    double percentagem; //Certeza da ferramenta em relacao a analise realizada
    int quantidade; //Quantas vezes a palavra se repete
    int tamanho; //tamanho da palavra
    struct palavra *proximo;
    struct palavra *anterior;
} Palavra;

/*Categoria de palavras de acordo com sua classificação*/
typedef struct categoria{
    char texto[10]; //analise morfossintatica
    int qtd_palavras; //quantidade palavras
    Palavra *palavra;
    struct categoria *proximo;
    struct categoria *anterior;
} Categoria;

/*Tabela de Frequencias*/
typedef struct frequencia{
    char variavel[100];
    int freq_abs;
    float freq_rel;
    int freq_abs_acumulada;
    float freq_rel_acumulada;
    struct frequencia *proximo;
} Frequencia;

/*Tabela Média Aritmetica e desvio padrão das Categorias de Palavras com base na certeza de etiquetação*/
typedef struct medDesvCat{
    char categoria[10];
    double media_aritmetica;
    double desvio_padrao;
    struct medDesvCat *proximo;
} MedDesvCat;

/*Inicio da lista de categorias com palavras*/
Categoria *categoria_header;

/*Inicio da lista de frequencias da categoria gramatical utilizada*/
Frequencia *freq_categoria_h; //h = header

/*Inicio da lista de frequencias do tamanho das palavras*/
Frequencia *freq_tamamanho_palavra_h;

/*Inicio da lista de media e desvio padrão com base na certeza de etiquetação*/
MedDesvCat *med_desv_h;
/*Ultimo da lista*/
MedDesvCat *med_desv_ultimo;


int totalCategorias = 0;
int totalPalavras = 0;

/*1*/
void iniciar();
int insere(char* texto, char* raiz, char* categoria, double percentagem);
Palavra* acharMeioPalavra(Palavra *comeco_el, Palavra *ultimo_el);
Categoria* acharMeioCategoria(Categoria *comeco_el, Categoria *ultimo_el);
Palavra* buscaBinariaPalavra(Palavra *p, char* texto);
Categoria* buscaBinariaCategoria(Categoria *l, char* texto);
int insereCategoria(Categoria *p_new, Categoria *p_elemento);
int inserePalavra(Palavra  *p_new, Palavra *p_palavra, Palavra **p_header);
Categoria* getResultado();
void destroi();
bool checkInput(char value[]);

/*2*/
int calcularFrequencias(Categoria *lista);
int insereFrequenciaCatOrdenada(Frequencia** frequencia, Frequencia** header); //Frequencia das categorias

/*3*/
int insereFrequenciaTamOrdenada(Frequencia** frequencia, Frequencia** header); //Frequencia da incidencia do tamanho das palavras

/*4*/
int insereMedDesv(MedDesvCat** med_desv);

#endif // MORFOSSINTAXE_H_INCLUDED
