#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char nome[50];
    char tipo[30];
    int prioridade;
} Item;

typedef struct {
    Item* itens;
    int tamanho;
    int capacidade;
} Mochila;

// ---------------- FUNCOES DA MOCHILA ---------------- //

void inicializarMochila(Mochila* m, int capacidade) {
    m->itens = (Item*) malloc(capacidade * sizeof(Item));
    m->tamanho = 0;
    m->capacidade = capacidade;
}

void aumentarCapacidade(Mochila* m) {
    m->capacidade *= 2;
    m->itens = (Item*) realloc(m->itens, m->capacidade * sizeof(Item));
}

void adicionarItem(Mochila* m, char nome[], char tipo[], int prioridade) {
    if (m->tamanho == m->capacidade) {
        aumentarCapacidade(m);
    }

    strcpy(m->itens[m->tamanho].nome, nome);
    strcpy(m->itens[m->tamanho].tipo, tipo);
    m->itens[m->tamanho].prioridade = prioridade;

    m->tamanho++;
}

void mostrarMochila(Mochila* m) {
    printf("\n===== INVENTARIO =====\n");
    for (int i = 0; i < m->tamanho; i++) {
        printf("%d - %s | Tipo: %s | Prioridade: %d\n",
               i,
               m->itens[i].nome,
               m->itens[i].tipo,
               m->itens[i].prioridade);
    }
}

// ---------------- BUSCA BINARIA ---------------- //

int compararNomes(const Item* a, const Item* b) {
    return strcmp(a->nome, b->nome);
}

int buscaBinaria(Mochila* m, char nome[]) {
    int inicio = 0, fim = m->tamanho - 1;

    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        int cmp = strcmp(m->itens[meio].nome, nome);

        if (cmp == 0) return meio;
        if (cmp < 0) inicio = meio + 1;
        else fim = meio - 1;
    }

    return -1;
}

// ---------------- SELECTION SORT ---------------- //

void ordenarPorNome(Mochila* m) {
    int i, j, menor;
    for (i = 0; i < m->tamanho - 1; i++) {
        menor = i;
        for (j = i + 1; j < m->tamanho; j++) {
            if (strcmp(m->itens[j].nome, m->itens[menor].nome) < 0) {
                menor = j;
            }
        }
        if (menor != i) {
            Item temp = m->itens[i];
            m->itens[i] = m->itens[menor];
            m->itens[menor] = temp;
        }
    }
}

void ordenarPorPrioridade(Mochila* m) {
    int i, j, maior;
    for (i = 0; i < m->tamanho - 1; i++) {
        maior = i;
        for (j = i + 1; j < m->tamanho; j++) {
            if (m->itens[j].prioridade > m->itens[maior].prioridade) {
                maior = j;
            }
        }
        if (maior != i) {
            Item temp = m->itens[i];
            m->itens[i] = m->itens[maior];
            m->itens[maior] = temp;
        }
    }
}

// ---------------- PROGRAMA PRINCIPAL ---------------- //

int main() {
    Mochila mochila;
    inicializarMochila(&mochila, 5);

    int opcao;
    char nome[50], tipo[30];
    int prioridade;

    while (1) {
        printf("\n===== MENU =====\n");
        printf("1 - Adicionar item\n");
        printf("2 - Mostrar inventario\n");
        printf("3 - Ordenar por nome\n");
        printf("4 - Ordenar por prioridade\n");
        printf("5 - Buscar item (busca binaria)\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        if (opcao == 0) break;

        switch (opcao) {

        case 1:
            printf("Nome do item: ");
            scanf("%s", nome);
            printf("Tipo (alimento, arma, ferramenta...): ");
            scanf("%s", tipo);
            printf("Prioridade (1 a 10): ");
            scanf("%d", &prioridade);

            adicionarItem(&mochila, nome, tipo, prioridade);
            printf("Item adicionado!\n");
            break;

        case 2:
            mostrarMochila(&mochila);
            break;

        case 3:
            ordenarPorNome(&mochila);
            printf("Inventario ordenado por nome!\n");
            break;

        case 4:
            ordenarPorPrioridade(&mochila);
            printf("Inventario ordenado por prioridade!\n");
            break;

        case 5:
            printf("Nome do item para buscar: ");
            scanf("%s", nome);
            ordenarPorNome(&mochila);
            int pos;
            pos = buscaBinaria(&mochila, nome);

            if (pos >= 0)
                printf("Item encontrado na posicao %d!\n", pos);
            else
                printf("Item nao encontrado!\n");
            break;

        default:
            printf("Opcao invalida!\n");
        }
    }

    free(mochila.itens);
    return 0;
}
