#include <stdio.h>
#include <string.h>

// Definindo a estrutura com typedef para simplificar o uso
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// Função para garantir que o buffer do teclado esteja sempre limpo
void LimparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main() {
    // Usando o apelido 'Territorio' definido no typedef
    Territorio territorios[5];
    int i;
    
    printf("\n=========================================================\n");
    printf("    Vamos cadastrar os 5 territorios iniciais do mundo\n");
    printf("=========================================================\n");
    
    for (i = 0; i < 5; i++) {
        printf("\n--- Cadastrando Territorio %d ---\n", i + 1);
        
        // Leitura do Nome
        printf("Nome do Territorio: ");
        fgets(territorios[i].nome, 30, stdin);
        // Remove o '\n' imediatamente após a leitura
        territorios[i].nome[strcspn(territorios[i].nome, "\n")] = '\0';
        
        // Leitura da Cor
        printf("Cor do exercito: ");
        fgets(territorios[i].cor, 10, stdin);
        territorios[i].cor[strcspn(territorios[i].cor, "\n")] = '\0';
        
        // Leitura das Tropas
        printf("Quantidade de tropas: ");
        scanf("%d", &territorios[i].tropas);
        
        // Limpa o buffer para a próxima iteração do loop (especialmente para o fgets seguinte)
        LimparBuffer();
    }
    
    printf("\nCadastro inicial concluido com sucesso!\n");
    printf("\n========================================\n");
    printf("      MAPA DO MUNDO - ESTADO ATUAL\n");
    printf("========================================\n");
    
    // Loop de exibição dos dados cadastrados
    for (i = 0; i < 5; i++) {
        printf("TERRITORIO %d:", i + 1);
        printf("\n - Nome: %s", territorios[i].nome);
        printf("\n - Dominado por (Cor): %s", territorios[i].cor);
        printf("\n - Tropas: %d\n", territorios[i].tropas);
        printf("----------------------------------------\n");
    }

    printf("\nFim do relatorio.\n");
    
    return 0;
}