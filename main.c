#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

int main(){
    FILE* fd = fopen("entrada.txt", "r");
    char inputLinha[100]; 
    int countLinha = 0;
    char* m = (char*) malloc(4965 * 5 * sizeof(char));

    if (fd == NULL) {
        perror("Erro ao abrir o arquivo");
        exit(EXIT_FAILURE);
    }
    
    free(m);
    fclose(fd);

    return 0;
}