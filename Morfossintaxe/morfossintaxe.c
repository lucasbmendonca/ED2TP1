#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "morfossintaxe.h"

void iniciar(){
    categoria_header = NULL;
}

//comment

void destroi(){
    if(categoria_header != NULL){
        Categoria *elemento_aux;
        Categoria *l_aux = categoria_header;
        Palavra *p_aux, *palavra_aux;
        while(l_aux != NULL){
            elemento_aux = l_aux;
            p_aux = l_aux->palavra;
            l_aux = l_aux->proximo;
            free(elemento_aux);
            while(p_aux != NULL){
                palavra_aux = p_aux;
                p_aux = p_aux->proximo;
                free(palavra_aux);
            }
        }
    }
}

void mostraResultado(){
    if(categoria_header != NULL){
        Categoria *l_aux = categoria_header;
        Palavra *p_aux, *palavra_aux;
        printf("\n*************************RESULTADO*************************\n");
        while(l_aux != NULL){
            printf("----> Categoria: %s || Quantidade: %d\n", l_aux->categoria, l_aux->qtd_palavras);
            p_aux = l_aux->palavra;
            while(p_aux != NULL){
                printf("<.> Palavra: %s || Tamanho: %d || Quantidade: %d\n", p_aux->texto, p_aux->tamanho, p_aux->quantidade);
                p_aux = p_aux->proximo;
            }
            l_aux = l_aux->proximo;
        }
        printf("***********************************************************\n");
    }
}

Palavra* meioPalavra(Palavra *palavra_inicio, Palavra *palavra_fim){

       if (palavra_inicio == NULL){ return NULL; }
       if (palavra_inicio->proximo == palavra_fim){ return palavra_inicio; }

        /*Variaveis auxiliar*/
        Palavra* p_devagar =  palavra_inicio;
        Palavra* p_rapido  =  palavra_inicio->proximo;

        while (p_devagar != palavra_fim)
        {
            if (p_rapido == NULL){return p_devagar;}

            p_rapido = p_rapido->proximo;
            if (p_rapido != palavra_fim)
            {
                /*Ja chegou ao fim da lista*/
                if(p_rapido == NULL){
                    p_devagar = p_devagar->proximo;
                    continue;
                }
                p_rapido = p_rapido->proximo;
            }
        }
        return p_devagar;
}

Palavra* buscaBinariaPalavra(Palavra *p, char* texto){

    Palavra* palavra_inicio = p;
    Palavra* palavra_fim = NULL;
    Palavra* palavra_meio, *palavra_anterior;

    palavra_meio = meioPalavra(palavra_inicio,palavra_fim);
    /*Se nao encontra a palavra, retorna ela mesma*/
    if(palavra_meio == NULL){ return p; }

    for(;;){
        int compare = strcmp(texto,palavra_meio->texto);
        if(compare == 0)
        {
            return palavra_meio;
            break;
        }
        else if(compare < 0){ palavra_fim = palavra_meio; }
        else if(compare > 0){ palavra_inicio = palavra_meio->proximo; }

        palavra_anterior = palavra_meio;
        palavra_meio = meioPalavra(palavra_inicio,palavra_fim);

        if(palavra_meio == NULL || palavra_anterior == palavra_meio)
        {
            return palavra_anterior;
            break;
        }
    }
}

Categoria* meioCategoria(Categoria* comeco_el, Categoria* ultimo_el){

        if (comeco_el == NULL){ return NULL; }
        if (comeco_el->proximo == ultimo_el){ return comeco_el; }

        /*Variaveis auxiliar*/
        Categoria* p_devagar = comeco_el;
        Categoria* p_rapido = comeco_el->proximo;

        while (p_devagar != ultimo_el)
        {
            if (p_rapido == NULL){ return p_devagar;}

            p_rapido = p_rapido->proximo;
            if (p_rapido != ultimo_el)
            {
                /*Ja chegou ao fim da lista*/
                if(p_rapido == NULL){
                    p_devagar = p_devagar->proximo;
                    continue;
                }
                p_rapido = p_rapido->proximo;
            }
        }
        return p_devagar;
}

Categoria* buscaBinariaCategoria(Categoria *l, char* texto){
    /*Auxiliares*/
    Categoria* elemento_comeco = l;
    Categoria* elemento_ultimo = NULL;
    Categoria* elemento_meio, *elemento_anterior;

    elemento_meio = meioCategoria(elemento_comeco,elemento_ultimo);
    if(elemento_meio == NULL){ return l; }

    for(;;){
        int compare = strcmp(texto,elemento_meio->categoria);
        if(compare == 0)
        {
            /*Adiciona +1 a frequencia da classificacao*/
            elemento_meio->qtd_palavras++;
            return elemento_meio;
            break;
        }
        else if(compare < 0){ elemento_ultimo = elemento_meio; }
        else if(compare > 0){ elemento_comeco = elemento_meio->proximo; }

        elemento_anterior = elemento_meio;
        elemento_meio = meioCategoria(elemento_comeco,elemento_ultimo);
        if(elemento_meio == NULL || elemento_anterior == elemento_meio)
        {
            return elemento_anterior;
            break;
        }
    }
}

void insereCategoria(Categoria *p_new, Categoria *p_elemento){
    int compare = strcmp(p_new->categoria, p_elemento->categoria);
    if (compare < 0)
    {
        p_new->anterior = p_elemento->anterior;
        p_new->proximo = p_elemento;
        /*Inserir entre dois elementos*/
        if (p_elemento->anterior != NULL){
            p_elemento->anterior->proximo = p_new;
            p_elemento->anterior = p_new;
          }
        /*Inserindo no começo*/
        else{
               p_elemento->anterior = p_new;
               p_elemento = p_new;
               categoria_header = p_elemento;
        }
    }
    else if(compare > 0)
    {
        p_new->proximo = p_elemento->proximo;
        /*Inserir entre dois elementos*/
        if (p_elemento->proximo != NULL){
            p_new->anterior = p_elemento->proximo->anterior;
            p_elemento->proximo->anterior = p_new;
        }
        /*Inserindo no final*/
        else{ p_new->anterior = p_elemento; }
        p_elemento->proximo = p_new;
    }
}

void inserePalavra(Palavra *p_new, Palavra *p_palavra, Palavra **p_header){

    int result = strcmp(p_new->texto,p_palavra->texto);
    if (result < 0)
    {
        /*Adicionando +1 a frequencia*/
        p_new->quantidade++;

        p_new->anterior = p_palavra->anterior;
        p_new->proximo = p_palavra;
        /*Inserir entre dois elementos*/
        if (p_palavra->anterior != NULL){
            p_palavra->anterior->proximo = p_new;
            p_palavra->anterior = p_new;
          }
        /*Inserindo no come�o*/
        else
        {
            p_palavra->anterior = p_new;
            p_palavra = p_new;
            *p_header = p_new;
        }
    }
    else if(result > 0)
    {
        /*Adicionando +1 a frequencia*/
        p_new->quantidade++;

        p_new->proximo = p_palavra->proximo;
        /*Inserir entre dois elementos*/
        if (p_palavra->proximo != NULL){
            p_new->anterior = p_palavra->proximo->anterior;
            p_palavra->proximo->anterior = p_new;
        }
        /*Inserindo no final*/
        else{ p_new->anterior = p_palavra; }

        p_palavra->proximo = p_new;
    }
    else if (result == 0){ p_palavra->quantidade++; return; }

}

void insere(char* texto, char* raiz, char* categoria, double percentagem){
    Categoria *new_element = (Categoria *)malloc(sizeof(Categoria));
    strcpy(new_element->categoria, categoria);
    new_element->proximo = NULL;
    new_element->anterior = NULL;

    Palavra *new_palavra = (Palavra *)malloc(sizeof(Palavra));
    strcpy(new_palavra->texto, texto);
    strcpy(new_palavra->raiz, raiz);
    new_palavra->tamanho = strlen(texto);
    new_palavra->percentagem = percentagem;
    new_palavra->proximo = NULL;
    new_palavra->anterior = NULL;

    new_element->palavra = new_palavra;
    new_element->qtd_palavras = 1;

    if(categoria_header == NULL){
        new_element->palavra->quantidade = 1;
        categoria_header = new_element;
    }
    else
    {
        Categoria *categoria, *header_categoria;
        Palavra *palavra, *palavra_header_temp;
        categoria = buscaBinariaCategoria(categoria_header,new_element->categoria);
        if (categoria != NULL)
        {
            /* Se a categoria ja esta na lista, guardo inicio da lista de palavras*/
            if (strcmp(new_element->categoria,categoria->categoria) == 0){
                palavra_header_temp = categoria->palavra;
            }
            /*Se nao estiver, o inicio da lista de palavras esta sendo criado agora*/
            else{
                palavra_header_temp = new_element->palavra;
            }
            insereCategoria(new_element, categoria);
             /*Tratar palavra*/
            palavra = buscaBinariaPalavra(palavra_header_temp,new_element->palavra->texto);
            if (palavra != NULL){
                    inserePalavra(new_element->palavra, palavra, &categoria->palavra);
            }
        }
    }
}
