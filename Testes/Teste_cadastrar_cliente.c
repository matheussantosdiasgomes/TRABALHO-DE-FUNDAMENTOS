#include <stdio.h>
#include <assert.h>
#include <string.h>

#define FILENAME_CLIENTES "clientes.txt"

typedef struct {
    int codigo;
    char nome[100];
    char endereco[100];
    char telefone[20];
} Cliente;

int gerarCodigo(char *filename) {
    FILE *file = fopen(filename, "r+");
    int codigo = 1;

    if (file != NULL) {
        fscanf(file, "%d", &codigo);
        int novoCodigo = codigo + 1;
        rewind(file);
        fprintf(file, "%d\n", novoCodigo);
    } else {
        file = fopen(filename, "w+");
        if (file != NULL) {
            fprintf(file, "%d\n", codigo);
        } else {
            printf("Erro ao criar o arquivo %s.\n", filename);
        }
    }

    fclose(file);
    return codigo;
}

void salvarCliente(Cliente cliente) {
    FILE *file = fopen(FILENAME_CLIENTES, "a");
    if (file != NULL) {
        fprintf(file, "%d\n%s\n%s\n%s\n", cliente.codigo, cliente.nome, cliente.endereco, cliente.telefone);
        fclose(file);
    } else {
        printf("Erro ao abrir o arquivo %s.\n", FILENAME_CLIENTES);
    }
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

void testarCadastrarCliente() {
    // Nome do arquivo de teste
    char *filename = FILENAME_CLIENTES;

    // Remove qualquer arquivo existente para garantir um teste limpo
    remove(filename);

    // Simula a entrada do usuário
    FILE *input = fopen("input.txt", "w");
    assert(input != NULL);
    fprintf(input, "John Doe\n123 Main St\n555-1234\n");
    fclose(input);

    // Redireciona a entrada padrão para o arquivo de simulação
    freopen("input.txt", "r", stdin);

    // Chama a função para cadastrar o cliente
    cadastrarCliente();

    // Verifica o resultado no arquivo de clientes
    FILE *file = fopen(filename, "r");
    assert(file != NULL);

    int codigo;
    char nome[100];
    char endereco[100];
    char telefone[20];

    // Pular a linha do último código gerado
    fscanf(file, "%d\n", &codigo); // Ignorar o próximo código disponível
    fscanf(file, "%d\n", &codigo); // Ler o código do cliente recém-cadastrado
    assert(codigo == 1); // O primeiro código gerado deve ser 1

    fscanf(file, "%[^\n]\n", nome);
    assert(strcmp(nome, "John Doe") == 0);

    fscanf(file, "%[^\n]\n", endereco);
    assert(strcmp(endereco, "123 Main St") == 0);

    fscanf(file, "%[^\n]\n", telefone);
    assert(strcmp(telefone, "555-1234") == 0);

    fclose(file);

    // Remove o arquivo de teste após o teste
    remove(filename);
    remove("input.txt");

    printf("Todos os testes passaram!\n");
}

int main() {
    testarCadastrarCliente();
    return 0;
}
