#include <stdio.h>
#include <assert.h>
#include <string.h>

#define FILENAME_QUARTOS "quartos.txt"

typedef struct {
    int numero;
    int quantidadeHospedes;
    float valorDiaria;
    char status[50];
} Quarto;

void resetarStatusQuartos() {
    FILE *file = fopen(FILENAME_QUARTOS, "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo %s.\n", FILENAME_QUARTOS);
        return;
    }

    Quarto quartos[100];
    int numQuartos = 0;

    // Lê todos os quartos do arquivo
    while (fscanf(file, "%d %d %f %[^\n]", &quartos[numQuartos].numero, &quartos[numQuartos].quantidadeHospedes,
                                          &quartos[numQuartos].valorDiaria, quartos[numQuartos].status) == 4) {
        numQuartos++;
    }

    fclose(file);

    file = fopen(FILENAME_QUARTOS, "w");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo %s para escrita.\n", FILENAME_QUARTOS);
        return;
    }

    // Escreve os quartos de volta no arquivo, alterando apenas o status para "desocupado"
    for (int i = 0; i < numQuartos; i++) {
        fprintf(file, "%d\n%d\n%.2f\ndesocupado\n", quartos[i].numero, quartos[i].quantidadeHospedes,
                                                quartos[i].valorDiaria);
    }

    fclose(file);

    printf("Status de todos os quartos resetados para desocupado.\n");
}

void testarResetarStatusQuartos() {
    // Configuração inicial: Cria um arquivo de teste com alguns quartos
    FILE *file = fopen(FILENAME_QUARTOS, "w");
    assert(file != NULL);
    fprintf(file, "101\n2\n150.00\nocupado\n");
    fprintf(file, "102\n3\n200.00\nocupado\n");
    fclose(file);

    // Chama a função a ser testada
    resetarStatusQuartos();

    // Verifica o resultado
    file = fopen(FILENAME_QUARTOS, "r");
    assert(file != NULL);

    Quarto quarto;
    while (fscanf(file, "%d %d %f %[^\n]", &quarto.numero, &quarto.quantidadeHospedes,
                                          &quarto.valorDiaria, quarto.status) == 4) {
        assert(strcmp(quarto.status, "desocupado") == 0);
    }

    fclose(file);

    printf("Todos os testes passaram!\n");
}

int main() {
    testarResetarStatusQuartos();
    return 0;
}
