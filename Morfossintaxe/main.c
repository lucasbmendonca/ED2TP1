#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "morfossintaxe.h"
#include "morfossintaxe.c"

int main()
{
    iniciar();
    /*Local variables*/
    char lv_texto[100], lv_raiz[100], lv_categoria[10];
    double lv_percentagem;
    int lv_result;

    /*Flags*/
    bool isEndOfFile = false;

    /*Tratamento do arquivo*/
    FILE* arq;
    arq = fopen("Morfossintaxe/slate-tagged3.txt","r");
    if(arq==NULL){
        printf("Nao foi possivel abrir o arquivo!\n");
    }
    else{
        do{
            lv_result = fscanf(arq,"%s %s %s %lf\n",lv_texto,lv_raiz,lv_categoria,&lv_percentagem);
            switch(lv_result){
                case EOF:
                    isEndOfFile = true;
                    break;
                case 4:
                    printf("Inserindo... Palavra: %s | Raiz: %s | Categoria: %s | Percentagem: %lf\n",lv_texto,lv_raiz,lv_categoria,lv_percentagem);
                    if (checkInput(lv_texto)){
                        if(insere(lv_texto,lv_raiz,lv_categoria,lv_percentagem)){
                            printf("SUCCESS: Palavra %s inserida com sucesso!\n",lv_texto);
                        }
                        else
                        { 
                            printf("ERROR: Ocorreu um erro desconhecido ao inserir %s.\n", lv_texto);
                        }
                    }else{
                        printf("ERROR: Palavra %s nao foi inserida. Caracter invalido.\n", lv_texto);
                    }
                    break;
                default:
                    break;    
            }
        }while(!isEndOfFile);
    }
    /*Lista principal do programa com categorias e suas palavras ordenadas*/
    Categoria* categoriaPalavras_list = getResultado();

    /*Calculo de Frequencias e Medias relativas as questões do trabalho*/
    calcFreqMed(categoriaPalavras_list);

    /*Questao 2 - Mostrar tabela de frequencias com relação a classe gramatical utilizada*/
    showFreqCategorias(); 

    /*Questao 3 - Mostrar tabela de frequencias com relação ao tamanho das palavras*/
    showFreqTamPalavras();

    /*Questao 4 - Mostrar resultado das medias e desvio padrão com base na medida de etiquetação*/
    showMedDesvCat();

    /*Questao 5 - Mostrar resultado das medidas de dispersão e localização relativas ao tamanho das palavras*/
    showLocDisp();

    /*Questao 6 - Frequencia das palavras - Quartis*/
    showFreqPalavras();
    calculaQuartil();
    char texto[100];
    printf("\nDigite uma palavra para busca de quartil:");
    scanf("%s",texto);
    getQuartil(texto);

    /*Questao 7 - Histograma de probabilidades de acordo com a certeza de etiquetação*/
    calcHistograma();
    showHistograma();

    /*Destroi todas as listas geradas pelo programa*/
    destroi();

    /*Fecho o arquivo*/
    fclose(arq);
    return 0;
}
