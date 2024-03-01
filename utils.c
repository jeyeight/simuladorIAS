#include <stdio.h>
#include <string.h>
#include <getopt.h>
#include "headers/utils.h"
#include "headers/types.h"

void zerarString(char string[], int tamanho){
    for(int i = 0; i < tamanho; i++){
        string[i] = '\0';
    }
}

void verificaArgumentos(int argc, char* argv[], FILE** fdEntrada, FILE** fdSaida){
    int opt;
    char *nomeArquivoEntrada = NULL;

    while ((opt = getopt(argc, argv, "p:i:")) != -1) {
        switch (opt) {
            case 'p':
                nomeArquivoEntrada = optarg;
                break;
            case 'i':
                strcpy((char*)BR.PC, optarg);
                break;
            default:
                fprintf(stderr, "Uso: %s -p nomedoarquivodeentrada.ias -i PC\n", argv[0]);
                exit(1);
        }
    }
    if (nomeArquivoEntrada == NULL) {
        fprintf(stderr, "É necessário fornecer os argumentos -p e -i\n");
        exit(1);
    }

    if (nomeArquivoEntrada[0] == '<' && nomeArquivoEntrada[strlen(nomeArquivoEntrada) - 1] == '>') {
        nomeArquivoEntrada++;
        nomeArquivoEntrada[strlen(nomeArquivoEntrada) - 1] = '\0';
    }

    *fdEntrada = fopen(nomeArquivoEntrada, "r");
    if (*fdEntrada == NULL) {
        perror("Erro ao abrir arquivo de entrada");
        exit(1);
    }

    *fdSaida = fopen("inoutfiles/saida.ias.m", "wb"); 
    if(*fdSaida == NULL) {
        perror("Erro ao abrir arquivo de saída");
        exit(1);
    }
}

void testarPesos(){
    printf("Testando os Pesos inseridos. \n");
    for(int i = 0; i< 22; i++){
        printf("Na operacao: %s ", nomesOperacoes[i]);
        printf("O peso atribuido foi: %i \n", Pesos[i]);
        // printf("O valor do enum é: %d\n", Operacoes);
        
    }
    
}

void verificaPesos(FILE * fdEntrada){
    char caracter[2];
    caracter[1] = '\0';
    char instrucao[10];
    char peso[10];
    int indice_instrucao = 0;
    int contador_teste = 0;
    caracter[0] = fgetc(fdEntrada);
    printf("%c\n", caracter[0]);
    if(caracter[0] == '/'){
        caracter[0] = fgetc(fdEntrada);
        //printf("%c\n", caracter[0]);
    
    }
    else{
        fseek(fdEntrada, -1, SEEK_CUR);
    }
    caracter[0] = 'm'; //teste
    zerarString(instrucao, 10);
    while(caracter[0] != '*'){
        while(caracter[0] != ' '){
            
            caracter[0] = fgetc(fdEntrada);
            if(caracter[0] != ' ' && caracter[0] != '\n'){
                strcat(instrucao, caracter);
                //printf("instrucao = %s\n", instrucao);

            }
                //printf("caracter = %c\n", caracter[0]);

        }

        

        caracter[0] = fgetc(fdEntrada);
        while (caracter[0] != '\n'){
            //printf("caracter = %c\n", caracter[0]);
            strcat(peso, caracter);
            caracter[0] = fgetc(fdEntrada);
            
            //printf("preso aqui");
        }

        //printf("%s aqui esta operacao, de tamanho %i \n", instrucao, strlen(instrucao));
        instrucao[strlen(instrucao) - 1] = '\0';
        //printf("%s aqui esta operacao \n", instrucao);
        //printf("%s aqui esta peso \n", peso);

        setar_peso(instrucao, atoi(peso));

        instrucao[0] = '\0';
        peso[0] = '\0';
        
        

        caracter[0] = fgetc(fdEntrada);
        //printf("%c - caracter ", caracter[0]);
        if(caracter[0] != '*'){
            fseek(fdEntrada, -1, SEEK_CUR);
        }

        //printf("%c - caracter no final do laço\n", caracter[0]);
        
    }
    caracter[0] = fgetc(fdEntrada); //ler novamente o *
    //printf("%c - caracter \n", caracter[0]);
    caracter[0] = fgetc(fdEntrada); //ler a /
    //printf("%c - caracter \n", caracter[0]);
    caracter[0] = fgetc(fdEntrada); //ler a \n sei la
    //printf("%c - caracter \n", caracter[0]); 
    
    
    
}


void setar_peso(char* operacao, int peso){
    //printf("\nminha operacao ao entrar na funcao e: %s\n", operacao);
    //printf("meu peso ao entrar na funcao e: %i\n", peso);
    for (int i = 0; i < 22; i++) {
        //printf("seila, entre operacao = %s e nomesOperacoes = %s\n", operacao, nomesOperacoes[i]);
        if (strcmp(operacao, nomesOperacoes[i]) == 0) {
            //printf("achei!");
            Pesos[i] = peso;
        }
    }
}

// bool isNegative(unsigned char* memoria, int number){
//     long long int linha = 0;

//     linha |= memoria[byte_atual];

//     if((linha >= 128) && (contadorNumeros < quantidade_dados)){
//             linha -= 128;
//             return = true;
//     }else{
//         return false;
//     }
// }