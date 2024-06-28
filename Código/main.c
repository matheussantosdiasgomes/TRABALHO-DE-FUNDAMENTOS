#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR 100
#define FILENAME_CLIENTES "clientes.txt"
#define FILENAME_FUNCIONARIOS "funcionarios.txt"
#define FILENAME_QUARTOS "quartos.txt"
#define FILENAME_ESTADIAS "estadias.txt"

typedef struct {
    int codigo;
    char nome[MAX_STR];
    char endereco[MAX_STR];
    char telefone[MAX_STR];
} Cliente;

typedef struct {
    int codigo;
    char nome[MAX_STR];
    char telefone[MAX_STR];
    char cargo[MAX_STR];
    float salario;
} Funcionario;

typedef struct {
    int numero;
    int quantidadeHospedes;
    float valorDiaria;
    char status[MAX_STR]; // "ocupado" ou "desocupado"
} Quarto;

typedef struct {
    int codigo;
    int codigoCliente;
    int numeroQuarto;
    char dataEntrada[MAX_STR]; // Formato dd/mm/yyyy
    char dataSaida[MAX_STR];   // Formato dd/mm/yyyy
    int quantidadeDiarias;
    int quantidadeHospedes;
} Estadia;

void cadastrarCliente();
void cadastrarFuncionario();
void cadastrarQuarto();
void cadastrarEstadia();
void baixarEstadia();
void pesquisarCliente();
void pesquisarFuncionario();
void mostrarEstadiasCliente();
int gerarCodigo(char *filename);
int calcularDiarias(char *dataEntrada, char *dataSaida);
void lerClientes(Cliente clientes[], int *numClientes);
void salvarCliente(Cliente cliente);
void lerFuncionarios(Funcionario funcionarios[], int *numFuncionarios);
void salvarFuncionario(Funcionario funcionario);
void lerQuartos(Quarto quartos[], int *numQuartos);
void salvarQuarto(Quarto quarto);
void lerEstadias(Estadia estadias[], int *numEstadias);
void salvarEstadia(Estadia estadia);
void resetarStatusQuartos();
void salvarEstadias(Estadia estadias[], int numEstadias);

int main() {
    int opcao;

    do {
        printf("\n--- Hotel Descanso Garantido ---\n");
        printf("1. Cadastrar Cliente\n");
        printf("2. Cadastrar Funcionario\n");
        printf("3. Cadastrar Quarto\n");
        printf("4. Cadastrar Estadia\n");
        printf("5. Baixar Estadia\n");
        printf("6. Pesquisar Cliente\n");
        printf("7. Pesquisar Funcionario\n");
        printf("8. Mostrar Estadias de um Cliente\n");
        printf("0. Sair\n");
        //printf("10. resetar status dos quartos\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        printf("\n");

        switch (opcao) {
            case 1:
                printf("Cadastrar Cliente\n");
                cadastrarCliente();
                break;
            case 2:
                printf("Cadastrar Funcionario\n");
                cadastrarFuncionario();
                break;
            case 3:
                printf("Cadastrar Quarto\n");
                cadastrarQuarto();
                break;
            case 4:
                printf("Cadastrar Estadia\n");
                cadastrarEstadia();
                break;
            case 5:
                printf("Baixar Estadia\n");
                baixarEstadia();
                break;
            case 6:
                printf("Pesquisar Cliente\n");
                pesquisarCliente();
                break;
            case 7:
                printf("Pesquisar Funcionario\n");
                pesquisarFuncionario();
                break;
            case 8:
                printf("Mostrar Estadias de um Cliente\n");
                mostrarEstadiasCliente();
                break;
            case 0:
                printf("Saindo\n");
                break;
            case 10:
                printf("Resetar status dos quartos\n");
                resetarStatusQuartos();
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 0);

    return 0;
}

void cadastrarCliente() {
    Cliente cliente;
    cliente.codigo = gerarCodigo(FILENAME_CLIENTES);
    printf("Nome: ");
    scanf(" %[^\n]s", cliente.nome);
    printf("Endereco: ");
    scanf(" %[^\n]s", cliente.endereco);
    printf("Telefone: ");
    scanf(" %[^\n]s", cliente.telefone);
    salvarCliente(cliente);
    printf("Cliente cadastrado com sucesso\n");
}

void cadastrarFuncionario() {
    Funcionario funcionario;
    funcionario.codigo = gerarCodigo(FILENAME_FUNCIONARIOS);
    printf("Nome: ");
    scanf(" %[^\n]s", funcionario.nome);
    printf("Telefone: ");
    scanf(" %[^\n]s", funcionario.telefone);
    printf("Cargo: ");
    scanf(" %[^\n]s", funcionario.cargo);
    printf("Salario: ");
    scanf("%f", &funcionario.salario);
    salvarFuncionario(funcionario);
    printf("Funcionario cadastrado com sucesso\n");
}

void cadastrarQuarto() {
    Quarto quarto;
    printf("Numero do quarto: ");
    scanf("%d", &quarto.numero);
    printf("Quantidade de hospedes: ");
    scanf("%d", &quarto.quantidadeHospedes);
    printf("Valor da diaria: ");
    scanf("%f", &quarto.valorDiaria);
    strcpy(quarto.status, "desocupado");
    salvarQuarto(quarto);
    printf("Quarto cadastrado com sucesso\n");
}

void pesquisarCliente() {
    Cliente clientes[100];
    int numClientes = 0;
    int codigo;
    char nome[MAX_STR];

    lerClientes(clientes, &numClientes);

    printf("Digite o codigo ou nome do cliente: ");
    scanf(" %[^\n]s", nome);
    codigo = atoi(nome);

    for (int i = 0; i < numClientes; i++) {
        if (clientes[i].codigo == codigo || strcasecmp(clientes[i].nome, nome) == 0) {
            printf("Codigo: %d\nNome: %s\nEndereco: %s\nTelefone: %s\n", clientes[i].codigo, clientes[i].nome, clientes[i].endereco, clientes[i].telefone);
            return;
        }
    }
    printf("Cliente nao encontrado.\n");
}

void pesquisarFuncionario() {
    Funcionario funcionarios[100];
    int numFuncionarios = 0;
    int codigo;
    char nome[MAX_STR];

    lerFuncionarios(funcionarios, &numFuncionarios);

    printf("Digite o codigo ou nome do funcionario: ");
    scanf(" %[^\n]s", nome);
    codigo = atoi(nome);

    for (int i = 0; i < numFuncionarios; i++) {
        if (funcionarios[i].codigo == codigo || strcasecmp(funcionarios[i].nome, nome
) == 0) {
            printf("Codigo: %d\nNome: %s\nTelefone: %s\nCargo: %s\nSalario: %.2f\n", funcionarios[i].codigo, funcionarios[i].nome, funcionarios[i].telefone, funcionarios[i].cargo, funcionarios[i].salario);
            return;
        }
    }
    printf("Funcionario nao encontrado.\n");
}

void mostrarEstadiasCliente() {
    Estadia estadias[100];
    Cliente clientes[100];
    int numEstadias = 0, numClientes = 0;
    int codigoCliente;

    lerEstadias(estadias, &numEstadias);
    lerClientes(clientes, &numClientes);

    printf("Codigo do cliente: ");
    scanf("%d", &codigoCliente);

    // Verificar se o cliente existe
    int clienteEncontrado = 0;
    for (int i = 0; i < numClientes; i++) {
        if (clientes[i].codigo == codigoCliente) {
            clienteEncontrado = 1;
            break;
        }
    }

    if (!clienteEncontrado) {
        printf("Cliente nao encontrado.\n");
        return;
    }

    // Mostrar todas as estadias do cliente
    printf("Estadias do cliente %d:\n", codigoCliente);
    printf("--------------------------\n");
    for (int i = 0; i < numEstadias; i++) {
        if (estadias[i].codigoCliente == codigoCliente) {
            printf("Codigo da Estadia: %d\n", estadias[i].codigo);
            printf("Numero do Quarto: %d\n", estadias[i].numeroQuarto);
            printf("Data de Entrada: %s\n", estadias[i].dataEntrada);
            printf("Data de Saida: %s\n", estadias[i].dataSaida);
            printf("Quantidade de Diarias: %d\n", estadias[i].quantidadeDiarias);
            printf("--------------------------\n");
        }
    }
}

int gerarCodigo(char *filename) {
    //printf("Gerando codigo para %s\n", filename);
    FILE *file = fopen(filename, "r+"); // Abrir o arquivo em modo de leitura e escrita
    int codigo = 1;

    if (file != NULL) {
        // Ler o último código usado (primeira linha do arquivo)
        fscanf(file, "%d", &codigo);

        // Atualizar o próximo código disponível
        int novoCodigo = codigo + 1;

        // Voltar para o início do arquivo para atualizar o código
        rewind(file);
        fprintf(file, "%d\n", novoCodigo);

        // Mover para o final do arquivo para adicionar novos dados
        fseek(file, 0, SEEK_END);
    } else {
        // Arquivo não existe, criar e inicializar com o primeiro código
        file = fopen(filename, "w+");
        if (file != NULL) {
            fprintf(file, "%d\n", codigo); // Escrever o primeiro código no arquivo
        } else {
            printf("Erro ao criar o arquivo %s.\n", filename);
            // Tratamento de erro, se necessário
        }
    }

    fclose(file);
    return codigo;
}

void lerClientes(Cliente clientes[], int *numClientes) {
    FILE *file = fopen(FILENAME_CLIENTES, "r");
    *numClientes = 0;

    if (file != NULL) {
        // Ler o último código usado (primeira linha do arquivo)
        fscanf(file, "%*d"); // Ignorar o primeiro número (último código usado)

        while (fscanf(file, "%d %[^\n] %[^\n] %[^\n]", &clientes[*numClientes].codigo, clientes[*numClientes].nome, clientes[*numClientes].endereco, clientes[*numClientes].telefone) == 4) {
            (*numClientes)++;
        }
        fclose(file);
    } else {
        printf("Erro ao abrir o arquivo %s.\n", FILENAME_CLIENTES);
        // Tratamento de erro, se necessário
    }
}

void salvarCliente(Cliente cliente) {
    FILE *file = fopen(FILENAME_CLIENTES, "a");
    if (file != NULL) {
        fprintf(file, "%d\n%s\n%s\n%s\n", cliente.codigo, cliente.nome, cliente.endereco, cliente.telefone);
        fclose(file);
    }
}

void lerFuncionarios(Funcionario funcionarios[], int *numFuncionarios) {
    FILE *file = fopen(FILENAME_FUNCIONARIOS, "r");
    *numFuncionarios = 0;

    if (file != NULL) {
        // Ler o último código usado (primeira linha do arquivo)
        fscanf(file, "%*d"); // Ignorar o primeiro número (último código usado)

        while (fscanf(file, "%d %[^\n] %[^\n] %[^\n] %f", &funcionarios[*numFuncionarios].codigo, funcionarios[*numFuncionarios].nome, funcionarios[*numFuncionarios].telefone, funcionarios[*numFuncionarios].cargo, &funcionarios[*numFuncionarios].salario) == 5) {
            (*numFuncionarios)++;
        }
        fclose(file);
    } else {
        printf("Erro ao abrir o arquivo %s.\n", FILENAME_FUNCIONARIOS);
        // Tratamento de erro, se necessário
    }
}

void salvarFuncionario(Funcionario funcionario) {
    FILE *file = fopen(FILENAME_FUNCIONARIOS, "a");
    if (file != NULL) {
        fprintf(file, "%d\n%s\n%s\n%s\n%f\n", funcionario.codigo, funcionario.nome, funcionario.telefone, funcionario.cargo, funcionario.salario);
        fclose(file);
    }
}

void lerQuartos(Quarto quartos[], int *numQuartos) {
    FILE *file = fopen(FILENAME_QUARTOS, "r");
    *numQuartos = 0;
    if (file != NULL) {
        while (fscanf(file, "%d %d %f %[^\n]", &quartos[*numQuartos].numero, &quartos[*numQuartos].quantidadeHospedes, &quartos[*numQuartos].valorDiaria, quartos[*numQuartos].status) != EOF) {
            (*numQuartos)++;
        }
        fclose(file);
    }
}

void salvarQuarto(Quarto quarto) {

    FILE *file = fopen(FILENAME_QUARTOS, "a");
    if (file != NULL) {
        fprintf(file, "%d\n%d\n%.2f\n%s\n", quarto.numero, quarto.quantidadeHospedes, quarto.valorDiaria, quarto.status);
        fclose(file);
    }
}

void lerEstadias(Estadia estadias[], int *numEstadias) {
    FILE *file = fopen(FILENAME_ESTADIAS, "r");
    *numEstadias = 0;

    if (file != NULL) {
        // Ignorar o primeiro número (último código usado)
        fscanf(file, "%*d");

        while (fscanf(file, "%d %d %d %s %s %d", &estadias[*numEstadias].codigo, &estadias[*numEstadias].codigoCliente,
                      &estadias[*numEstadias].numeroQuarto, estadias[*numEstadias].dataEntrada,
                      estadias[*numEstadias].dataSaida, &estadias[*numEstadias].quantidadeDiarias) == 6) {
            (*numEstadias)++;
        }
        fclose(file);
    } else {
        printf("Erro ao abrir o arquivo %s.\n", FILENAME_ESTADIAS);
        // Tratamento de erro, se necessário
    }
}

void salvarEstadia(Estadia estadia) {
    FILE *file = fopen(FILENAME_ESTADIAS, "a");
    if (file != NULL) {
        fprintf(file, "%d\n%d\n%d\n%s\n%s\n%d\n", estadia.codigo, estadia.codigoCliente, estadia.numeroQuarto,
                estadia.dataEntrada, estadia.dataSaida, estadia.quantidadeDiarias);
        fclose(file);
    }
}

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

void cadastrarEstadia() {
    Estadia estadia;
    Quarto quartos[100];
    Cliente clientes[100];
    int numQuartos = 0;
    int numClientes = 0;

    lerQuartos(quartos, &numQuartos);

    printf("Codigo do cliente: ");
    scanf("%d", &estadia.codigoCliente);

    lerClientes(clientes, &numClientes);


    // Verificar se o cliente existe
    int clienteEncontrado = 0;
    for (int i = 0; i < numClientes; i++) {
        if (clientes[i].codigo == estadia.codigoCliente) {
            clienteEncontrado = 1;
            break;
        }
    }

    if (!clienteEncontrado) {
        printf("Cliente nao encontrado.\n");
        return;
    }

    printf("Quantidade de hospedes: ");
    scanf("%d", &estadia.quantidadeHospedes); // Ler quantidade de hóspedes

    // Verificar se há um quarto disponível para a quantidade de hóspedes
    int quartoDisponivel = 0;
    for (int i = 0; i < numQuartos; i++) {
        if (quartos[i].quantidadeHospedes >= estadia.quantidadeHospedes && strcmp(quartos[i].status, "desocupado") == 0) {
            quartoDisponivel = 1;
            estadia.numeroQuarto = quartos[i].numero; // Definir o número do quarto correto
            // Marcar o quarto como ocupado diretamente no array
            strcpy(quartos[i].status, "ocupado");
            break;
        }
    }

    if (!quartoDisponivel) {
        printf("Quarto nao disponivel para a quantidade de hospedes informada.\n");
        return;
    }

    printf("Data de entrada (dd/mm/yyyy): ");
    scanf(" %s", estadia.dataEntrada);

    printf("Data de saida (dd/mm/yyyy): ");
    scanf(" %s", estadia.dataSaida);

    // Calcular quantidade de diárias
    estadia.quantidadeDiarias = calcularDiarias(estadia.dataEntrada, estadia.dataSaida);

    // Atualizar arquivo de quartos com o status atualizado
    FILE *fileQuartos = fopen(FILENAME_QUARTOS, "w");
    if (fileQuartos == NULL) {
        printf("Erro ao abrir o arquivo %s para escrita.\n", FILENAME_QUARTOS);
        return;
    }

    for (int i = 0; i < numQuartos; i++) {
        fprintf(fileQuartos, "%d %d %.2f %s\n", quartos[i].numero, quartos[i].quantidadeHospedes,
                                                quartos[i].valorDiaria, quartos[i].status);
    }

    fclose(fileQuartos);

    // Gerar código da estadia
    estadia.codigo = gerarCodigo(FILENAME_ESTADIAS);

    // Salvar estadia no arquivo
    salvarEstadia(estadia);

    printf("\nNumero do quarto: %d\n", estadia.numeroQuarto);
    printf("Quantidade de diarias: %d\n", estadia.quantidadeDiarias);
    printf("Estadia cadastrada com sucesso.\n");
}

void salvarEstadias(Estadia estadias[], int numEstadias) {
    FILE *fileEstadias = fopen(FILENAME_ESTADIAS, "w");
    if (fileEstadias == NULL) {
        printf("Erro ao abrir o arquivo %s para escrita.\n", FILENAME_ESTADIAS);
        return;
    }

    fprintf(fileEstadias, "%d\n", estadias[numEstadias - 1].codigo + 1); // Escrever o próximo código disponível
    for (int i = 0; i < numEstadias; i++) {
        fprintf(fileEstadias, "%d\n%d\n%d\n%s\n%s\n%d\n", estadias[i].codigo, estadias[i].codigoCliente, estadias[i].numeroQuarto,
                estadias[i].dataEntrada, estadias[i].dataSaida, estadias[i].quantidadeDiarias);
    }

    fclose(fileEstadias);
}

void baixarEstadia() {
    Estadia estadias[100];
    Quarto quartos[100];
    Cliente clientes[100];
    int numEstadias = 0, numQuartos = 0, numClientes = 0;
    int codigoCliente, totalDiarias = 0;
    float valorTotal = 0.0;

    lerEstadias(estadias, &numEstadias);
    lerQuartos(quartos, &numQuartos);
    lerClientes(clientes, &numClientes);

    printf("Codigo do cliente: ");
    scanf("%d", &codigoCliente);

    // Verificar se o cliente existe
    int clienteEncontrado = 0;
    for (int i = 0; i < numClientes; i++) {
        if (clientes[i].codigo == codigoCliente) {
            clienteEncontrado = 1;
            break;
        }
    }

    if (!clienteEncontrado) {
        printf("Cliente nao encontrado.\n");
        return;
    }

    // Mostrar todas as estadias do cliente
    printf("Estadias do cliente %d:\n", codigoCliente);
    printf("--------------------------\n");
    for (int i = 0; i < numEstadias; i++) {
        if (estadias[i].codigoCliente == codigoCliente) {
            printf("Codigo da Estadia: %d\n", estadias[i].codigo);
            printf("Numero do Quarto: %d\n", estadias[i].numeroQuarto);
            printf("Data de Entrada: %s\n", estadias[i].dataEntrada);
            printf("Data de Saida: %s\n", estadias[i].dataSaida);
            printf("Quantidade de Diarias: %d\n", estadias[i].quantidadeDiarias);
            printf("--------------------------\n");
        }
    }

    printf("Digite o codigo da estadia a ser baixada: ");
    int codigoEstadia;
    scanf("%d", &codigoEstadia);

    // Encontrar a estadia selecionada
    Estadia estadiaSelecionada;
    int estadiaIndex = -1;
    for (int i = 0; i < numEstadias; i++) {
        if (estadias[i].codigo == codigoEstadia && estadias[i].codigoCliente == codigoCliente) {
            estadiaSelecionada = estadias[i];
            estadiaIndex = i;
            break;
        }
    }

    if (estadiaIndex == -1) {
        printf("Estadia nao encontrada para o cliente.\n");
        return;
    }

    // Calcular valor total da estadia
    for (int i = 0; i < numQuartos; i++) {
        if (quartos[i].numero == estadiaSelecionada.numeroQuarto) {
            valorTotal = estadiaSelecionada.quantidadeDiarias * quartos[i].valorDiaria;
            totalDiarias = estadiaSelecionada.quantidadeDiarias;
            break;
        }
    }

    // Atualizar status do quarto para desocupado no array de quartos
    for (int i = 0; i < numQuartos; i++) {
        if (quartos[i].numero == estadiaSelecionada.numeroQuarto) {
            strcpy(quartos[i].status, "desocupado");
            break;
        }
    }

    // Reescrever o arquivo de quartos com os quartos atualizados
    FILE *fileQuartos = fopen(FILENAME_QUARTOS, "w");
    if (fileQuartos == NULL) {
        printf("Erro ao abrir o arquivo %s para escrita.\n", FILENAME_QUARTOS);
        return;
    }

    for (int i = 0; i < numQuartos; i++) {
        fprintf(fileQuartos, "%d %d %.2f %s\n", quartos[i].numero, quartos[i].quantidadeHospedes,
                quartos[i].valorDiaria, quartos[i].status);
    }

    fclose(fileQuartos);


     // Remover a estadia do array de estadias
    for (int i = estadiaIndex; i < numEstadias - 1; i++) {
        estadias[i] = estadias[i + 1];
    }
    numEstadias--;

    // Reescrever o arquivo de estadias com as estadias restantes
    salvarEstadias(estadias, numEstadias);

    printf("Estadia baixada com sucesso.\n");
    printf("Total de diarias: %d\n", totalDiarias);
    printf("Valor total a pagar: %.2f\n", valorTotal);
}