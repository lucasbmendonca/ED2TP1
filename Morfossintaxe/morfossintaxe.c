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

Categoria* getResultado(){
    if(categoria_header != NULL){
        Categoria *l_aux = categoria_header;
        Palavra *p_aux, *palavra_aux;
        printf("\n*************************RESULTADO*************************\n");
        while(l_aux != NULL){
            printf("----> Categoria: %s || Quantidade: %d\n", l_aux->texto, l_aux->qtd_palavras);
            p_aux = l_aux->palavra;
            while(p_aux != NULL){
                printf("<.> Palavra: %s || Tamanho: %d || Quantidade: %d\n", p_aux->texto, p_aux->tamanho, p_aux->quantidade);
                p_aux = p_aux->proximo;
            }
            l_aux = l_aux->proximo;
        }
        printf("***********************************************************\n");
    }
    return categoria_header;
}

bool checkInput(char value[]){
//Verificações ASCII    
    int lenght = strlen(value);
    int i = 0, result = 0;
    char c1 = value[0], c2;

    if(lenght > 1){
   /*Somente caracteres do alfabeto*/
        if(!( c1 >= 65 && c1 <= 90) || (c1 >= 97 && c1 <= 122)){
            do{ 
                c2 = value[i++];
                if((( c2 >= 65 && c2 <= 90) || (c2 >= 97 && c2 <= 122))){
                    return true;
                }else{
                    //printf("Não inserir: %s\n", value);
                    return false;
                }
            }while(c2 != '\000');
            /*Caracteres iguais [;;...'']
            Ex.: Palavra 1 = ;;;
                 Palavra 2 = --
            Não devem ser inseridos!
            Se o numero de caracteres iguais for igual ao tamanho da palavra, 
            a palavra possui todos os caracteres idênticos.*/
            if (!(result != lenght + 1)){ 
                    //printf("Não inserir: %s\n", value);
                return false;
            }
            return true;
        }else
        {
            return true;
        }
        
    }
    else{
        if(( c1 >= 65 && c1 <= 90) || (c1 >= 97 && c1 <= 122))
        {
            return true;
        }        
        //printf("Não inserir: %s\n", value);
        return false;
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
            totalPalavras++;
            return palavra_meio;
        }
        else if(compare < 0){ palavra_fim = palavra_meio; }
        else if(compare > 0){ palavra_inicio = palavra_meio->proximo; }

        palavra_anterior = palavra_meio;
        palavra_meio = meioPalavra(palavra_inicio,palavra_fim);

        if(palavra_meio == NULL || palavra_anterior == palavra_meio)
        {   
            totalPalavras++;
            return palavra_anterior;
        }
    }
}

Categoria* acharMeio(Categoria* comeco_el, Categoria* ultimo_el){

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

Categoria* buscaBinaria(Categoria *l, char* texto){
    /*Auxiliares*/
    Categoria* elemento_comeco = l;
    Categoria* elemento_ultimo = NULL;
    Categoria* elemento_meio, *elemento_anterior;

    elemento_meio = acharMeio(elemento_comeco,elemento_ultimo);
    if(elemento_meio == NULL){ return l; }

    for(;;){
        int compare = strcmp(texto,elemento_meio->texto);
        if(compare == 0)
        {
            /*Adiciona +1 a frequencia da classificacao*/
            elemento_meio->qtd_palavras++;
            return elemento_meio;
            //break;
        }
        else if(compare < 0){ elemento_ultimo = elemento_meio; }
        else if(compare > 0){ elemento_comeco = elemento_meio->proximo; }

        elemento_anterior = elemento_meio;
        elemento_meio = acharMeio(elemento_comeco,elemento_ultimo);
        if(elemento_meio == NULL || elemento_anterior == elemento_meio)
        {
            return elemento_anterior;
            //break
        }
    }
}

int insereCategoria(Categoria *p_new, Categoria *p_elemento){
    int compare = strcmp(p_new->texto, p_elemento->texto);
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
        return true;
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
        return true;
    }
    return false;
}

int inserePalavra(Palavra *p_new, Palavra *p_palavra, Palavra **p_header){

    int compare = strcmp(p_new->texto,p_palavra->texto);

    if (compare < 0)
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
        /*Inserindo no começo da lista de palavras*/
        else
        {
            p_palavra->anterior = p_new;
            p_palavra = p_new;
            *p_header = p_new;
        }
        return true;
    }
    else if(compare > 0)
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
        return true;
    }
    else if (compare == 0)
    {
        p_palavra->quantidade++; 
        return true; 
    }

    return false;
}

int insere(char* texto, char* raiz, char* categoria, double percentagem){
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

    if(categoria_header == NULL){
        new_element->palavra->quantidade = 1;
        categoria_header = new_element;
        return true;
    }
    else
    {
        Palavra *palavra, *palavra_header_temp;
        Categoria *categoria = buscaBinaria(categoria_header,new_element->texto);
        bool flag_categ_existe = false;
        if (categoria != NULL)
        {
            /* Se a categoria ja esta na lista, guardo inicio da lista de palavras*/
            if (strcmp(new_element->texto,categoria->texto) == 0){
                palavra_header_temp = categoria->palavra;
                flag_categ_existe = true; //Categoria ja esta presente na lista
            }
            /*Se nao estiver, o inicio da lista de palavras esta sendo criado agora*/
            else{
                palavra_header_temp = new_element->palavra;
            }
        
            //Se a categoria nao existe, insiro
            if(!flag_categ_existe){
                flag_categ_existe = insereCategoria(new_element, categoria);
                totalCategorias++;
            }

            /*Tratar palavra*/
            if(flag_categ_existe){ //Se a categoria foi inserida com sucesso ou já existia na lista
                palavra = buscaBinariaPalavra(palavra_header_temp,new_element->palavra->texto);
                if (palavra != NULL){
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

int insereFrequenciaOrdenada(Frequencia** frequencia){

    if (frequencia == NULL){
        return false;
    }

    if(frequencia_header == NULL){
        frequencia_header = *frequencia;
        return true;
    }

    Frequencia *elemento = NULL;
    Frequencia *elemento_anterior = NULL;
    elemento = frequencia_header;
    do{
        if(elemento->freq_abs < (*frequencia)->freq_abs){
             elemento_anterior = elemento;
             elemento = elemento->proximo;
        }
        else if((elemento->freq_abs > (*frequencia)->freq_abs) || (elemento->freq_abs == (*frequencia)->freq_abs)){
            if (elemento_anterior == NULL){
                (*frequencia)->proximo = frequencia_header;
                frequencia_header = (*frequencia);
                return true;
            }
            elemento_anterior->proximo = (*frequencia);
            (*frequencia)->proximo = elemento;
            return true;
        }
    }while(elemento != NULL);

    elemento_anterior->proximo = (*frequencia);
    return true;
}

int calcularFrequencias(Categoria* lista){

    Frequencia* frequencia;
    Categoria* categoria = lista;
    
    while(categoria != NULL){
        frequencia = (Frequencia *)malloc(sizeof(Frequencia));
        frequencia->proximo = NULL;
        strcpy(frequencia->variavel,categoria->texto);
        frequencia->freq_abs = categoria->qtd_palavras;
        frequencia->freq_rel = (frequencia->freq_abs/(float)totalPalavras)*100;
        frequencia->freq_abs_acumulada = 0;
        frequencia->freq_rel_acumulada = 0;
        insereFrequenciaOrdenada(&frequencia);
        categoria = categoria->proximo;
    }

    /*Guardo anterior e seto freq. absoluta e relativa acumuladas do primeiro elemento*/
    Frequencia *frequencia_ant = frequencia_header;
    frequencia_ant->freq_abs_acumulada = frequencia_ant->freq_abs;
    frequencia_ant->freq_rel_acumulada = frequencia_ant->freq_rel;
    
    /*Calculo demais frequencias acumuladas*/
    frequencia = frequencia_header->proximo;
    while(frequencia != NULL){
         frequencia->freq_abs_acumulada = frequencia->freq_abs + frequencia_ant->freq_abs_acumulada;
         frequencia->freq_rel_acumulada = frequencia->freq_rel + frequencia_ant->freq_rel_acumulada;
         frequencia_ant = frequencia;
         frequencia = frequencia->proximo;
    }
    
    frequencia = frequencia_header;
    printf("%-10s%-20s%-10s%-10s%-10%s\n", "X", "ni", "fi", 
    "Ni", "Fi");
    while(frequencia != NULL){
        printf("%-10s%-20d%-10.2f%-10.d%-10.2f\n",frequencia->variavel, frequencia->freq_abs, 
        frequencia->freq_rel, frequencia->freq_abs_acumulada, frequencia->freq_rel_acumulada);
         frequencia = frequencia->proximo;
    }

    while(frequencia_header!=NULL){
        frequencia_header =  frequencia->proximo;
        free(frequencia);
    }
}
