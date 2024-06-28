#include <assert.h>
#include <stdio.h>

// Declaração da função a ser testada
int calcularDiarias(char *dataEntrada, char *dataSaida);

// Função principal para executar os testes
int main() {
    // Teste 1: Mesma data
    assert(calcularDiarias("01/01/2024", "01/01/2024") == 0);

    // Teste 2: Diferentes dias no mesmo mês
    assert(calcularDiarias("01/01/2024", "10/01/2024") == 9);

    // Teste 3: Diferentes meses no mesmo ano
    assert(calcularDiarias("01/01/2024", "01/02/2024") == 30);

    // Teste 4: Diferentes anos
    assert(calcularDiarias("01/01/2023", "01/01/2024") == 365);

    // Teste 5: Diferentes dias, meses e anos
    assert(calcularDiarias("01/01/2023", "10/02/2024") == 404);

    printf("Todos os testes passaram com sucesso!\n");

    return 0;
}

// Definição da função a ser testada
int calcularDiarias(char *dataEntrada, char *dataSaida) {
    int diaEntrada, mesEntrada, anoEntrada;
    int diaSaida, mesSaida, anoSaida;

    sscanf(dataEntrada, "%d/%d/%d", &diaEntrada, &mesEntrada, &anoEntrada);
    sscanf(dataSaida, "%d/%d/%d", &diaSaida, &mesSaida, &anoSaida);

    int totalDias = 0;

    // Calcula o número de dias entre as datas
    if (anoSaida > anoEntrada) {
        totalDias += (anoSaida - anoEntrada) * 365;
    }
    if (mesSaida > mesEntrada) {
        totalDias += (mesSaida - mesEntrada) * 30;
    }
    totalDias += diaSaida - diaEntrada;

    return totalDias;
}
