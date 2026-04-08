#include <stdio.h>   // Biblioteca padrão para entrada e saída (printf, scanf)
#include <stdlib.h>  // Biblioteca para alocação de memória (malloc, calloc, free)
#include <string.h>  // Biblioteca para manipular strings (strcspn, strlen)

// Definição de constantes para evitar "números mágicos"
#define MAX_LIVROS 50
#define TAM_STRING 100
#define MAX_EMPRESTIMOS 100

// Definição da estrutura para Livros
typedef struct {
    char nome[TAM_STRING];
    char autor[TAM_STRING];
    char editora[TAM_STRING];
    int edicao;
    int disponivel; // 1 para Disponível, 0 para Emprestado
} Livro;

// Definição da estrutura para Empréstimos
typedef struct {
    int indiceLivro; // Índice do livro no array da biblioteca
    char nomeUsuario[TAM_STRING];
} Emprestimo;

// Função para limpar o lixo do teclado
void LimparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main() {
    // Alocação dinâmica de memória
    Livro *biblioteca = (Livro *) calloc(MAX_LIVROS, sizeof(Livro));
    Emprestimo *emprestimos = (Emprestimo *) malloc(MAX_EMPRESTIMOS * sizeof(Emprestimo));

    // Verificação de segurança na alocação
    if (biblioteca == NULL || emprestimos == NULL) {
        printf("Erro: Falha ao alocar memoria.\n");
        return 1;
    }

    int totalLivros = 0;
    int totalEmprestimos = 0;
    int opcao;
    
    do {
        // Menu visual principal
        printf("\n==========================================\n");
        printf("         BIBLIOTECA - PARTE 2\n");
        printf("==========================================\n\n");
        printf("1 - Cadastrar novo livro\n");
        printf("2 - Listar todos os livros\n");
        printf("3 - Realizar emprestimo\n");
        printf("4 - Listar emprestimos\n");
        printf("5 - Sair\n");
        printf("-------------------------------------------\n");
        printf("Escolha uma opcao: ");
        
        scanf("%d", &opcao);
        LimparBufferEntrada(); // Limpeza após ler a opção do menu
        
        switch (opcao) {
            case 1: // CADASTRO
                printf("\n--- Cadastro de Novo Livro ---\n\n");
                if (totalLivros < MAX_LIVROS) {
                    printf("Digite o nome do livro: ");
                    fgets(biblioteca[totalLivros].nome, TAM_STRING, stdin);
                    biblioteca[totalLivros].nome[strcspn(biblioteca[totalLivros].nome, "\n")] = '\0';
                    
                    printf("Digite o autor: ");
                    fgets(biblioteca[totalLivros].autor, TAM_STRING, stdin);
                    biblioteca[totalLivros].autor[strcspn(biblioteca[totalLivros].autor, "\n")] = '\0';
                    
                    printf("Digite a editora: ");
                    fgets(biblioteca[totalLivros].editora, TAM_STRING, stdin);
                    biblioteca[totalLivros].editora[strcspn(biblioteca[totalLivros].editora, "\n")] = '\0';
                    
                    printf("Digite a edicao: ");
                    scanf("%d", &biblioteca[totalLivros].edicao);
                    LimparBufferEntrada(); // MUITO IMPORTANTE: Limpa o buffer após o scanf da edição
                    
                    biblioteca[totalLivros].disponivel = 1;
                    totalLivros++;
                    printf("\nLivro cadastrado com sucesso!\n");     
                } else {
                    printf("\nErro: Biblioteca cheia!\n");
                }
                break;
                
            case 2: // LISTAGEM DE LIVROS
                printf("\n--- Lista de Livros Cadastrados ---\n\n");
                if (totalLivros == 0) {
                    printf("Nenhum livro no acervo.\n");
                } else {
                    for (int i = 0; i < totalLivros; i++) {
                        printf("------------------------------\n");
                        printf("ID: %d | Nome: %s\n", i + 1, biblioteca[i].nome);
                        printf("Autor: %s | Status: %s\n", 
                               biblioteca[i].autor, 
                               biblioteca[i].disponivel ? "Disponivel" : "Emprestado");
                    }
                }
                break;

            case 3: // REALIZAR EMPRÉSTIMO
                printf("\n--- Realizar Emprestimo ---\n\n");
                if (totalEmprestimos >= MAX_EMPRESTIMOS) {
                    printf("Limite de emprestimos atingido!\n");
                } else {
                    int disponiveis = 0;
                    for (int i = 0; i < totalLivros; i++) {
                        if (biblioteca[i].disponivel) {
                            printf("%d - %s\n", i + 1, biblioteca[i].nome);
                            disponiveis++;
                        }
                    }

                    if (disponiveis == 0) {
                        printf("Nenhum livro disponivel para emprestimo.\n");
                    } else {
                        printf("\nNumero do livro: ");
                        int numLivro;
                        scanf("%d", &numLivro);
                        LimparBufferEntrada(); // Limpa após ler o número do livro

                        int indice = numLivro - 1;

                        if (indice >= 0 && indice < totalLivros && biblioteca[indice].disponivel) {
                            printf("Nome do usuario: ");
                            fgets(emprestimos[totalEmprestimos].nomeUsuario, TAM_STRING, stdin);
                            emprestimos[totalEmprestimos].nomeUsuario[strcspn(emprestimos[totalEmprestimos].nomeUsuario, "\n")] = '\0';

                            emprestimos[totalEmprestimos].indiceLivro = indice;
                            biblioteca[indice].disponivel = 0;
                            totalEmprestimos++;
                            printf("\nEmprestimo realizado com sucesso!\n");
                        } else {
                            printf("\nErro: Numero invalido ou livro ja emprestado.\n");
                        }
                    }
                }
                break;
                
            case 4: // LISTAGEM DE EMPRÉSTIMOS
                printf("\n--- Lista de Emprestimos Ativos ---\n\n");
                if (totalEmprestimos == 0) {
                    printf("Nenhum emprestimo registrado.\n");
                } else {
                    for (int i = 0; i < totalEmprestimos; i++) {
                        int idx = emprestimos[i].indiceLivro;
                        printf("Livro: %s | Usuario: %s\n", 
                               biblioteca[idx].nome, 
                               emprestimos[i].nomeUsuario);
                    }
                }
                break;
                
            case 5: // SAÍDA
                printf("\nEncerrando o sistema e liberando memoria...\n");
                break;
                
            default:
                printf("\nOpção invalida!\n");
                break;          
        }

        // --- ÚNICA PAUSA DO SISTEMA ---
        // Este bloco centraliza a pausa para todas as opções, evitando duplicação.
        if (opcao != 5) {
            printf("\n-------------------------------------------");
            printf("\nPressione Enter para voltar ao menu...");
            getchar(); // Aguarda o usuário pressionar Enter
        }

    } while (opcao != 5);
    
    // Liberação da memória alocada
    free(biblioteca);
    free(emprestimos);
    
    return 0;
}