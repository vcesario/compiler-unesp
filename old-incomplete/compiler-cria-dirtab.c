#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "compiler-separa-str.h"

#define _size 1000

void pegaDirs();
void printDirs();

int main(){
    /** PRIMEIRO, ESCANEAR O ARQUIVO .ASM PARA
    *   ARMAZENAR AS DIRETIVAS EM UM ARQUIVO .TXT **/
    printf("Digite o nome do arquivo em linguagem de montagem (com a extensao): ");
    char arq_nome[_size];
    char input;
    gets(arq_nome);
    pegaDirs(arq_nome);
    printf("\nPressione\n\t[P] para exibir os rotulos e seus valores respectivos.\n\tQualquer outra tecla para encerrar.");
    input = getch();
    if (toupper(input) == 'P'){
        printDirs();
    }

}

void pegaDirs(char nome[]){
    FILE *arq, *tabela;
    char cmd_linha[_size];
    tipoAsm astr;
    int nlin = 0;

    if ((arq = fopen(nome, "r")) == NULL){
        printf("Erro na leitura de '%s'.", nome);
        exit(1);
    }
    tabela = fopen("tabela_rots.txt", "w");

    while (fgets(cmd_linha,_size,arq)){
        cmd_linha[strlen(cmd_linha)-1] = '\0'; //deletando o caracter de newline

        astr = separaStr(cmd_linha);

        if (strcmp(astr.rot,"")){
            if (!stricmp(astr.mne,"EQU")){
                fprintf(tabela, astr.rot);
                fprintf(tabela, " ");
                fprintf(tabela, astr.op1);
                fprintf(tabela, "\n");
            }
            else{
                fprintf(tabela, astr.rot);
                fprintf(tabela, " ");
                fprintf(tabela, "%d", nlin);
                fprintf(tabela, "\n");
            }
        }

        /** SE COMANDO FOR 'RET', ADICIONA UMA LINHA
        *   DO CONTRÁRIO, ADICIONA DUAS **/
        if (stricmp(astr.mne,"EQU")){
            if (!stricmp(astr.mne,"RET")){
                nlin += 1;
            }
            else{
                nlin += 2;
            }
        }
    }

    fclose(tabela);
    fclose(arq);

    printf("Fim de execucao.");
    getch();
}

void printDirs(){

    FILE *tabela;
    char cmd_linha[_size];

    if ((tabela = fopen("tabela_rots.txt", "r")) == NULL){
        printf("Erro na leitura de tabela_rots.txt");
        exit(1);
    }

    int i;

    while (fgets(cmd_linha,_size,tabela)){
        cmd_linha[strlen(cmd_linha)-1] = '\0'; //deletando o caracter de newline

        i=0;
        printf("\n\nROT: ");
        while(cmd_linha[i] != ' '){
            printf("%c",cmd_linha[i]);
            i++;
        }
        i++;
        printf("\nVAL: ");
        while(cmd_linha[i]){
            printf("%c",cmd_linha[i]);
            i++;
        }
    }
}
