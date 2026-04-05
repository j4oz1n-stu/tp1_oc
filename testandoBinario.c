#include <stdio.h>
#include <stdlib.h>
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
int main(){
    int n = -2;
    char n_bin[6];
    binario(n,n_bin);
    printf("%s",n_bin);

}
