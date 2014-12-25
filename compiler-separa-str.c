#include <stdio.h>
#include <string.h>
#define _size 100

//ASSEMBLY STRING
typedef struct{
    char rot[_size];
    char mne[_size];
    char op1[_size];
    char op2[_size];
}tipoAsm;

tipoAsm separaStr();

int main(){
    char str_input[_size];
    tipoAsm astr;
    do{
        /******************/
        printf("Comando: ");
        gets(str_input);
        /** trocar o método acima por uma captura de arquivo **/

        astr = separaStr(str_input);

        printf("\nROT: \t%s", astr.rot);
        printf("\nMNE: \t%s", astr.mne);
        printf("\nOP1: \t%s", astr.op1);
        printf("\nOP2: \t%s", astr.op2);

        printf("\n\n");
    }while(1); /**ARRUMAR CONDIÇÃO**/

    return 0;
}

tipoAsm separaStr(char str[_size]){
    int i,j;
    tipoAsm astr;

    i = j = 0;

    if (str[i] != ' ' && i<strlen(str)){
        for(j=0;str[i] != ' ';j++,i++){
            astr.rot[j] = str[i];
        }
        astr.rot[j] = '\0';
    }
    else
        strcpy(astr.rot, " ");
    i++;

    if (str[i] != ' ' && i<strlen(str)){
        for(j=0;str[i] != ' ';j++,i++){
            astr.mne[j] = str[i];
        }
        astr.mne[j] = '\0';
    }
    else
        strcpy(astr.mne, " ");
    i++;

    if (str[i] != ' ' && i<strlen(str)){
        for(j=0;str[i] != ',' && str[i] && str[i] != ';';j++,i++){
            astr.op1[j] = str[i];
        }
        astr.op1[j] = '\0';
    }
    else
        strcpy(astr.op1, " ");
    i++;

    if (str[i] != ' ' && i<strlen(str)){
        for(j=0;str[i] && str[i] != ';';j++,i++){
            astr.op2[j] = str[i];
        }
        astr.op2[j] = '\0';
    }
    else
        strcpy(astr.op2, " ");

    return astr;
}
