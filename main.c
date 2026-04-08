#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void binario(int valor, char binario[]) {
    for (int i = 4; i >= 0; i--) {
        binario[4 - i] = ((valor >> i) & 1) + '0';
    }
    binario[5] = '\0';
}
void binario_imediato(int valor, char binario[]) {
    for (int i = 11; i >= 0; i--) {
        binario[11 - i] = ((valor >> i) & 1) + '0';
    }
    binario[12] = '\0';
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
            if(linha[i]==',' || linha[i]=='x' || linha[i]=='(' || linha[i]==')') linha[i]=' ';
        }
        char comando [3];
        sscanf(linha, "%s", comando);
        if (strcmp(comando, "sub")==0){
            unsigned int rd;
            char rd_bin [6];
            unsigned int rs1;
            char rs1_bin[6];
            unsigned int rs2;
            char rs2_bin[6];
            sscanf(linha, "%*s  %d  %d  %d", &rd, &rs1, &rs2);
            binario(rd, rd_bin);
            binario(rs1, rs1_bin);
            binario(rs2, rs2_bin);
            // RISC-V SUB: funct7 | rs2 | rs1 | funct3 | rd | opcode
            if(escolha_de_saida==1){
                //saida de arquivo
                fprintf(saida, "0100000%s%s000%s0110011\n", rs2_bin, rs1_bin, rd_bin);
            }
            else{
                printf("0100000%s%s000%s0110011\n", rs2_bin, rs1_bin, rd_bin);
            }

        }
        else if(strcmp(comando, "ori")==0){
            unsigned int rd,rs1;
            signed int imm;
            char rd_bin[6];char rs1_bin[6];char imm_bin[13];
            sscanf(linha,"%*s %d %d %d",&rd,&rs1,&imm);
            binario(rd, rd_bin);
            binario(rs1, rs1_bin);
            binario_imediato(imm, imm_bin);
            // RISC-V ORI: imm[11:0] | rs1 | funct3 | rd | opcode
            if(escolha_de_saida==1){
                //saida de arquivo
                fprintf(saida, "%s%s110%s0010011\n", imm_bin, rs1_bin, rd_bin);
            }
            else{
                printf("%s%s110%s0010011\n", imm_bin, rs1_bin, rd_bin);
            }
        }
        else if(strcmp(comando, "beq")==0){
            unsigned int rs1,rs2;
            int rotulo_endereco;
            int offset;
            char rs1_bin[6];char rs2_bin[6];char offset_bin[13];
            sscanf(linha,"%*s %d %d",&rs1,&rs2);
            binario(rs1,rs1_bin);binario(rs2,rs2_bin);
            if(escolha_de_saida==1){
                //saida de arquivo
                fprintf(saida, "0000000%s%s000000001100011\n", rs2_bin, rs1_bin);//ue
            }
            else{
                printf("0000000%s%s000000001100011\n", rs2_bin, rs1_bin);
            }

        }
        else if(strcmp(comando, "lb")==0){
            unsigned int rd;
            char rd_bin[6];
            unsigned int rs1;
            char rs1_bin[6];
            signed int imm;
            char imm_bin[13];
            sscanf(linha, "%*s %d %d %d", &rd, &imm, &rs1);
            binario(rd, rd_bin);
            binario(rs1, rs1_bin);
            binario_imediato(imm, imm_bin);
            // RISC-V LB: imm[11:0] | rs1 | funct3 | rd | opcode
            if(escolha_de_saida==1){
                //saida de arquivo
                fprintf(saida, "%s%s000%s0000011\n", imm_bin, rs1_bin, rd_bin);
            }
            else{
                printf("%s%s000%s0000011\n", imm_bin, rs1_bin, rd_bin);
            }

        }
        else if(strcmp(comando, "sb")==0){ //meu
            unsigned int rs2;
            char rs2_bin[6];
            unsigned int rs1;
            char rs1_bin[6];
            signed int imm;
            char imm_bin[13];
            sscanf(linha, "%*s %d %d %d", &rs2, &imm, &rs1);
            binario(rs2, rs2_bin);
            binario(rs1, rs1_bin);
            binario_imediato(imm, imm_bin);
            char imm_5_11_bin [8];
            char imm_0_4_bin [6];
            for (int i = 0; i < 7; i++){
                imm_5_11_bin[i] = imm_bin[i];
            }
            imm_5_11_bin[7] = '\0';
            for (int i = 0; i < 5; i++){
                imm_0_4_bin[i] = imm_bin[i + 7]; 
            }
            imm_0_4_bin[5] = '\0';
            // RISC-V SB: imm[11:5] | rs2 | rs1 | funct3 | imm[4:0] | opcode
            if(escolha_de_saida==1){
                //saida de arquivo
                fprintf(saida, "%s%s%s000%s0100011", imm_5_11_bin, rs2_bin, rs1_bin, imm_0_4_bin);
            }
            else{
                printf("%s%s%s000%s0100011", imm_5_11_bin, rs2_bin, rs1_bin, imm_0_4_bin);
            }

        }
        else if(strcmp(comando, "and")==0){ //meu
            unsigned int rd;
            char rd_bin [6];
            unsigned int rs1;
            char rs1_bin[6];
            unsigned int rs2;
            char rs2_bin[6];
            sscanf(linha, "%*s  %d  %d  %d", &rd, &rs1, &rs2);
            binario(rd, rd_bin);
            binario(rs1, rs1_bin);
            binario(rs2, rs2_bin);
            // RISC-V AND: funct7 | rs2 | rs1 | funct3 | rd | opcode
            if(escolha_de_saida==1){
                //saida de arquivo
                fprintf(saida, "0000000%s%s111%s0110011\n", rs2_bin, rs1_bin, rd_bin);
            }
            else{
                printf("0000000%s%s111%s0110011\n", rs2_bin, rs1_bin, rd_bin);
            }

        }
        else if(strcmp(comando, "srl")==0){ //meu
                        unsigned int rd;
            char rd_bin [6];
            unsigned int rs1;
            char rs1_bin[6];
            unsigned int rs2;
            char rs2_bin[6];
            sscanf(linha, "%*s  %d  %d  %d", &rd, &rs1, &rs2);
            binario(rd, rd_bin);
            binario(rs1, rs1_bin);
            binario(rs2, rs2_bin);
            // RISC-V SRL: funct7 | rs2 | rs1 | funct3 | rd | opcode
            if(escolha_de_saida==1){
                //saida de arquivo
                fprintf(saida, "0000000%s%s101%s0110011\n", rs2_bin, rs1_bin, rd_bin);
            }
            else{
                printf("0000000%s%s101%s0110011\n", rs2_bin, rs1_bin, rd_bin);
            }
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