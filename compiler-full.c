#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define _size 1000

//ASSEMBLY STRING
typedef struct{
    char rot[_size];
    char mne[_size];
    char op1[_size];
    char op2[_size];
}tipoAsm;

void escreveTabela();
void escreveMaquina();
tipoAsm separaStr();
int contemStr();
int procura();

int main(int argc, char *argv[]){
    if (argc != 2) {
        printf("\n\tSintaxe: montar <nome_do_arquivo.extensao>\n");
        exit(0);
    }

    escreveTabela(argv[1]);
    escreveMaquina(argv[1]);
    /*
    if (!strcmp(argv[0],"monta")){
    }*/
    return 0;
}


void escreveTabela(char* nome){
    FILE *arq, *tabela;
    char cmd_linha[_size];
    tipoAsm astr;
    int nlin = 0;

    if ((arq = fopen(nome, "r")) == NULL){
        printf("\n\tErro na leitura de '%s'.", nome);
        exit(1);
    }
    tabela = fopen("tabela.txt", "w");

    while (fgets(cmd_linha,_size,arq)){
        if (cmd_linha[strlen(cmd_linha)-1] == '\n'){ //deletando o caractere de newline
            cmd_linha[strlen(cmd_linha)-1] = '\0';
        }

        astr = separaStr(cmd_linha);

        if (strcmp(astr.rot,"")){ //se o valor da comparação difere de 0, ou seja, se string DIFERE de <vazio>
            if (!stricmp(astr.mne,"EQU")){ //se o mnemonico é EQU
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

        if (stricmp(astr.mne,"EQU")){ //se o mnemonico NÃO for EQU
            if (!stricmp(astr.mne,"RET")){ //se o comando for RET
                nlin += 1;
            }
            else{
                nlin += 2;
            }
        }
    }

    fclose(tabela);
    fclose(arq);
}

void escreveMaquina(char* nomeAsm){
    FILE *arqOpc, *arqAsm, *arqTab;
    tipoAsm astr;
    char cmd_linha[_size], _op[_size], cmd_maq[_size], nomeOpc[_size];
    int i, comOp, ehRotulo, nlin = 0;

    //ABERTURA DOS ARQUIVOS
    if ((arqAsm = fopen(nomeAsm, "r")) == NULL){
        printf("\n\tErro na leitura de '%s'.", nomeAsm);
        exit(1);
    }

    if ((arqTab = fopen("tabela.txt", "r")) == NULL){
        printf("\n\tErro na leitura de 'tabela.txt'.", nomeAsm);
        exit(1);
    }

    //CRIANDO NOME.OPC
    strcpy(nomeOpc,nomeAsm);
    for (i=0;nomeOpc[i] != '.';i++);
    nomeOpc[i+1] = 'o';
    nomeOpc[i+2] = 'p';
    nomeOpc[i+3] = 'c';
    nomeOpc[i+4] = '\0';
    arqOpc = fopen(nomeOpc,"w");
    /*---------------------------------------------------*/

iterar:
    while (fgets(cmd_linha,_size,arqAsm)){

        comOp = 1;

        if (cmd_linha[strlen(cmd_linha)-1] == '\n'){ //deletando o caractere de newline
            cmd_linha[strlen(cmd_linha)-1] = '\0';
        }

        /*printf("\n\t%s..",cmd_linha);
        getch();*/

        astr = separaStr(cmd_linha);

        if (!stricmp(astr.mne,"MOV")){
            if (!stricmp(astr.op1,"AL")){
                if (astr.op2[0] == '['){

                    for (i=1;astr.op2[i] != ']';i++){
                        _op[i-1] = astr.op2[i];
                    }
                    _op[i-1] = '\0';

                    strcpy(cmd_maq,"a0h");
                }
                else{
                    strcpy(_op,astr.op2);
                    strcpy(cmd_maq,"b0h");
                }
            }
            else if (!stricmp(astr.op2,"AL")){

                for (i=1;astr.op1[i] != ']';i++){
                    _op[i-1] = astr.op1[i];
                }
                _op[i-1] = '\0';

                strcpy(cmd_maq,"a2h");
            }
            else{
                printf("\n\tErro: Linha <%d>, comando <%s> nao pode ser interpretado.", nlin, cmd_linha);
                strcpy(cmd_maq,"<?>");
                strcpy(_op,"<?>");
                getch();
                goto contar;
            }
        }
        else if (!stricmp(astr.mne,"ADD")){
            if (astr.op2[0] == '['){

                for (i=1;astr.op2[i] != ']';i++){
                    _op[i-1] = astr.op2[i];
                }
                _op[i-1] = '\0';

                strcpy(cmd_maq,"02h");
            }
            else{
                strcpy(_op,astr.op2);
                strcpy(cmd_maq,"04h");
            }
        }
        else if (!stricmp(astr.mne,"SUB")){
            if (astr.op2[0] == '['){

                for (i=1;astr.op2[i] != ']';i++){
                    _op[i-1] = astr.op2[i];
                }
                _op[i-1] = '\0';

                strcpy(cmd_maq,"2ah");
            }
            else{
                strcpy(_op,astr.op2);
                strcpy(cmd_maq,"2ch");
            }
        }
        else if (!stricmp(astr.mne,"CMP")){
            if (astr.op2[0] == '['){

                for (i=1;astr.op2[i] != ']';i++){
                    _op[i-1] = astr.op2[i];
                }
                _op[i-1] = '\0';

                strcpy(cmd_maq,"3ah");
            }
            else{
                strcpy(_op,astr.op2);
                strcpy(cmd_maq,"3ch");
            }
        }
        else if (!stricmp(astr.mne,"JMP")){
            strcpy(_op,astr.op1);
            strcpy(cmd_maq,"ebh");
        }
        else if (!stricmp(astr.mne,"JC")){
            strcpy(_op,astr.op1);
            strcpy(cmd_maq,"72h");
        }
        else if (!stricmp(astr.mne,"JNC")){
            strcpy(_op,astr.op1);
            strcpy(cmd_maq,"73h");
        }
        else if (!stricmp(astr.mne,"JZ")){
            strcpy(_op,astr.op1);
            strcpy(cmd_maq,"74h");
        }
        else if (!stricmp(astr.mne,"JNZ")){
            strcpy(_op,astr.op1);
            strcpy(cmd_maq,"75h");
        }
        else if (!stricmp(astr.mne,"JBE")){
            strcpy(_op,astr.op1);
            strcpy(cmd_maq,"76h");
        }
        else if (!stricmp(astr.mne,"JA")){
            strcpy(_op,astr.op1);
            strcpy(cmd_maq,"77h");
        }
        else if (!stricmp(astr.mne,"CALL")){
            strcpy(_op,astr.op1);
            strcpy(cmd_maq,"e8h");
        }
        else if (!stricmp(astr.mne,"RET")){
            comOp = 0;
            strcpy(cmd_maq,"c3h");
        }
        else if (!stricmp(astr.mne,"HLT")){
            comOp = 0;
            strcpy(cmd_maq,"f4h");
        }
        else if (stricmp(astr.mne,"EQU") && stricmp(astr.mne,"")){
            printf("\n\tErro: Linha <%d>, comando <%s> nao pode ser interpretado.", nlin, astr.mne);
            strcpy(cmd_maq,"<?>");
            getch();
            goto contar;
        }

        if ((stricmp(astr.rot,"")) && (!stricmp(astr.mne,""))){ //SE A LINHA CONTEM APENAS UM ROTULO, ITERAR
            goto iterar;
        }
        if (!stricmp(astr.mne,"EQU")){ //SE A LINHA FOR DIRETIVA (EQU), ITERAR
            goto iterar;
        }

        //SE NÃO FOR NUMERO E NEM ESTIVER NA TABELA DE DIRETIVAS, TERMINA
        if (comOp){
            ehRotulo = 1;
            for (i = 0;i<strlen(_op) && ehRotulo;i++){
                if (!isdigit(_op[i])){
                    ehRotulo = 0;
                }
            }
            if (!ehRotulo){
                if (procura(arqTab, 1000,_op) == 0){
                    printf("\n\tErro: Linha <%d>, termo <%s> nao pode ser interpretado.", nlin, _op);
                    strcpy(_op,"<?>");
                    getch();
                    goto contar;
                }
            }
        }

contar:
        fprintf(arqOpc,"%s\n",cmd_maq);
        nlin++;

        if (comOp){
            fprintf(arqOpc,"%s\n",_op);
            nlin++;
        }
    }

    fclose(arqAsm);
    fclose(arqOpc);
    fclose(arqTab);

    remove("tabela.txt");
}

tipoAsm separaStr(char str[_size]){
    int i,j;
    tipoAsm astr;

    i = j = 0;

    if (str[i] != ' ' && i<strlen(str)){
        for(j=0;str[i] != ' ' && str[i] != ';';j++,i++){
            astr.rot[j] = str[i];
        }
        astr.rot[j] = '\0';
    }
    else
        strcpy(astr.rot, "");

    i++;

    if (str[i] != ' ' && i<strlen(str)){
        for(j=0;str[i] != ' ' && str[i] != ';';j++,i++){
            astr.mne[j] = str[i];
        }
        astr.mne[j] = '\0';
    }
    else
        strcpy(astr.mne, "");

    i++;

    if (str[i] != ' ' && i<strlen(str)){
        for(j=0;str[i] != ',' && str[i] != ';' && str[i] != ' ' && str[i];j++,i++){
            astr.op1[j] = str[i];
        }
        astr.op1[j] = '\0';
    }
    else
        strcpy(astr.op1, "");

    i++;

    if (i<strlen(str)){
        for(j=0;str[i] && str[i] != ';' && str[i] != ' ';j++,i++){
            astr.op2[j] = str[i];
        }
        astr.op2[j] = '\0';
    }
    else
        strcpy(astr.op2, "");

    return astr;
}

int contemStr(char str1[_size], char str2[_size]){
    int i,j;
    int igual = 0;

    for (i=0;i<strlen(str1) && !igual;i++){
        if (str1[i] == str2[0]){
            igual = 1;
            for (j=1;(j<strlen(str2) && (j+i)<strlen(str1)) && igual;j++){
                if (str1[i+j] != str2[j]){
                    igual = 0;
                }
            }
        }
    }

    return igual;
}

int procura(FILE* tab, int strsz, char str[strsz]){
    char cmd_linha[_size], diretiva[_size], valor[_size];
    int i,j;

    rewind(tab);

        /*printf("\n\tvalor: %s",str);
        getch();*/
    while(fgets(cmd_linha,_size,tab)){
        cmd_linha[strlen(cmd_linha)-1] = '\0'; //deletando o caractere de newline

        /*printf("\n\tlinha_tab: %s",cmd_linha);
        getch();*/
        i=j=0;
        while (cmd_linha[i] != ' '){
            diretiva[i] = cmd_linha[i];
            i++;
        }
        diretiva[i] = '\0';
        i++;
        while (cmd_linha[i] != '\n' && cmd_linha[i] != '\0'){
            valor[j] = cmd_linha[i];
            i++;
            j++;
        }
        valor[j] = '\0';


        if (!stricmp(diretiva,str)){
            strcpy(str,valor);
            return 1;
        }
    }

    return 0;
}

