#include <stdio.h>
#include <string.h>

int *creatFile(char nameFile_[200]){
    FILE *p;
    char *nameFile, *extesao;
    strcpy (nameFile,nameFile_);

    extesao = strchr(nameFile,'.');

    if (strcmp(extesao,".txt") == 0){
        p = fopen(nameFile,"w");
    }else if (strcmp(extesao,".bin") == 0){
        p = fopen(nameFile,"wb");
    }
    if (p == NULL){
        printf(">> Erro ao criar Arquivo");
        return 1;
    }

    fclose(p);
    return 0;
}


char *nameFile(char nameFile_[200]){
    char nameFile[10];
    strcpy(nameFile,"asda");
    printf("%s",*nameFile);
    return nameFile;
}


int TxtEscrever(FILE **p, char entry){
    FILE *tp;
    tp = fopen(p,"r");
    fprintf(p,entry);
    fclose(p);
}

int main(){
    //FILE *p;
    // char nameFile[100];
    // printf("%s",creatFile("Exemplo.txt"));
    // strcpy(nameFile,creatFile("Exemplo.txt"));
    // printf("\np: %p %s",nameFile,nameFile);
    // //TxtEscrever(p,"test");
    char name[10] = nameFile("Exemplo.txt");
    //strcpy(name,nameFile("Exemplo.txt"));
    printf("%s",name);

}