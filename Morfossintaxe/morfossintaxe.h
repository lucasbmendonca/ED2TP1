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

Categoria *categoria_header;

void iniciar();
int insere(char* texto, char* raiz, char* categoria, double percentagem);
Palavra* meioPalavra(Palavra *comeco_el, Palavra *ultimo_el);
Categoria* meioCategoria(Categoria *comeco_el, Categoria *ultimo_el);
Palavra* buscaBinariaPalavra(Palavra *p, char* texto);
Categoria* buscaBinariaCategoria(Categoria *l, char* texto);
int insereCategoria(Categoria *p_new, Categoria *p_elemento);
int inserePalavra(Palavra  *p_new, Palavra *p_palavra, Palavra **p_header);
void mostraResultado();
void destroi();
bool checkInput(char value[]);

#endif // MORFOSSINTAXE_H_INCLUDED
