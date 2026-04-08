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
void cleaner (char linha[]){
    for(int i = 1; linha[i]!='\0'; i++){
        if(linha[i]==',' || linha[i]=='x' || linha[i]=='(' || linha[i]==')') linha[i]=' ';
    }
}
void output_w(char comando[], int output_type, FILE* saida){
    if(output_type==1){
        //saida de arquivo
        fprintf(saida, "%s\n", comando);
    }
    else{
        printf("%s\n", comando);
    }
}
void assembler (char linha[], int output_type, FILE* saida){
    cleaner(linha);
    char comando [3];
    char output [33];
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
        snprintf(output, "0100000%s%s000%s0110011", rs2_bin, rs1_bin, rd_bin);
        output_w(output, output_type, saida);

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
        snprintf(output, "%s%s110%s0010011", imm_bin, rs1_bin, rd_bin);
        output_w(output, output_type, saida);
    }
    else if(strcmp(comando, "beq")==0){
        unsigned int rs1,rs2;
        int rotulo_endereco;
        int offset;
        char rs1_bin[6];char rs2_bin[6];char offset_bin[13];
        sscanf(linha,"%*s %d %d",&rs1,&rs2);
        binario(rs1,rs1_bin);
        binario(rs2,rs2_bin);
        snprintf(output, "0000000%s%s000000001100011", rs2_bin, rs1_bin);
        output_w(output, output_type, saida);

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
        snprintf(output, "%s%s000%s0000011", imm_bin, rs1_bin, rd_bin);
        output_w(output, output_type, saida);

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
        snprintf(output, "%s%s%s000%s0100011", imm_5_11_bin, rs2_bin, rs1_bin, imm_0_4_bin);
        output_w(output, output_type, saida);

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
        snprintf(output, "0000000%s%s111%s0110011", rs2_bin, rs1_bin, rd_bin);
        output_w(output, output_type, saida);

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
        snprintf(output, "0000000%s%s101%s0110011", rs2_bin, rs1_bin, rd_bin);
        output_w(output, output_type, saida);
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
    int output_type;
    printf("Escolha a forma que voce gostaria de receber a saida,\n");
    printf("Digite 1 para saida de arquivo ou 2 pra saida no terminal!\n");
    scanf("%d",&output_type);
    
    while(fgets(linha, 70, entrada)!=NULL){
        assembler(linha, output_type, saida);
    }
    fclose(entrada);
    fclose(saida);
    return 0;

}