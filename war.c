#include <stdio.h>
#include <string.h>

// CONSTANTES GLOBAIS
#define QTE_TERRITORIO 5
#define TAM_STRING 30
#define TAM_STRING2 10

// DEFINE A ESTRUTURA DE UM TERRITORIO
typedef struct {
    char nome[TAM_STRING];
    char cor[TAM_STRING2];
    int qteTropas;
} Territorio;

void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main() {
    Territorio territoriosNoMundo[QTE_TERRITORIO];

    printf("==========WAR ESTRUTURADO==========\n\n");
    printf("Vamos cadastrar as tropas:\n");

    for (int i = 0; i < QTE_TERRITORIO; i++) {
        printf("\nTERRITORIO #%d:\n", i + 1);

        printf("NOME: ");
        fgets(territoriosNoMundo[i].nome, TAM_STRING, stdin);

        printf("COR: ");
        fgets(territoriosNoMundo[i].cor, TAM_STRING2, stdin);

        printf("QUANTIDADE DE TROPAS: ");
        scanf("%d", &territoriosNoMundo[i].qteTropas);
        limparBufferEntrada();

        // Remove o \n do final do fgets
        territoriosNoMundo[i].nome[strcspn(territoriosNoMundo[i].nome, "\n")] = '\0';
        territoriosNoMundo[i].cor[strcspn(territoriosNoMundo[i].cor, "\n")] = '\0';

        printf("\n------------------------------------------\n");
    }

    printf("\n===== LISTA DE TROPAS =====\n");
    for (int i = 0; i < QTE_TERRITORIO; i++) {
        printf("\nTERRITORIO #%d:\n", i + 1);
        printf("Nome: %s\n", territoriosNoMundo[i].nome);
        printf("Cor: %s\n", territoriosNoMundo[i].cor);
        printf("Quantidade de tropas: %d\n", territoriosNoMundo[i].qteTropas);
    }

    return 0;
}
