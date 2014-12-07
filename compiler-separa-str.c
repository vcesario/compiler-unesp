#include <stdio.h>
#include <string.h>
#define _size 100

//ASSEMBLY STRING
struct astr{
    char rot[_size];
    char mne[_size];
    char op1[_size];
    char op2[_size];
};

struct astr separaStr();

int main(){
    char _str[_size];
    struct astr _astr;
    do{
        printf("Comando: ");
        gets(_str);

        _astr = separaStr(_str);

        printf("\nROT: \t%s", _astr.rot);
        printf("\nMNE: \t%s", _astr.mne);
        printf("\nOP1: \t%s", _astr.op1);
        printf("\nOP2: \t%s", _astr.op2);

        printf("\n\n");
    }while(1);

    return 0;
}

struct astr separaStr(char str[_size]){
    int i,j;
    struct astr _astr;

    i = j = 0;

    if (str[i] != ' ' && i<strlen(str)){
        for(j=0;str[i] != ' ';j++,i++){
            _astr.rot[j] = str[i];
        }
        _astr.rot[j] = '\0';
    }
    else
        strcpy(_astr.rot, " ");
    i++;

    if (str[i] != ' ' && i<strlen(str)){
        for(j=0;str[i] != ' ';j++,i++){
            _astr.mne[j] = str[i];
        }
        _astr.mne[j] = '\0';
    }
    else
        strcpy(_astr.mne, " ");
    i++;

    if (str[i] != ' ' && i<strlen(str)){
        for(j=0;str[i] != ',' && str[i];j++,i++){
            _astr.op1[j] = str[i];
        }
        _astr.op1[j] = '\0';
    }
    else
        strcpy(_astr.op1, " ");
    i++;

    if (str[i] != ' ' && i<strlen(str)){
        for(j=0;str[i];j++,i++){
            _astr.op2[j] = str[i];
        }
        _astr.op2[j] = '\0';
    }
    else
        strcpy(_astr.op2, " ");

    return _astr;
}
