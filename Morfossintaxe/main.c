#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "morfossintaxe.h"
#include "morfossintaxe.c"
#define C_FILENAME "slate-tagged2.txt"

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
    arq = fopen(C_FILENAME,"r");
    if(arq==NULL){
        printf("Nao foi possivel abrir o arquivo!\n");
    }
    else{
        //[a-zA-Z]
        lv_result = fscanf(arq,"%s %s %s %lf\n",lv_texto,lv_raiz,lv_categoria,&lv_percentagem);
        do{
            switch(lv_result){
                case EOF:
                    isEndOfFile = true;
                    break;
                case 0:
                    /*Ler a linha novamente, já que um caracter especial foi encontrado.
                    Embora essa leitura seja ignorada, serve para ler a proxima linha da iteracao.*/
                    fscanf(arq,"%s %s %s %s\n");
                    break;
                default:
                    printf("Inserindo... Palavra: %s | Raiz: %s | Categoria: %s | Percentagem: %lf\n",lv_texto,lv_raiz,lv_categoria,lv_percentagem);
                    insere(lv_texto,lv_raiz,lv_categoria,lv_percentagem);
                    break;
            }
            lv_result = fscanf(arq,"%s %s %s %lf\n",lv_texto,lv_raiz,lv_categoria,&lv_percentagem);
        }while(!isEndOfFile);
    }
    mostraResultado();
    destroi();
    fclose(arq);
    printf("ola");
    return 0;
}
