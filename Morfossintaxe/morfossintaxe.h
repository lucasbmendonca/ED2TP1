#ifndef MORFOSSINTAXE_H_INCLUDED
#define MORFOSSINTAXE_H_INCLUDED

/*Estrutura da Lista de Palavra.*/
typedef struct palavra{
    char texto[100]; //Palavra da frase original.
    char raiz[100]; //Raiz da palavra.
    double percentagem; //Certeza da ferramenta em relacao a análise realizada.
    int quantidade; //Quantas vezes a palavra se repete.
    int tamanho; //Tamanho da palavra.
    struct palavra *proximo; //Próxima palavra.
    struct palavra *anterior; //Palavra anterior.
} Palavra;

/*Estrutura de Lista de Categoria de Palavras de acordo com sua classificação.*/
typedef struct categoria{
    char texto[10]; //Análise morfossintática.
    int qtd_palavras; //Quantidade de palavras que a categoria possui.
    Palavra *palavra; //Inicio da lista de palavras (Lista de Lista).
    struct categoria *proximo; //Proxima categoria.
    struct categoria *anterior; //Categoria anterior.
} Categoria;

/*Estrutura para Lista de Frequencias.*/
typedef struct frequencia{
    char variavel[100]; //Variável em estudo: x.
    int freq_abs; //Frequência absoluta: ni.
    float freq_rel; //Frequencia relativa: fi.
    int freq_abs_acumulada; //Frequencia absoluta acumulada: Ni.
    float freq_rel_acumulada; //Frequencia relativa acumulada: Fi.
    struct frequencia *proximo; //Proxima frequencia
} Frequencia;

/*Lista de Média Aritmetica e Desvio Padrão das Categorias de Palavras com base na certeza de etiquetação.*/
typedef struct medDesvCat{
    char categoria[10]; //Categoria de uma palavra.
    double media_aritmetica; //Media aritmética com base na medida de etiquetação da categoria.
    double desvio_padrao; //Desvio padrão com base na medida de etiquetação da categoria.
    struct medDesvCat *proximo; //Proxima informação de medidas.
} MedDesvCat;

/*Estrutura de Lista de frequencia das palavras para implementação de Quartil*/
typedef struct freqPalavras{
    char palavra[100];
    int quantidade;
    struct freqPalavras *proximo;
} FreqPalavras;

/*Estrutura para histograma de probabilidades*/
typedef struct histograma{
    double limite_inferior;
    double limite_superior;
    int freq_abs;
    double freq_rel;
    double ponto_medio;
    struct histograma *proximo;
} Histograma;

typedef struct frequenciaCerteza{
    double certeza;
    int frequencia;
    struct frequenciaCerteza* proximo;
} FrequenciaCerteza;

/*Inicio da lista de categorias com palavras.*/
Categoria *categoria_header;

/*Inicio da lista de frequencias da categoria gramatical utilizada.*/
Frequencia *freq_categoria_h;

/*Inicio da lista de frequencias do tamanho das palavras.*/
Frequencia *freq_tamanho_palavra_h;

/*Inicio da lista de media e desvio padrão com base na certeza de etiquetação*/
MedDesvCat *med_desv_h;

/*Ultimo da lista de media e desvio padrao*/
MedDesvCat *med_desv_ultimo;

/*Inicio da Frequencia de Palavras*/
FreqPalavras *freq_palavras_h;

/*Inicio da lista do histograma de probabilidades com base na certeza de etiquetação*/
Histograma* histograma_h;
Histograma* histograma_fim;
FrequenciaCerteza* freq_certeza_h;
double maiorCertezaHistograma;
double menorCertezaHistograma;

int totalCategorias = 0; //Total de categorias durante a execução do programa.
int totalPalavras = 0; //Total de palavras lidas do arquivo.

/*Medidas de localização e dispersao, relativas ao tamanho das palavras: media
aritmetica, mediana, moda e desvio padrao.*/
int totalTamanhoPalavras = 0; //Quantos diferentes tamanhos de palavras existem.
double ma_tam_palavra = 0; //Média Aritmética dos tamanhos de palavras.
int mediana_tam_palavra = 0; //Mediana dos tamanhos de palavras.
int moda_tam_palavra = 0; //Moda dos tamanhos de palavras.
double desvio_padrao_tam_palavra = 0; //Desvio padrão dos tamanhos de palavras.
int somaFreqPalavras = 0; //Soma da quantidade de Frequencia das palavras.
int mediana_posicao = 0;

float quartil_1;
float quartil_2;
float quartil_3;

Categoria* getResultado();
void iniciar();
void destroi();
int insere(char* texto, char* raiz, char* categoria, double percentagem);
bool checkInput(char value[]);

Palavra* acharMeioPalavra(Palavra *comeco_el, Palavra *ultimo_el);
Categoria* acharMeioCategoria(Categoria *comeco_el, Categoria *ultimo_el);
Palavra* buscaBinariaPalavra(Palavra *p, char* texto);
Categoria* buscaBinariaCategoria(Categoria *l, char* texto);

int insereCategoria(Categoria *p_new, Categoria *p_elemento);
int inserePalavra(Palavra  *p_new, Palavra *p_palavra, Palavra **p_header);
int calcFreqMed(Categoria *lista); //Calcular frequencias e medidas das questões apresentadas no trabalho prático.
int insereFrequenciaCatOrdenada(Frequencia** frequencia, Frequencia** header); //Frequencia das categorias.
int insereFrequenciaTamOrdenada(Frequencia** frequencia, Frequencia** header); //Frequencia da incidencia do tamanho das palavras.
int insereMedDesv(MedDesvCat** med_desv); //Insere na lista de media e desvio padrão com base na etiquetação.
int insereFreqPalavraOrdenada(Palavra* palavra); //Insere na lista de Frequencia das palavras.
int getQuartil(char texto[]);//Retorna quartil de acordo com palavra informada
void calculaQuartil(); //Calcula Quartis das Frequencias de Palavras;
int insereHistograma(double limite_inferior, double limite_superior, int frequencia, double ponto_medio);
int insereFrequenciaCertezaOrd(Palavra *palavra);

void showFreqTamPalavras();
void showFreqCategorias();
void showMedDesvCat();
void showLocDisp();
void showFreqPalavras();
void calcHistograma();

#endif // MORFOSSINTAXE_H_INCLUDED