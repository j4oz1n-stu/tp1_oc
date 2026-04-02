#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void binario(int valor, char binario[]){
    for(int i = 0; i < 5; i++) {
        binario[i] = '0';
    }
    binario[5] = '\0';
    int i=1;
    while(valor>0){
        binario[5-i] = valor%2 + '0';
        valor= valor/2;
        i++;
    }
}
void binario_imediato(int valor, char binario[]){
    for(int i =0;i<12;i++){
        binario[i] = '0';
    }
    binario[12] = '\0';
    int i=1;
    while(valor>0){
        binario[12-i] = valor%2 + '0';
        valor= valor/2;
        i++;
    }
}

int main(int argc, char *argv[]){
    if (argc < 3) {
        return 1;
    }
    FILE *entrada = fopen(argv[1], "r");
    FILE *saida = fopen(argv[2], "w");

    if (entrada == NULL || saida == NULL) {
        perror("Erro ao abrir os arquivos");
        return 1;
    }
    char linha [70];
    int escolha_de_saida;
    printf("Escolha a forma que voce gostaria de receber a saida,\n");
    printf("Digite 1 para saida de arquivo ou 2 pra saida no terminal!\n");
    scanf("%d",&escolha_de_saida);
    
    while(fgets(linha, 70, entrada)!=NULL){
        for(int i = 1; linha[i]!='\0'; i++){
            if(linha[i]==',' || linha[i]=='x') linha[i]=' ';
        }
        char comando [3];
        sscanf(linha, "%s", comando);
        if (strcmp(comando, "sub")==0){
            int rd;
            char rd_bin [6];
            int reg1;
            char reg1_bin[6];
            int reg2;
            char reg2_bin[6];
            sscanf(linha, "%*s  %d  %d  %d", &rd, &reg1, &reg2);
            binario(rd, rd_bin);
            binario(reg1, reg1_bin);
            binario(reg2, reg2_bin);
            // RISC-V SUB: funct7 | rs2 | rs1 | funct3 | rd | opcode
            printf("0100000%s%s000%s0110011", reg2_bin, reg1_bin, rd_bin);
            if(escolha_de_saida==1){
                //saida de arquivo
                fprintf(saida, "0100000%s%s000%s0110011", reg2_bin, reg1_bin, rd_bin);
            }
            else{
                printf("0100000%s%s000%s0110011", reg2_bin, reg1_bin, rd_bin);
            }

        }
        else if(strcmp(comando, "ori")==0){
            
        }
        else if(strcmp(comando, "beq")==0){
            
        }
        else if(strcmp(comando, "lb")==0){
            
        }
        else if(strcmp(comando, "sb")==0){
            
        }
        else if(strcmp(comando, "and")==0){
            
        }
        else if(strcmp(comando, "srl")==0){
            
        }
        

    }
    fclose(entrada);
    fclose(saida);
    return 0;

    //abrir o arquivo e fazer um while que le linha por linha,
    // apos isso fzer um if que analisa duas strings, como por exemplo: "sub"=="sub", porem so ate o primeiro espaço da string
    //dentro do if printar algo do tipo: printf("000000%d%d000%d0010110", x5, x6, x9) se a escolha for printar no terminal
    //se a escolha for escrever num arquivo é so fazer a mesma coisa mas com fprintf

}