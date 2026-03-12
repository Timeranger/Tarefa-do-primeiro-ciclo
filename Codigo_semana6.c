#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define MAX_CLIENTES 100

typedef struct {
    char nome[255];
    char telefone[20];
    char email[255];
} Cliente;

void cadastrarCliente(Cliente clientes[], int *total) {

    if (*total >= MAX_CLIENTES) {
        printf("Limite máximo de clientes atingido!\n");
        return;
    }

    printf("\n=== Cadastro Cliente ===\n");

    printf("Nome: ");
    fgets(clientes[*total].nome, 255, stdin);
    clientes[*total].nome[strcspn(clientes[*total].nome, "\n")] = '\0';

    printf("Telefone: ");
    fgets(clientes[*total].telefone, 20, stdin);
    clientes[*total].telefone[strcspn(clientes[*total].telefone, "\n")] = '\0';

    printf("Email: ");
    fgets(clientes[*total].email, 255, stdin);
    clientes[*total].email[strcspn(clientes[*total].email, "\n")] = '\0';

    (*total)++;

    printf("Cliente cadastrado com sucesso!\n\n");
}

void listarClientes(Cliente clientes[], int total) {

    if (total == 0) {
        printf("Nenhum cliente cadastrado.\n\n");
        return;
    }

    printf("\n=== Lista de Clientes ===\n");

    for (int i = 0; i < total; i++) {
        printf("Cliente %d\n", i + 1);
        printf("Nome: %s\n", clientes[i].nome);
        printf("Telefone: %s\n", clientes[i].telefone);
        printf("Email: %s\n", clientes[i].email);
        printf("-------------------------\n");
    }

    printf("\n");
}

void buscarCliente(Cliente clientes[], int total) {

    if (total == 0) {
        printf("Nenhum cliente cadastrado.\n\n");
        return;
    }

    char nomeBusca[255];
    int encontrado = 0;

    printf("Digite o nome do cliente para buscar: ");
    fgets(nomeBusca, 255, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    for (int i = 0; i < total; i++) {

        if (strcmp(clientes[i].nome, nomeBusca) == 0) {

            printf("\nCliente encontrado:\n");
            printf("Nome: %s\n", clientes[i].nome);
            printf("Telefone: %s\n", clientes[i].telefone);
            printf("Email: %s\n\n", clientes[i].email);

            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("Cliente não encontrado.\n\n");
    }
}

void editarCliente(Cliente clientes[], int total) {

    if (total == 0) {
        printf("Nenhum cliente cadastrado.\n\n");
        return;
    }

    char nomeBusca[255];
    int encontrado = 0;

    printf("Digite o nome do cliente que deseja editar: ");
    fgets(nomeBusca, 255, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    for (int i = 0; i < total; i++) {

        if (strcmp(clientes[i].nome, nomeBusca) == 0) {

            printf("\nCliente encontrado!\n");

            printf("Novo telefone: ");
            fgets(clientes[i].telefone, 20, stdin);
            clientes[i].telefone[strcspn(clientes[i].telefone, "\n")] = '\0';

            printf("Novo email: ");
            fgets(clientes[i].email, 255, stdin);
            clientes[i].email[strcspn(clientes[i].email, "\n")] = '\0';

            printf("Cliente atualizado com sucesso!\n\n");

            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("Cliente não encontrado.\n\n");
    }
}

void removerCliente(Cliente clientes[], int *total) {

    if (*total == 0) {
        printf("Nenhum cliente cadastrado.\n\n");
        return;
    }

    char nomeBusca[255];
    int encontrado = -1;

    printf("Digite o nome do cliente que deseja remover: ");
    fgets(nomeBusca, 255, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    for (int i = 0; i < *total; i++) {

        if (strcmp(clientes[i].nome, nomeBusca) == 0) {
            encontrado = i;
            break;
        }
    }

    if (encontrado == -1) {
        printf("Cliente não encontrado.\n\n");
        return;
    }

    for (int i = encontrado; i < *total - 1; i++) {
        clientes[i] = clientes[i + 1];
    }

    (*total)--;

    printf("Cliente removido com sucesso!\n\n");
}

/* ---------- FUNÇÃO RECURSIVA ---------- */

int contarNomesRecursivo(Cliente clientes[], int total, int indice, int tamanho) {

    if (indice >= total) {
        return 0;
    }

    int contador = 0;

    if (strlen(clientes[indice].nome) == tamanho) {
        printf("- %s\n", clientes[indice].nome);
        contador = 1;
    }

    return contador + contarNomesRecursivo(clientes, total, indice + 1, tamanho);
}

void estatisticas(Cliente clientes[], int total) {

    if (total == 0) {
        printf("Nenhum cliente cadastrado.\n\n");
        return;
    }

    int tamanho;

    printf("Digite a quantidade de caracteres do nome: ");
    scanf("%d", &tamanho);
    getchar();

    printf("\nClientes com %d caracteres:\n", tamanho);

    int resultado = contarNomesRecursivo(clientes, total, 0, tamanho);

    printf("\nTotal encontrado: %d\n\n", resultado);
}

int main() {

    setlocale(LC_ALL, "pt_BR.UTF-8");

    Cliente clientes[MAX_CLIENTES];
    int totalClientes = 0;
    int opcao = 0;

    printf("Seja bem-vindo!\n\n");

    while (opcao != 7) {

        printf("1 - Cadastrar cliente\n");
        printf("2 - Listar clientes\n");
        printf("3 - Buscar cliente\n");
        printf("4 - Editar cliente\n");
        printf("5 - Remover cliente\n");
        printf("6 - Estatísticas\n");
        printf("7 - Sair\n");

        scanf("%d", &opcao);
        getchar();

        printf("\n");

        if (opcao == 1)
            cadastrarCliente(clientes, &totalClientes);

        if (opcao == 2)
            listarClientes(clientes, totalClientes);

        if (opcao == 3)
            buscarCliente(clientes, totalClientes);

        if (opcao == 4)
            editarCliente(clientes, totalClientes);

        if (opcao == 5)
            removerCliente(clientes, &totalClientes);

        if (opcao == 6)
            estatisticas(clientes, totalClientes);

        if (opcao < 1 || opcao > 7)
            printf("Opcao invalida!\n\n");
    }

    return 0;
}
