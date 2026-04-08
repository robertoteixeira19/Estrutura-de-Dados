#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Estrutura para representar os territórios no jogo
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// Função para limpar o buffer do teclado e evitar bugs em leituras subsequentes
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Protótipos das funções
void cadastrarTerritorios(Territorio* mapa, int qtd);
void exibirMapa(Territorio* mapa, int qtd);
void atacar(Territorio* atacante, Territorio* defensor);
void liberarMemoria(Territorio* mapa);

int main() {
    int qtd = 5; 
    srand(time(NULL)); // Semente para números aleatórios (dados)

    // Alocação dinâmica para os territórios
    Territorio* mapa = (Territorio*) malloc(qtd * sizeof(Territorio));
    if (mapa == NULL) return 1;

    printf("========================================\n");
    printf("    WAR ESTRUTURADO - CADASTRO INICIAL\n");
    printf("========================================\n");
    
    cadastrarTerritorios(mapa, qtd);

    // Loop principal do jogo
    while (1) {
        exibirMapa(mapa, qtd);
        printf("\n--- FASE DE ATAQUE ---\n");
        int idxAtk, idxDef;
        
        printf("Escolha o territorio atacante (1 a 5, ou 0 para sair): ");
        if(scanf("%d", &idxAtk) != 1) {
            limparBuffer(); 
            continue;
        }
        
        if (idxAtk == 0) break; // Finaliza o programa

        printf("Escolha o territorio defensor (1 a 5): ");
        if(scanf("%d", &idxDef) != 1) {
            limparBuffer();
            continue;
        }

        // Conversão de entrada (1-5) para índice (0-4)
        int a = idxAtk - 1; 
        int d = idxDef - 1;

        // VALIDAÇÕES DE REGRAS E BLOQUEIOS
        if (a >= 0 && a < qtd && d >= 0 && d < qtd) {
            
            // BLOQUEIO: Território com 0 tropas não pode atacar
            if ((mapa + a)->tropas <= 0) {
                printf("\n[!] BLOQUEADO: O territorio %s esta derrotado e nao pode mais atacar!\n", (mapa + a)->nome);
            } 
            // BLOQUEIO: Não faz sentido atacar um território que já está zerado/conquistado
            else if ((mapa + d)->tropas <= 0) {
                printf("\n[!] BLOQUEADO: O territorio %s ja foi neutralizado!\n", (mapa + d)->nome);
            }
            else if (a == d) {
                printf("\n[!] Erro: Ataque invalido! Um territorio nao ataca a si mesmo.\n");
            } 
            else if (strcmp((mapa + a)->cor, (mapa + d)->cor) == 0) {
                printf("\n[!] Erro: %s e %s sao do mesmo exercito (%s)!\n", (mapa + a)->nome, (mapa + d)->nome, (mapa + a)->cor);
            } 
            else {
                // Executa a batalha
                atacar((mapa + a), (mapa + d));
            }
        } else {
            printf("\n[!] Erro: Numero invalido!\n");
        }

        printf("\nPressione Enter para prosseguir...");
        limparBuffer();
        getchar(); 
    }

    liberarMemoria(mapa);
    return 0;
}

// Função para preencher os dados iniciais
void cadastrarTerritorios(Territorio* mapa, int qtd) {
    for (int i = 0; i < qtd; i++) {
        printf("\n--- Cadastrando Territorio %d ---\n", i + 1);
        
        printf("Nome do Territorio: ");
        scanf(" %29[^\n]", (mapa + i)->nome);
        limparBuffer();

        printf("Cor do Exercito: ");
        scanf(" %9[^\n]", (mapa + i)->cor);
        limparBuffer();

        do {
            printf("Numero de Tropas (1-6): ");
            if (scanf("%d", &(mapa + i)->tropas) != 1) {
                printf("[!] Entrada invalida!\n");
                limparBuffer();
                (mapa + i)->tropas = -1; 
            } else {
                limparBuffer();
            }
        } while((mapa + i)->tropas < 1 || (mapa + i)->tropas > 6);
    }
}

// Função de ataque com lógica de exibição imediata de derrota
void atacar(Territorio* atacante, Territorio* defensor) {
    int dAtk = (rand() % 6) + 1;
    int dDef = (rand() % 6) + 1;

    printf("\n--- RESULTADO DA BATALHA ---\n");
    printf("%s [%d] vs %s [%d]\n", atacante->nome, dAtk, defensor->nome, dDef);

    if (dAtk > dDef) {
        printf("VITORIA DO ATAQUE! %s perdeu uma tropa.\n", defensor->nome);
        defensor->tropas--;

        // EXIBIÇÃO IMEDIATA DA DERROTA/CONQUISTA
        if (defensor->tropas <= 0) {
            defensor->tropas = 0; // Garante valor zero
            strcpy(defensor->cor, atacante->cor); // Atualiza para a cor do conquistador
            printf("\n[!] ATENCAO: O territorio %s foi DERROTADO!\n", defensor->nome);
            printf("[!] %s agora pertence ao exercito %s e esta fora de combate.\n", defensor->nome, defensor->cor);
        }
    } else {
        printf("VITORIA DA DEFESA! %s perdeu uma tropa.\n", atacante->nome);
        atacante->tropas--;
        
        // Se o atacante perder a última tropa tentando atacar
        if (atacante->tropas <= 0) {
            atacante->tropas = 0;
            printf("\n[!] ATENCAO: O territorio atacante (%s) ficou SEM TROPAS e foi derrotado!\n", atacante->nome);
        }
    }
}

// Função para imprimir o mapa e o estado das tropas
void exibirMapa(Territorio* mapa, int qtd) {
    printf("\n========================================\n");
    printf("    MAPA DO MUNDO - ESTADO ATUAL\n");
    printf("========================================\n\n");
    for (int i = 0; i < qtd; i++) {
        if ((mapa + i)->tropas > 0) {
            printf("%d. %s (Exercito %s, Tropas: %d)\n", 
                   i + 1, (mapa + i)->nome, (mapa + i)->cor, (mapa + i)->tropas);
        } else {
            // Se o território foi conquistado/derrotado, exibe a nova cor e o status zerado
            printf("%d. %s (Exercito %s, [DERROTADO/FORA DE COMBATE])\n", 
                   i + 1, (mapa + i)->nome, (mapa + i)->cor);
        }
    }
}

// Liberação de memória
void liberarMemoria(Territorio* mapa) {
    free(mapa);
    printf("\nMemoria liberada. Fim de jogo!\n");
}