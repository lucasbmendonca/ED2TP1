#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>
#include "morfossintaxe.h"

/*Inicializa listas do programa*/
void iniciar()
{
    categoria_header = NULL;
    freq_categoria_h = NULL;
    freq_tamanho_palavra_h = NULL;
}

/*Libera memória do programa destruindo as listas*/
void destroi()
{
    //Destroi lista de categorias com suas palavras
    if (categoria_header != NULL)
    {
        Categoria *elemento_aux;
        Categoria *l_aux = categoria_header;
        Palavra *p_aux, *palavra_aux;
        while (l_aux != NULL)
        {
            elemento_aux = l_aux;
            p_aux = l_aux->palavra;
            l_aux = l_aux->proximo;
            free(elemento_aux);
            while (p_aux != NULL)
            {
                palavra_aux = p_aux;
                p_aux = p_aux->proximo;
                free(palavra_aux);
            }
        }
    }
    /*Destroi lista de frequencias de tamanho da palavra*/
    Frequencia *frequencia = freq_tamanho_palavra_h;
    while (frequencia != NULL)
    {
        Frequencia *frequencia_aux = frequencia->proximo;
        free(frequencia);
        frequencia = frequencia_aux;
    }
    /*Destroi lista de frequencias de categorias*/
    frequencia = freq_categoria_h;
    while (frequencia != NULL)
    {
        Frequencia *frequencia_aux = frequencia->proximo;
        free(frequencia);
        frequencia = frequencia_aux;
    }
}

/*Retorna resultado da lista principal do programa: Categorias ordenadas com suas palavras ordenadas*/
Categoria *getResultado()
{
    if (categoria_header != NULL)
    {
        Categoria *l_aux = categoria_header;
        Palavra *p_aux, *palavra_aux;
        printf("\n*************************RESULTADO*************************\n");
        while (l_aux != NULL)
        {
            printf("----> Categoria: %s || Quantidade: %d\n", l_aux->texto, l_aux->qtd_palavras);
            p_aux = l_aux->palavra;
            while (p_aux != NULL)
            {
                printf("<.> Palavra: %s || Tamanho: %d || Quantidade: %d\n", p_aux->texto, p_aux->tamanho, p_aux->quantidade);
                p_aux = p_aux->proximo;
            }
            l_aux = l_aux->proximo;
        }
        printf("***********************************************************\n");
    }
    return categoria_header;
}

/*Verifica input do TXT*/
bool checkInput(char value[])
{
    /*Verificações ASCII*/
    int lenght = strlen(value);
    int i = 0, result = 0;
    char c1 = value[0], c2;

    if (lenght > 1)
    {
        /*Somente caracteres do alfabeto*/
        if (!(c1 >= 65 && c1 <= 90) || (c1 >= 97 && c1 <= 122))
        {
            do
            {
                c2 = value[i++];
                if (((c2 >= 65 && c2 <= 90) || (c2 >= 97 && c2 <= 122)))
                {
                    return true;
                }
                else
                {
                    return false;
                }
            } while (c2 != '\000');
            /*Caracteres iguais [;;...'']
            Ex.: Palavra 1 = ;;;
                 Palavra 2 = --
            Não devem ser inseridos!
            Se o numero de caracteres iguais for igual ao tamanho da palavra, 
            a palavra possui todos os caracteres idênticos.*/
            if (!(result != lenght + 1))
            {
                return false;
            }
            return true;
        }
        else
        {
            return true;
        }
    }
    else
    {
        if ((c1 >= 65 && c1 <= 90) || (c1 >= 97 && c1 <= 122))
        {
            return true;
        }
        return false;
    }
}

/*Retorna a palavra que está no meio da Lista de Palavras*/
Palavra *acharMeioPalavra(Palavra *comeco_el, Palavra *ultimo_el)
{

    if (comeco_el == NULL)
    {
        return NULL;
    }
    if (comeco_el->proximo == ultimo_el)
    {
        return comeco_el;
    }

    /*Variaveis auxiliares*/
    Palavra *p_devagar = comeco_el;
    Palavra *p_rapido = comeco_el->proximo;

    while (p_devagar != ultimo_el)
    {
        if (p_rapido == NULL)
        {
            return p_devagar;
        }

        p_rapido = p_rapido->proximo;
        if (p_rapido != ultimo_el)
        {
            /*Ja chegou ao fim da lista*/
            if (p_rapido == NULL)
            {
                p_devagar = p_devagar->proximo;
                continue;
            }
            p_rapido = p_rapido->proximo;
        }
    }
    return p_devagar;
}

/*Busca uma palavra através de Busca Binária*/
Palavra *buscaBinariaPalavra(Palavra *p, char *texto)
{

    Palavra *palavra_inicio = p;
    Palavra *palavra_fim = NULL;
    Palavra *palavra_meio, *palavra_anterior;

    palavra_meio = acharMeioPalavra(palavra_inicio, palavra_fim);
    /*Se nao encontra a palavra, retorna ela mesma*/
    if (palavra_meio == NULL)
    {
        return p;
    }

    for (;;)
    {
        int compare = strcmp(texto, palavra_meio->texto);
        if (compare == 0)
        {
            totalPalavras++;
            return palavra_meio;
        }
        else if (compare < 0)
        {
            palavra_fim = palavra_meio;
        }
        else if (compare > 0)
        {
            palavra_inicio = palavra_meio->proximo;
        }

        palavra_anterior = palavra_meio;
        palavra_meio = acharMeioPalavra(palavra_inicio, palavra_fim);

        if (palavra_meio == NULL || palavra_anterior == palavra_meio)
        {
            totalPalavras++;
            return palavra_anterior;
        }
    }
}

/*Retorna a categoria que está no meio da Lista de Categorias*/
Categoria *acharMeioCategoria(Categoria *comeco_el, Categoria *ultimo_el)
{

    if (comeco_el == NULL)
    {
        return NULL;
    }
    if (comeco_el->proximo == ultimo_el)
    {
        return comeco_el;
    }

    /*Variaveis auxiliar*/
    Categoria *p_devagar = comeco_el;
    Categoria *p_rapido = comeco_el->proximo;

    while (p_devagar != ultimo_el)
    {
        if (p_rapido == NULL)
        {
            return p_devagar;
        }

        p_rapido = p_rapido->proximo;
        if (p_rapido != ultimo_el)
        {
            /*Ja chegou ao fim da lista*/
            if (p_rapido == NULL)
            {
                p_devagar = p_devagar->proximo;
                continue;
            }
            p_rapido = p_rapido->proximo;
        }
    }
    return p_devagar;
}

/*Busca uma categoria através de busca binária*/
Categoria *buscaBinariaCategoria(Categoria *l, char *texto)
{
    /*Auxiliares*/
    Categoria *elemento_comeco = l;
    Categoria *elemento_ultimo = NULL;
    Categoria *elemento_meio, *elemento_anterior;

    elemento_meio = acharMeioCategoria(elemento_comeco, elemento_ultimo);
    if (elemento_meio == NULL)
    {
        return l;
    }

    for (;;)
    {
        int compare = strcmp(texto, elemento_meio->texto);
        if (compare == 0)
        {
            /*Adiciona +1 a frequencia da classificacao*/
            elemento_meio->qtd_palavras++;
            return elemento_meio;
        }
        else if (compare < 0)
        {
            elemento_ultimo = elemento_meio;
        }
        else if (compare > 0)
        {
            elemento_comeco = elemento_meio->proximo;
        }

        elemento_anterior = elemento_meio;
        elemento_meio = acharMeioCategoria(elemento_comeco, elemento_ultimo);
        if (elemento_meio == NULL || elemento_anterior == elemento_meio)
        {
            return elemento_anterior;
        }
    }
}

/*Insere Categoria na lista de categorias de forma ordenada*/
int insereCategoria(Categoria *p_new, Categoria *p_elemento)
{
    int compare = strcmp(p_new->texto, p_elemento->texto);
    if (compare < 0)
    {
        p_new->anterior = p_elemento->anterior;
        p_new->proximo = p_elemento;
        /*Inserir entre dois elementos*/
        if (p_elemento->anterior != NULL)
        {
            p_elemento->anterior->proximo = p_new;
            p_elemento->anterior = p_new;
        }
        /*Inserindo no começo*/
        else
        {
            p_elemento->anterior = p_new;
            p_elemento = p_new;
            categoria_header = p_elemento;
        }
        return true;
    }
    else if (compare > 0)
    {
        p_new->proximo = p_elemento->proximo;
        /*Inserir entre dois elementos*/
        if (p_elemento->proximo != NULL)
        {
            p_new->anterior = p_elemento->proximo->anterior;
            p_elemento->proximo->anterior = p_new;
        }
        /*Inserindo no final*/
        else
        {
            p_new->anterior = p_elemento;
        }
        p_elemento->proximo = p_new;
        return true;
    }
    return false;
}

/*Insere palavra na lista de palavras de forma ordenada*/
int inserePalavra(Palavra *p_new, Palavra *p_palavra, Palavra **p_header)
{
    int compare = strcmp(p_new->texto, p_palavra->texto);

    if (compare < 0)
    {
        /*Adicionando +1 a frequencia*/
        p_new->quantidade++;

        p_new->anterior = p_palavra->anterior;
        p_new->proximo = p_palavra;
        /*Inserir entre dois elementos*/
        if (p_palavra->anterior != NULL)
        {
            p_palavra->anterior->proximo = p_new;
            p_palavra->anterior = p_new;
        }
        /*Inserindo no começo da lista de palavras*/
        else
        {
            p_palavra->anterior = p_new;
            p_palavra = p_new;
            *p_header = p_new;
        }
        return true;
    }
    else if (compare > 0)
    {
        /*Adicionando +1 a frequencia*/
        p_new->quantidade++;

        p_new->proximo = p_palavra->proximo;
        /*Inserir entre dois elementos*/
        if (p_palavra->proximo != NULL)
        {
            p_new->anterior = p_palavra->proximo->anterior;
            p_palavra->proximo->anterior = p_new;
        }
        /*Inserindo no final*/
        else
        {
            p_new->anterior = p_palavra;
        }

        p_palavra->proximo = p_new;
        return true;
    }
    else if (compare == 0)
    {
        p_palavra->quantidade++;
        return true;
    }

    return false;
}

/*Insere linha do TXT lido com a categoria, palavra e propriedades*/
int insere(char *texto, char *raiz, char *categoria, double percentagem)
{
    Categoria *new_element = (Categoria *)malloc(sizeof(Categoria));
    strcpy(new_element->texto, categoria);
    new_element->proximo = NULL;
    new_element->anterior = NULL;

    Palavra *new_palavra = (Palavra *)malloc(sizeof(Palavra));
    strcpy(new_palavra->texto, texto);
    strcpy(new_palavra->raiz, raiz);
    new_palavra->tamanho = strlen(texto);
    new_palavra->percentagem = percentagem;
    new_palavra->quantidade = 0;
    new_palavra->proximo = NULL;
    new_palavra->anterior = NULL;

    new_element->palavra = new_palavra;
    new_element->qtd_palavras = 1;

    if (categoria_header == NULL)
    {
        new_element->palavra->quantidade = 1;
        categoria_header = new_element;
        return true;
    }
    else
    {
        Palavra *palavra, *palavra_header_temp;
        Categoria *categoria = buscaBinariaCategoria(categoria_header, new_element->texto);
        bool flag_categ_existe = false;
        if (categoria != NULL)
        {
            /*Se a categoria ja esta na lista, guardo inicio da lista de palavras*/
            if (strcmp(new_element->texto, categoria->texto) == 0)
            {
                palavra_header_temp = categoria->palavra;
                flag_categ_existe = true; //Categoria ja esta presente na lista
            }
            /*Se nao estiver, o inicio da lista de palavras esta sendo criado agora*/
            else
            {
                palavra_header_temp = new_element->palavra;
            }

            /*Se a categoria nao existe, é inserida*/
            if (!flag_categ_existe)
            {
                flag_categ_existe = insereCategoria(new_element, categoria);
                totalCategorias++;
            }

            /*Tratar palavra*/
            if (flag_categ_existe)
            { /*Se a categoria foi inserida com sucesso ou já existia na lista*/
                palavra = buscaBinariaPalavra(palavra_header_temp, new_element->palavra->texto);
                if (palavra != NULL)
                {
                    return inserePalavra(new_element->palavra, palavra, &categoria->palavra);
                }
            }
            else
            {
                return false;
            }
        }
    }
    return false;
}

/*Insere uma linha na lista de tabela de frequências do tamanho de uma palavra de forma ordenada*/
int insereFrequenciaTamOrdenada(Frequencia **frequencia, Frequencia **header)
{

    if (frequencia == NULL)
    {
        return false;
    }

    if (*header == NULL)
    {
        *header = *frequencia;
        totalTamanhoPalavras++;
        return true;
    }

    Frequencia *elemento = NULL;
    Frequencia *elemento_anterior = NULL;
    elemento = *header;
    int compare;
    do
    {
        /*Comparação dos tamanhos para inserir ordenado*/
        int variavelTam1 = atoi(elemento->variavel);      //Cast de string para INT
        int variavelTam2 = atoi((*frequencia)->variavel); //Cast de string para INT
        if (variavelTam1 < variavelTam2)
        {
            compare = -1;
        }
        else if (variavelTam1 > variavelTam2)
        {
            compare = 1;
        }
        else if (variavelTam1 == variavelTam2)
        {
            compare = 0;
        }

        if (compare < 0)
        {
            elemento_anterior = elemento;
            elemento = elemento->proximo;
        }
        else if (compare > 0 || compare == 0)
        {
            if (compare == 0)
            {
                elemento->freq_abs = elemento->freq_abs + (*frequencia)->freq_abs;
                elemento->freq_rel = (elemento->freq_abs / (float)totalPalavras) * 100;
                free((*frequencia));
                return true;
            }

            if (elemento_anterior == NULL)
            {
                (*frequencia)->proximo = *header;
                *header = (*frequencia);
                totalTamanhoPalavras++;
                return true;
            }
            elemento_anterior->proximo = (*frequencia);
            (*frequencia)->proximo = elemento;
            totalTamanhoPalavras++;
            return true;
        }
    } while (elemento != NULL);

    elemento_anterior->proximo = (*frequencia);
    totalTamanhoPalavras++;
    return true;
}

/*Insere uma linha da tabela de Frequencias da categoria gramatical utilizada de forma ordenada*/
int insereFrequenciaCatOrdenada(Frequencia **frequencia, Frequencia **header)
{
    if (frequencia == NULL)
    {
        return false;
    }

    if (*header == NULL)
    {
        *header = *frequencia;
        return true;
    }

    Frequencia *elemento = NULL;
    Frequencia *elemento_anterior = NULL;
    elemento = *header;
    do
    {
        int compare = strcmp(elemento->variavel, (*frequencia)->variavel);
        if (compare < 0)
        {
            elemento_anterior = elemento;
            elemento = elemento->proximo;
        }
        else if (compare > 0 || compare == 0)
        {
            if (compare == 0)
            {
                elemento->freq_abs = elemento->freq_abs + (*frequencia)->freq_abs;
                elemento->freq_rel = (elemento->freq_abs / (float)totalPalavras) * 100;
                free((*frequencia));
                return true;
            }

            if (elemento_anterior == NULL)
            {
                (*frequencia)->proximo = *header;
                *header = (*frequencia);
                return true;
            }
            elemento_anterior->proximo = (*frequencia);
            (*frequencia)->proximo = elemento;
            return true;
        }
    } while (elemento != NULL);

    elemento_anterior->proximo = (*frequencia);
    return true;
}

/*Insere na lista de categorias a media e desvio padrão com base na certeza de etiquetação da palavra nesta categoria
Como as categorias já estã ordenadas, insiro sempre no fim*/
int insereMedDesv(MedDesvCat **med_desv)
{

    if (med_desv_h == NULL)
    {
        med_desv_h = (*med_desv);
        med_desv_ultimo = med_desv_h;
        return true;
    }

    if (med_desv_ultimo != NULL)
    {
        med_desv_ultimo->proximo = (*med_desv);
        med_desv_ultimo = (*med_desv);
        return true;
    }

    return false;
}

/*Insere na lista de frequencia de palavras de forma ordenada*/
int insereFreqPalavraOrdenada(Palavra *palavra)
{
    if (palavra != NULL)
    {
        FreqPalavras *frequencia = (FreqPalavras *)malloc(sizeof(FreqPalavras));
        strcpy(frequencia->palavra, palavra->texto);
        frequencia->quantidade = palavra->quantidade;
        frequencia->proximo = NULL;

        if (freq_palavras_h == NULL)
        {
            freq_palavras_h = frequencia;
            somaFreqPalavras++;
            return true;
        }

        FreqPalavras* elemento_atual = freq_palavras_h;
        FreqPalavras* elemento_anterior = NULL;
        while(elemento_atual!=NULL){

            if(palavra->quantidade < elemento_atual->quantidade || palavra->quantidade == elemento_atual->quantidade)
            {
                if(elemento_anterior == NULL) //Inserindo no começo da lista
                { 
                    frequencia->proximo = freq_palavras_h;
                    freq_palavras_h = frequencia;
                    somaFreqPalavras++;
                    return true;
                }
                //Inserindo entre dois elementos
                frequencia->proximo = elemento_anterior->proximo;
                elemento_anterior->proximo = frequencia;
                somaFreqPalavras++;
                return true;
            }
            elemento_anterior = elemento_atual;
            elemento_atual = elemento_atual->proximo;
        }

        //Insere no fim
        if (elemento_atual == NULL)
        {
            elemento_anterior->proximo = frequencia;
            somaFreqPalavras++;
            return true;
        }
        return false;
    }
}

/*
  -------------------------------------------------------------------------------------------------
  Descrição: Metodo responsável por calcular as frequencias e medidas das questões 2, 3, 4, 5, 6.
  Aqui estará disposto um cabeçalho de forma que o trecho de código seja identificado e relacionado
  a cada questão do Trabalho Prático. 
  -------------------------------------------------------------------------------------------------
  OBS.: Somente um método foi usado para realizar o processamento de dados destas questões de 
  forma a otimizar a performance no cálculo de frequências e demais medidas, 
  a fim de não realizar iterações desnecessárias.
  -------------------------------------------------------------------------------------------------
  Resolução Questão 2: COD-001 > Frequencias Categoria Gramatical.
  Resolução Questão 3: COD-002 > Frequencias Tamanho das Palavras.
  Resolução Questão 4: COD-003 > Para cada categoria, calcular media aritmetica e 
                                 desvio padrão com base na certeza de etiquetação.
  Resolução Questão 5: COD-004 > Medidas de localização e dispersão, relativas ao 
                                 Tamanho das Palavras: média aritmética, mediana, moda e desvio padrão.
  Resolução Questão 6: COD-005 > Calcular os valores de quartis, de acordo com a categoria gramatical,
                                 para uso posteior na função getQuartil() que, dada uma palavra indicada 
                                 pelo utilizador, permite obter, o quartil a que pertence.
*/
int calcFreqMed(Categoria *lista)
{
    Frequencia *frequencia;
    Categoria *categoria = lista;

    while (categoria != NULL)
    {
        /*INI - COD-001
        Frequencia relativa a categoria de palavras
        */
        frequencia = (Frequencia *)malloc(sizeof(Frequencia));
        frequencia->proximo = NULL;
        strcpy(frequencia->variavel, categoria->texto);
        frequencia->freq_abs = categoria->qtd_palavras;
        frequencia->freq_rel = (frequencia->freq_abs / (float)totalPalavras) * 100;
        frequencia->freq_abs_acumulada = 0;
        frequencia->freq_rel_acumulada = 0;
        insereFrequenciaCatOrdenada(&frequencia, &freq_categoria_h);
        /*FIM - COD-001*/

        /*INI - COD-003
        Média Aritmetica e desvio padrão das Categorias de Palavras com base na certeza de etiquetação
        */
        MedDesvCat *med_desv_cat = (MedDesvCat *)malloc(sizeof(MedDesvCat));
        med_desv_cat->proximo = NULL;
        strcpy(med_desv_cat->categoria, categoria->texto);
        double somatorioCertezaFrequencia = 0;
        double media = 0;
        /*FIM - COD-003*/

        Palavra *palavra = categoria->palavra;
        while (palavra != NULL)
        {
            /*INI - COD-002
            Frequencias: Tamanho das Palavras
            */
            frequencia = (Frequencia *)malloc(sizeof(Frequencia));
            frequencia->proximo = NULL;
            char tamanho[20];
            sprintf(tamanho, "%d", palavra->tamanho); //Cast de int para string
            strcpy(frequencia->variavel, tamanho);
            frequencia->freq_abs = palavra->quantidade;
            frequencia->freq_rel = (frequencia->freq_abs / (float)totalPalavras) * 100;
            frequencia->freq_abs_acumulada = 0;
            frequencia->freq_rel_acumulada = 0;
            insereFrequenciaTamOrdenada(&frequencia, &freq_tamanho_palavra_h);
            /*FIM COD-002*/

            somatorioCertezaFrequencia = somatorioCertezaFrequencia + (palavra->quantidade * palavra->percentagem); /*COD-003*/
            ma_tam_palavra = ma_tam_palavra + (palavra->tamanho * palavra->quantidade);                             /*COD-004*/

            /*INI COD-005*/
            insereFreqPalavraOrdenada(palavra);
            /*FIM - COD-005*/

            palavra = palavra->proximo;
        }

        /*INI - COD-003*/
        media = (somatorioCertezaFrequencia / categoria->qtd_palavras);
        med_desv_cat->media_aritmetica = media;
        double variancia = 0;
        palavra = categoria->palavra;
        while (palavra != NULL)
        {
            variancia = variancia + pow(((palavra->percentagem - media) * palavra->quantidade), 2);
            palavra = palavra->proximo;
        }
        if (categoria->qtd_palavras - 1 > 0)
        {
            variancia = variancia / (categoria->qtd_palavras - 1);
            med_desv_cat->desvio_padrao = sqrt(variancia);
        }
        else
        {
            med_desv_cat->desvio_padrao = 0;
        }
        insereMedDesv(&med_desv_cat);
        /*FIM - COD-003*/

        categoria = categoria->proximo;
    }

    /*INI - COD-001
    Guardo anterior e seto freq. absoluta e relativa acumuladas do primeiro elemento para Frequencias de Categorias.
    */
    Frequencia *frequencia_ant = freq_categoria_h;
    frequencia_ant->freq_abs_acumulada = frequencia_ant->freq_abs;
    frequencia_ant->freq_rel_acumulada = frequencia_ant->freq_rel;
    /*Calculo demais frequencias acumuladas*/
    frequencia = freq_categoria_h->proximo;
    while (frequencia != NULL)
    {
        frequencia->freq_abs_acumulada = frequencia->freq_abs + frequencia_ant->freq_abs_acumulada;
        frequencia->freq_rel_acumulada = frequencia->freq_rel + frequencia_ant->freq_rel_acumulada;
        frequencia_ant = frequencia;
        frequencia = frequencia->proximo;
    }
    /*FIM COD-001*/

    /*INI - COD-002
    Guardo anterior e seto freq. absoluta e relativa acumuladas do primeiro elemento para Frequencias de Tamanho de Palavras.
    */
    frequencia_ant = freq_tamanho_palavra_h;
    frequencia_ant->freq_abs_acumulada = frequencia_ant->freq_abs;
    frequencia_ant->freq_rel_acumulada = frequencia_ant->freq_rel;
    /*FIM - COD-002*/

    /*INI - COD-004
     Medidas de localização e dispersão: tamanho das palavras
    */
    ma_tam_palavra = ma_tam_palavra / totalPalavras;

    //Moda
    int tamanho = atoi(frequencia_ant->variavel);
    int maiorFrequencia = frequencia_ant->freq_abs;
    moda_tam_palavra = tamanho;

    //Mediana
    int posicao_mediana;
    /*Total do Rol do Tamanho de palavras: verificar se é impar ou par para calcular a mediana*/
    if (totalPalavras % 2 != 0)
    {
        posicao_mediana = ((totalTamanhoPalavras + 1) / 2);
    }
    else
    {
        float soma1 = (totalTamanhoPalavras/2);
        float soma2 = ((totalPalavras + 1) / 2);
        posicao_mediana = ((soma1+soma2)/2);
    }

    //Variancia
    double variancia = pow(((tamanho - ma_tam_palavra) * maiorFrequencia), 2);
    /*FIM COD-004

    /*INI - COD-002
    Calculo demais frequencias acumuladas para Tamanho de Palavras
    */
    frequencia = freq_tamanho_palavra_h->proximo;
    int posicao = 0;

    while (frequencia != NULL)
    {
        /*INI COD-004*/
        tamanho = atoi(frequencia->variavel); //Variavel que contém o tamanho da palavra
        posicao++;
        if (posicao == posicao_mediana)
        {
            mediana_tam_palavra = tamanho; //Posição da mediana recebe variavel de tamanho
        }
        if (frequencia->freq_abs > maiorFrequencia)
        {
            maiorFrequencia = frequencia->freq_abs; //Elemento de maior frequencia absoluta será a moda
            moda_tam_palavra = tamanho;
        }
        variancia = variancia + pow(((tamanho - ma_tam_palavra) * frequencia->freq_abs), 2);
        /*Fim COD-004*/

        frequencia->freq_abs_acumulada = frequencia->freq_abs + frequencia_ant->freq_abs_acumulada;
        frequencia->freq_rel_acumulada = frequencia->freq_rel + frequencia_ant->freq_rel_acumulada;
        frequencia_ant = frequencia;
        frequencia = frequencia->proximo;
    }
    /*FIM - COD-002*/

    /*INI COD-004*/
    if (totalPalavras - 1 > 0)
    {
        //Variancia
        variancia = variancia / (totalPalavras - 1);
        //Desvio padrao
        desvio_padrao_tam_palavra = sqrt(variancia);
        /*FIM COD-004*/
    }
}

/*Mostra tabela de frequencias de categorias com relação a sua quantidade de palavras*/
void showFreqCategorias()
{
    if (freq_categoria_h != NULL)
    {
        Frequencia *frequencia = freq_categoria_h;
        printf("\nTabela de Frequencias na quantidade de palavras de uma categoria:\n");
        printf("%-10s%-10s%-10s%-10s%-10s\n", "X", "ni", "fi", "Ni", "Fi");
        while (frequencia != NULL)
        {
            printf("%-10s%-10d%-10.2f%-10.d%-10.2f\n", frequencia->variavel, frequencia->freq_abs,
                   frequencia->freq_rel, frequencia->freq_abs_acumulada, frequencia->freq_rel_acumulada);
            frequencia = frequencia->proximo;
        }
    }
    else
    {
        printf("\nLista de Frequências de Categoria vazia!");
    }
}

/*Mostra tabela de frequencias do tamanho das palavras*/
void showFreqTamPalavras()
{
    if (freq_tamanho_palavra_h != NULL)
    {
        Frequencia *frequencia = freq_tamanho_palavra_h;
        printf("\nTabela de Frequencias do tamanho das palavras:\n");
        printf("%-10s%-10s%-10s%-10s%-10s\n", "X", "ni", "fi", "Ni", "Fi");
        while (frequencia != NULL)
        {
            printf("%-10s%-10d%-10.2f%-10.d%-10.2f\n", frequencia->variavel, frequencia->freq_abs,
                   frequencia->freq_rel, frequencia->freq_abs_acumulada, frequencia->freq_rel_acumulada);
            frequencia = frequencia->proximo;
        }
    }
    else
    {
        printf("\nLista de Frequências de Tamanho de Palavras vazia!");
    }
}

/*Mostra resultado das medias e desvio padrão das categorias de palavras com base na medida de etiquetação*/
void showMedDesvCat()
{
    if (med_desv_h != NULL)
    {
        printf("\nTabela de Media e Desvio Padrao da categoria com base na etiquetacao:\n");
        MedDesvCat *elemento = med_desv_h;
        printf("%-20s%-20s%-20s\n", "Categoria", "Media Artimetica", "Desvio Padrao");
        while (elemento != NULL)
        {
            printf("%-20s%-20.5lf%-20.5lf\n", elemento->categoria, elemento->media_aritmetica, elemento->desvio_padrao);
            elemento = elemento->proximo;
        }
    }
    else
    {
        printf("\nLista de Medias e Desvios Padrões com base na etiquetação vazia!");
    }
}

/*Mostra Medidas de Localização e Dispersão relativas ao tamanho das palavras*/
void showLocDisp()
{
    printf("\nMedidas de localizacao e dispersao relativas ao tamanho das palavras:\n");
    printf("%-20s%-20s%-20s%-20s\n", "Media Aritmetica", "Moda", "Mediana", "Desvio Padrao");
    printf("%-20.5lf%-20d%-20.5lf%-20.5lf\n", ma_tam_palavra, moda_tam_palavra, mediana_tam_palavra, desvio_padrao_tam_palavra);
}

/*Mostra Frequencia das palavras*/
void showFreqPalavras(){
    FreqPalavras* frequencia = freq_palavras_h;
    printf("\nTabela de Frequencias das palavras:");
    printf("\n%-20s%-20s", "Palavra", "Frequencia");
    while(frequencia != NULL)
    {
        printf("\n%-20s%-20d", frequencia->palavra, frequencia->quantidade);
        frequencia = frequencia->proximo;
    }
}

void calculaQuartil(){
    float mediana = 0;
    int soma = somaFreqPalavras;
    //Quartil 2
    if(soma%2 != 0){
        mediana = ((soma + 1) / 2);
    }
    else
    {
        float soma1 = (soma + 1)/2;
        float soma2 = (soma / 2);
        mediana = ((soma1+soma2)/2);
    }
    quartil_2 = mediana;

    //Quartil 1
    soma = quartil_2 - 1;
    if(soma%2 != 0){
        mediana = ((soma + 1) / 2);
    }
    else
    {
        float soma1 = (soma + 1)/2;
        float soma2 = (soma / 2);
        mediana = ((soma1+soma2)/2);
    }
    quartil_1 = mediana;

    //Quartil 3
    soma = somaFreqPalavras + quartil_2 + 1;
    if(soma%2 != 0){
        mediana = ((soma + 1) / 2);
    }
    else
    {
        float soma1 = (soma + 1)/2;
        float soma2 = (soma / 2);
        mediana = ((soma1+soma2)/2);
    }
    quartil_3 = mediana;

    printf("\nQuartil 1: %.2f | Quartil 2: %.2f | Quartil 3: %.2f", quartil_1, quartil_2, quartil_3); 
}

int getQuartil(char texto[]){
    if(freq_palavras_h !=NULL){
        FreqPalavras* frequencia = freq_palavras_h;
        int posicao = 0;
        while(frequencia!=NULL){
            posicao++;
            int compare = strcmp(texto, frequencia->palavra);
            if(compare == 0){
                if(posicao <= quartil_1){
                    printf("\nPalavra %s esta no Quartil 1. Posicao %d no Rol.", texto, posicao);
                    return true;
                }
                else if(posicao > quartil_1 && posicao <= quartil_2)
                {
                    printf("\nPalavra %s esta no Quartil 2. Posicao %d no Rol.", texto, posicao);
                    return true;
                }
                else if((posicao > quartil_2) && (posicao <= quartil_3)){
                     printf("\nPalavra %s esta no Quartil 3. Posicao %d no Rol.", texto, posicao);
                     return true;
                }
                else{
                     printf("\nPalavra %s esta no Quartil 4. Posicao %d no Rol.", texto, posicao);
                     return true;
                }
            }
            frequencia = frequencia->proximo;
        }
        printf("\nPalavra nao esta presente no Rol.");
        return false;
    }
}