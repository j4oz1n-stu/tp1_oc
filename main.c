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

int main(){
    char nome_arquivo [60];
    printf("insira o nome do arquivo que sera aberto (lembre-se de colocar a extensão do arquivo)\n");
    printf("ex: meu_assembly.asm\n");
    scanf("%s", nome_arquivo);
    FILE * arquivo;
    char linha [70];
    arquivo = fopen(nome_arquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo.\n");
        return 1;
    }
    while(fgets(linha, 70, arquivo)!=NULL){
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

        }
    }
    fclose(arquivo);

    //abrir o arquivo e fazer um while que le linha por linha,
    // apos isso fzer um if que analisa duas strings, como por exemplo: "sub"=="sub", porem so ate o primeiro espaço da string
    //dentro do if printar algo do tipo: printf("000000%d%d000%d0010110", x5, x6, x9) se a escolha for printar no terminal
    //se a escolha for escrever num arquivo é so fazer a mesma coisa mas com fprintf

}