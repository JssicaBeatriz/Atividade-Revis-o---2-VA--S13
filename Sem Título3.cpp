#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Tarefa {
    int id;
    char titulo[100];
    int prioridade;
    char data_criacao[11]; // Formato: YYYY-MM-DD
    struct Tarefa* anterior;
    struct Tarefa* proximo;
} Tarefa;

Tarefa* criar_tarefa(int id, const char* titulo, int prioridade, const char* data_criacao) {
    Tarefa* nova_tarefa = (Tarefa*)malloc(sizeof(Tarefa));
    nova_tarefa->id = id;
    strcpy(nova_tarefa->titulo, titulo);
    nova_tarefa->prioridade = prioridade;
    strcpy(nova_tarefa->data_criacao, data_criacao);
    nova_tarefa->anterior = NULL;
    nova_tarefa->proximo = NULL;
    return nova_tarefa;
}

void adicionar_tarefa(Tarefa** cabeca, int id, const char* titulo, int prioridade, const char* data_criacao) {
    Tarefa* nova_tarefa = criar_tarefa(id, titulo, prioridade, data_criacao);
    if (*cabeca == NULL || (*cabeca)->prioridade > prioridade) {
        nova_tarefa->proximo = *cabeca;
        if (*cabeca != NULL) {
            (*cabeca)->anterior = nova_tarefa;
        }
        *cabeca = nova_tarefa;
        return;
    }

    Tarefa* atual = *cabeca;
    while (atual->proximo != NULL && atual->proximo->prioridade <= prioridade) {
        atual = atual->proximo;
    }

    nova_tarefa->proximo = atual->proximo;
    if (atual->proximo != NULL) {
        atual->proximo->anterior = nova_tarefa;
    }
    atual->proximo = nova_tarefa;
    nova_tarefa->anterior = atual;
}

void remover_tarefa(Tarefa** cabeca, int id) {
    Tarefa* atual = *cabeca;
    while (atual != NULL) {
        if (atual->id == id) {
            if (atual->anterior != NULL) {
                atual->anterior->proximo = atual->proximo;
            } else {
                *cabeca = atual->proximo;
            }
            if (atual->proximo != NULL) {
                atual->proximo->anterior = atual->anterior;
            }
            free(atual);
            printf("Tarefa com ID %d removida.\n", id);
            return;
        }
        atual = atual->proximo;
    }
    printf("Tarefa com ID %d não encontrada.\n", id);
}

void buscar_tarefa(Tarefa* cabeca, int id) {
    Tarefa* atual = cabeca;
    while (atual != NULL) {
        if (atual->id == id) {
            printf("Tarefa encontrada:\n");
            printf("ID: %d\nTítulo: %s\nPrioridade: %d\nData de Criação: %s\n", 
                   atual->id, atual->titulo, atual->prioridade, atual->data_criacao);
            return;
        }
        atual = atual->proximo;
    }
    printf("Tarefa com ID %d não encontrada.\n", id);
}

void listar_tarefas(Tarefa* cabeca) {
    Tarefa* atual = cabeca;
    printf("Tarefas em ordem de prioridade:\n");
    while (atual != NULL) {
        printf("ID: %d | Título: %s | Prioridade: %d | Data de Criação: %s\n", 
               atual->id, atual->titulo, atual->prioridade, atual->data_criacao);
        atual = atual->proximo;
    }
}

void listar_tarefas_inversa(Tarefa* cabeca) {
    if (cabeca == NULL) {
        printf("Nenhuma tarefa para listar.\n");
        return;
    }

    Tarefa* atual = cabeca;
    while (atual->proximo != NULL) {
        atual = atual->proximo;
    }

    printf("Tarefas em ordem inversa:\n");
    while (atual != NULL) {
        printf("ID: %d | Título: %s | Prioridade: %d | Data de Criação: %s\n", 
               atual->id, atual->titulo, atual->prioridade, atual->data_criacao);
        atual = atual->anterior;
    }
}

int main() {
    Tarefa* lista_tarefas = NULL;
    int escolha, id, prioridade;
    char titulo[100], data_criacao[11];

    do {
        printf("\nMenu de Gerenciamento de Tarefas:\n");
        printf("1. Adicionar Tarefa\n");
        printf("2. Remover Tarefa\n");
        printf("3. Buscar Tarefa\n");
        printf("4. Listar Tarefas\n");
        printf("5. Listar Tarefas em Ordem Inversa\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &escolha);

        switch (escolha) {
            case 1:
                printf("Digite ID da tarefa: ");
                scanf("%d", &id);
                printf("Digite título da tarefa: ");
                scanf(" %[^\n]", titulo);
                printf("Digite prioridade da tarefa: ");
                scanf("%d", &prioridade);
                printf("Digite data de criação (YYYY-MM-DD): ");
                scanf("%s", data_criacao);
                adicionar_tarefa(&lista_tarefas, id, titulo, prioridade, data_criacao);
                break;
            case 2:
                printf("Digite ID da tarefa a ser removida: ");
                scanf("%d", &id);
                remover_tarefa(&lista_tarefas, id);
                break;
            case 3:
                printf("Digite ID da tarefa a ser buscada: ");
                scanf("%d", &id);
                buscar_tarefa(lista_tarefas, id);
                break;
            case 4:
                listar_tarefas(lista_tarefas);
                break;
            case 5:
                listar_tarefas_inversa(lista_tarefas);
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (escolha != 0);

    return 0;
}

