#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// CONSTANTES GLOBAIS
#define QTE_TERRITORIO 5
#define TAM_STRING 30
#define TAM_STRING2 10

// DEFINE A ESTRUTURA DE UM TERRITORIO
typedef struct
{
    char nome[TAM_STRING];
    char cor[TAM_STRING2];
    int qteTropas;
} Territorio;

// Função que exibe o estado atual do mapa
void mostrarMapa(Territorio *territorios)
{
    printf("\n===== LISTA DE TROPAS =====\n");
    for (int i = 0; i < QTE_TERRITORIO; i++)
    {
        printf("\nTERRITORIO #%d: ", i + 1);
        printf("%s", territorios[i].nome);
        printf(" (Exercito: %s, ", territorios[i].cor);
        printf("Tropas: %d)\n", territorios[i].qteTropas);
    };
}
// Função que realiza um ataque entre dois territórios
void realizandoAtaque(Territorio *ataque, Territorio *defesa)
{
    int numAtaque = (rand() % 6) + 1;
    int numDefesa = (rand() % 6) + 1;
    printf("\n===RESULTADO DA BATALHA:===\n");
    printf("O atacante %s rolou um dado e tirou: %d\n", ataque->nome, numAtaque);
    printf("O defensor %s rolou um dado e tirou: %d\n", defesa->nome, numDefesa);

    if (numAtaque > numDefesa)
    {
        defesa->qteTropas--;
        if (defesa->qteTropas <= 0)
        {
            printf("CONQUISTA! O territorio %s foi dominado pelo exercito %s\n", defesa->nome, ataque->cor);
            strcpy(defesa->cor, ataque->cor);
        }
    }
    else if (numDefesa > numAtaque)
    {
        ataque->qteTropas--;
        if (ataque->qteTropas <= 0)
        {
            printf("CONQUISTA! O territorio %s foi dominado pelo exercito %s\n", ataque->nome, defesa->cor);
            strcpy(ataque->cor, defesa->cor);
        }
    }
    else
    {
        printf("EMPATE, nenhuma tropa foi perdida!\n");
    }
}
// Função para limpar o buffer do teclado 
void limparBufferEntrada()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

int main()
{
    srand(time(NULL)); // Inicializa o gerador de números aleatórios (baseado no horário atual)

    // Aloca dinamicamente memória para armazenar os territórios
    Territorio *territoriosNoMundo = (Territorio *)calloc(QTE_TERRITORIO, sizeof(Territorio));

    printf("==========WAR ESTRUTURADO==========\n\n");
    printf("Vamos cadastrar as tropas:\n");

    for (int i = 0; i < QTE_TERRITORIO; i++)
    {
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

    printf("\nMENU DO MUNDO - ESTADO ATUAL:");
    // Ponteiros para funções 
    void (*mostrar)(Territorio *) = mostrarMapa;
    void (*acaoAtaque)(Territorio *, Territorio *) = realizandoAtaque;

    mostrar(territoriosNoMundo);

    int resp;
    do
    {
        Territorio *ataque;
        Territorio *defesa;

        printf("\n==FASE DE ATAQUE!==\n");
        printf("Escolha o territorio atacante(1 a 5, ou 0 para sair): ");
        scanf("%d", &resp);
        limparBufferEntrada();

        if (resp <= 0 || resp > QTE_TERRITORIO)
        {
            printf("Programa encerrado!\n");
            break;
        }
        else
        {
            ataque = &territoriosNoMundo[resp - 1];
        }

        printf("\nEscolha o territorio defensor(1 a 5(diferente do ataque), ou 0 para sair): ");
        scanf("%d", &resp);
        limparBufferEntrada();

        if (resp <= 0 || resp > QTE_TERRITORIO)
        {
            printf("Programa encerrado!\n");
            break;
        }
        else
        {
            defesa = &territoriosNoMundo[resp - 1];
        }

        if (ataque == defesa)
        {
            printf("Um territorio nao pode atacar a si mesmo!\n");
            continue;
        }
        else
        {
            acaoAtaque(ataque, defesa);
            mostrar(territoriosNoMundo);
        }

    } while (resp != 0);

    // Libera a memória alocada dinamicamente
    free(territoriosNoMundo);

    return 0;
}
