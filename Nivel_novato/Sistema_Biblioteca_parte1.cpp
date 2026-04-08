#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Constantes para facilitar a manutenção do código no futuro
#define MAX_LIVROS 50
#define TAM_STRING 100

// Uso do 'typedef' para não precisarmos repetir a palavra 'struct' pelo código
typedef struct {
    char nome[TAM_STRING];
    char autor[TAM_STRING];
    char editora[TAM_STRING];
    int edicao;
} Livro;

// Função essencial para consumir o caractere 'Enter' (\n) que sobra no buffer após um scanf
void LimparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main() {
    // Agora podemos usar apenas 'Livro' em vez de 'struct Livro'
    Livro biblioteca[MAX_LIVROS];
    int totalLivros = 0;
    int opcao;
    
    do {
        // Menu principal
        printf("\n==========================================\n");
        printf("         BIBLIOTECA - PARTE 1\n");
        printf("==========================================\n\n");
        printf("1 - Cadastrar novo livro\n");
        printf("2 - Listar todos os livros\n");
        printf("3 - Sair\n");
        printf("Escolha uma opcao: ");
        
        scanf("%d", &opcao);
        LimparBufferEntrada(); // Limpa o '\n' deixado pelo scanf antes de usar fgets
        
        switch (opcao) {
            case 1:
                printf("\n--- Cadastro de Novo Livro ---\n\n");
                
                // Verifica se ainda há espaço na biblioteca
                if (totalLivros < MAX_LIVROS) {
                    
                    // Leitura do Nome
                    printf("Digite o nome do livro: ");
                    fgets(biblioteca[totalLivros].nome, TAM_STRING, stdin);
                    // Remove o '\n' capturado pelo fgets imediatamente após a leitura
                    biblioteca[totalLivros].nome[strcspn(biblioteca[totalLivros].nome, "\n")] = '\0';
                    
                    // Leitura do Autor
                    printf("Digite o autor: ");
                    fgets(biblioteca[totalLivros].autor, TAM_STRING, stdin);
                    biblioteca[totalLivros].autor[strcspn(biblioteca[totalLivros].autor, "\n")] = '\0';
                    
                    // Leitura da Editora
                    printf("Digite a editora: ");
                    fgets(biblioteca[totalLivros].editora, TAM_STRING, stdin);
                    biblioteca[totalLivros].editora[strcspn(biblioteca[totalLivros].editora, "\n")] = '\0';
                    
                    // Leitura da Edição (Número inteiro)
                    printf("Digite a edicao: ");
                    scanf("%d", &biblioteca[totalLivros].edicao);
                    LimparBufferEntrada(); // Limpa o buffer novamente após o scanf
                    
                    // Incrementa o contador de livros cadastrados
                    totalLivros++;
                    
                    printf("\nLivro cadastrado com sucesso!\n");     
                } else {
                    // Aviso caso o limite definido em MAX_LIVROS seja atingido
                    printf("\nBiblioteca cheia! Nao e possivel cadastrar mais livros.\n");
                }
                
                printf("\nPressione Enter para continuar...");
                getchar(); // Pausa a tela até o usuário apertar Enter
                break;
                
            case 2:
                printf("\n--- Lista de Livros Cadastrados ---\n\n");
                
                // Verifica se há livros para mostrar
                if (totalLivros == 0) {
                    printf("Nenhum livro cadastrado ainda.\n"); // Correção de digitação aqui
                } else {
                    // Percorre o array imprimindo os dados de cada livro
                    for (int i = 0; i < totalLivros; i++) {
                        printf("------------------------------\n");
                        printf("LIVRO %d\n", i + 1);
                        printf("Nome: %s\n", biblioteca[i].nome);
                        printf("Autor: %s\n", biblioteca[i].autor);
                        printf("Editora: %s\n", biblioteca[i].editora);
                        printf("Edicao: %d\n", biblioteca[i].edicao);
                    }
                    printf("------------------------------\n");
                }
                
                printf("\nPressione Enter para continuar...");
                getchar(); // Pausa a tela
                break;
                
            case 3:
                printf("\nSaindo do sistema...\n");
                break;
                
            default:
                // Trata entradas inválidas no menu (ex: usuário digita 5)
                printf("\nOpcao invalida! Tente novamente.\n");
                printf("\nPressione Enter para continuar...");
                getchar();
                break;          
        }
    } while (opcao != 3); // O loop continua até o usuário escolher a opção 3
    
    return 0;
}