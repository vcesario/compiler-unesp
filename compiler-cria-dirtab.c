#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "compiler-separa-str.h"

#define _size 1000

//ASSEMBLY STRING
/*typedef struct{
    char rot[_size];
    char mne[_size];
    char op1[_size];
    char op2[_size];
}tipoAsm;*/

void pegaDirs();

int main(){
    /** PRIMEIRO, ESCANEAR O ARQUIVO .ASM PARA
    *   ARMAZENAR AS DIRETIVAS EM UM ARQUIVO .TXT **/
    printf("Digite o nome do arquivo em linguagem de montagem (com a extensao): ");
    char arq_nome[_size];
    gets(arq_nome);
    pegaDirs(arq_nome);

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
        printf("frase: %s\n",cmd_linha);


        astr = separaStr(cmd_linha);

        //strcpy(cmd_linha,"");

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
        getch();
    }

    fclose(tabela);
    fclose(arq);

    printf("Fim de execucao.");
    getch();
}
