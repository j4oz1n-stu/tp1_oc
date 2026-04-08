# tp1_oc
# Montador RISC-V (Assembler)

Este projeto é um **Montador (Assembler)** desenvolvido em linguagem C. Ele traduz instruções da arquitetura **RISC-V** para linguagem de máquina em formato binário de 32 bits.

O programa processa um arquivo de entrada `.asm`, realiza o fatiamento de imediatos para diferentes tipos de instruções (R, I, S, B) e gera uma saída em binário, a qual o local de saída é por escolha do usuario.

---

## Instruções Suportadas

O montador suporta as seguintes instruções e formatos:

| Formato | Instrução | Descrição |
| :--- | :--- | :--- |
| **Tipo-R** | `sub` | Subtração de registradores |
| **Tipo-R** | `and` | Operação lógica AND |
| **Tipo-R** | `srl` | Deslocamento lógico à direita |
| **Tipo-I** | `ori` | OR imediato |
| **Tipo-I** | `lb` | Carregar byte da memória |
| **Tipo-S** | `sb` | Salvar byte na memória |
| **Tipo-B** | `beq` | Desvio se igual |

---

## Estrutura do Projeto

* `main.c`: Código-fonte principal com a lógica de tradução.
* `Makefile`: Automação de compilação e execução.
* `assembly.asm`: Arquivo de entrada com as instruções assembly.
* `saida.txt`: Arquivo gerado com o código de máquina resultante.

---

## Estrutura e Modularização do Código

O projeto foi desenvolvido seguindo princípios de modularização para garantir clareza e facilidade de manutenção. As principais responsabilidades foram divididas nas seguintes funções:

* **`cleaner` (Tratamento de Dados):** Atua no pré-processamento da linha lida do arquivo `.asm`. Sua função é limpar a string, removendo caracteres como `x`, `,`, `(` e `)`, padronizando a entrada para que os dados sejam extraídos corretamente.
* **`binario` (Conversão de Registradores):** Converte os índices dos registradores para o formato binário de **5 bits**.
* **`binario_imediato` (Conversão de Constantes):** Converte valores imediatos para o formato binário de **12 bits**, essencial para instruções Tipo-I, S e B.
* **`labels_finder` (Resolução de Endereços):** Função dedicada a percorrer o arquivo para identificar e mapear os *labels* (etiquetas). Essencial para o cálculo de saltos na instrução `beq`, permitindo o uso de desvios condicionais no código assembly.
* **`assembler` (Análise e Tradução):** O núcleo do programa. Esta função identifica qual instrução está sendo lida, aplica a lógica de montagem específica para cada tipo (R, I, S, B), realiza o fatiamento de imediatos e organiza os campos de bits.
* **`output_w` (Persistência e Saída):** Responsável por abstrair a escrita dos resultados. Dependendo da escolha do usuário, esta função encaminha a instrução traduzida para o terminal ou para o arquivo de destino.

---

## Como Executar

### Utilizando o Makefile 

1.  **Apenas compilar o programa:**
    ```bash
    make
    ```

2.  **Compilar e rodar o montador:**
    ```bash
    make run
    ```
    Nota: O programa solicitará no terminal se você deseja a saída no arquivo (1) ou no próprio terminal (2).

3.  **Limpar arquivos temporários:**
    ```bash
    make clean
    ```

### Compilação Manual

1.  Caso não possua o `make` instalado:
```bash
gcc main.c -o montador
./montador assembly.asm saida.txt
