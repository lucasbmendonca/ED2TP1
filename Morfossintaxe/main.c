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
        //[a-zA-Z]
        //lv_result = fscanf(arq,"%s %s %s %lf\n",lv_texto,lv_raiz,lv_categoria,&lv_percentagem);
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
                   /*Ler a linha novamente.
                    Embora essa leitura seja ignorada, serve para ler a proxima linha da iteracao.
                    fscanf(arq,"%s %s %s %s\n");*/
                    break;    
            }
        }while(!isEndOfFile);
    }
    Categoria* lista = getResultado();
    calcularFrequencias(lista);
    destroi();
    fclose(arq);
    return 0;
}
