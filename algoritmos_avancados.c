#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ============================================================================
//                           PROJETO Detective Quest
// ============================================================================
// Matrícula: 20250212488
// Faculdade: Estácio
// Aluno: Ângelo Oliveira dos Santos
// Cuso: Análise e desenvolvimento de sistemas
// Desafio: nível novato
// Tema 4 - Árvores e Tabela Hash
// ============================================================================

// Estrutura que representa uma sala da mansão
typedef struct Sala {
    char nome[50];           // Nome da sala
    struct Sala *esquerda;   // Ponteiro para a sala à esquerda
    struct Sala *direita;    // Ponteiro para a sala à direita
} Sala;

// Protótipos das funções
Sala* criarSala(const char* nome);
void explorarMansao(Sala* raiz);
void liberarArvore(Sala* raiz);
void exibirMapa(Sala* raiz, int nivel);

int main() {
    printf("=== Detective Quest - Exploracao da Mansao ===\n\n");
    printf("Voce e um detetive investigando um misterio numa mansao antiga.\n");
    printf("Explore os comodos para encontrar pistas!\n\n");

    // Construção do mapa da mansão como árvore binária
    // Nível 0: Hall de entrada (raiz)
    Sala* hall = criarSala("Hall de Entrada");
    
    // Nível 1: Salas conectadas ao Hall
    hall->esquerda = criarSala("Sala de Estar");
    hall->direita = criarSala("Corredor Principal");
    
    // Nível 2: Salas conectadas à Sala de Estar
    hall->esquerda->esquerda = criarSala("Biblioteca");
    hall->esquerda->direita = criarSala("Sala de Musica");
    
    // Nível 2: Salas conectadas ao Corredor Principal
    hall->direita->esquerda = criarSala("Cozinha");
    hall->direita->direita = criarSala("Escritorio");
    
    // Nível 3: Salas mais profundas
    hall->esquerda->esquerda->esquerda = criarSala("Sala Secreta");
    hall->esquerda->direita->direita = criarSala("Varanda");
    hall->direita->esquerda->esquerda = criarSala("Despensa");
    hall->direita->direita->direita = criarSala("Jardim de Inverno");

    // Exibe a estrutura completa da mansão (opcional)
    printf("Mapa completo da mansao (visualizacao hierarquica):\n");
    exibirMapa(hall, 0);
    printf("\n");

    // Inicia a exploração interativa a partir do Hall de Entrada
    explorarMansao(hall);

    // Libera a memória alocada para a árvore
    liberarArvore(hall);
    
    printf("\nInvestigacao concluida. Volte sempre, detetive!\n");
    return 0;
}

/**
 * Cria uma nova sala dinamicamente com o nome especificado
 * @param nome Nome da sala a ser criada
 * @return Ponteiro para a sala criada, ou NULL em caso de erro
 */
Sala* criarSala(const char* nome) {
    // Aloca memória para uma nova sala
    Sala* novaSala = (Sala*)malloc(sizeof(Sala));
    
    if (novaSala == NULL) {
        printf("Erro: nao foi possivel alocar memoria para a sala!\n");
        exit(1);
    }
    
    // Copia o nome para a estrutura da sala
    strcpy(novaSala->nome, nome);
    
    // Inicializa os ponteiros como NULL (sem conexões)
    novaSala->esquerda = NULL;
    novaSala->direita = NULL;
    
    return novaSala;
}

/**
 * Permite a exploração interativa da mansão
 * @param raiz Ponteiro para a sala atual (inicia no Hall de Entrada)
 */
void explorarMansao(Sala* raiz) {
    Sala* salaAtual = raiz;
    char escolha;
    
    printf("=== INICIANDO EXPLORACAO ===\n");
    
    // Loop principal de exploração
    while (salaAtual != NULL) {
        printf("\nVoce esta na: %s\n", salaAtual->nome);
        
        // Verifica se há caminhos disponíveis
        int temEsquerda = (salaAtual->esquerda != NULL);
        int temDireita = (salaAtual->direita != NULL);
        
        if (!temEsquerda && !temDireita) {
            printf("Este e um comodo sem saida. Exploracao concluida neste ramo.\n");
            break;
        }
        
        // Exibe opções de navegação disponíveis
        printf("\nOpcoes de exploracao:\n");
        if (temEsquerda) {
            printf("  (e) Ir para ESQUERDA -> %s\n", salaAtual->esquerda->nome);
        }
        if (temDireita) {
            printf("  (d) Ir para DIREITA -> %s\n", salaAtual->direita->nome);
        }
        printf("  (s) Sair da exploracao\n");
        
        // Obtém a escolha do jogador
        printf("\nPara onde deseja ir? ");
        scanf(" %c", &escolha);
        
        // Processa a escolha do jogador
        switch (escolha) {
            case 'e':
            case 'E':
                if (temEsquerda) {
                    salaAtual = salaAtual->esquerda;
                    printf("\n>>> Movendo-se para a esquerda...\n");
                } else {
                    printf("Nao ha caminho para a esquerda!\n");
                }
                break;
                
            case 'd':
            case 'D':
                if (temDireita) {
                    salaAtual = salaAtual->direita;
                    printf("\n>>> Movendo-se para a direita...\n");
                } else {
                    printf("Nao ha caminho para a direita!\n");
                }
                break;
                
            case 's':
            case 'S':
                printf("Saindo da exploracao...\n");
                return;
                
            default:
                printf("Opcao invalida! Use 'e' para esquerda, 'd' para direita ou 's' para sair.\n");
                break;
        }
    }
    
    printf("\nVoce chegou a um comodo final. Retornando ao Hall de Entrada.\n");
}

/**
 * Libera toda a memória alocada para a árvore (pós-ordem)
 * @param raiz Ponteiro para a raiz da árvore
 */
void liberarArvore(Sala* raiz) {
    if (raiz == NULL) {
        return;
    }
    
    // Libera recursivamente as subárvores esquerda e direita
    liberarArvore(raiz->esquerda);
    liberarArvore(raiz->direita);
    
    // Libera o nó atual
    free(raiz);
}

/**
 * Exibe o mapa completo da mansão de forma hierárquica
 * @param raiz Ponteiro para a raiz da árvore
 * @param nivel Nível atual na hierarquia (para indentação)
 */
void exibirMapa(Sala* raiz, int nivel) {
    if (raiz == NULL) {
        return;
    }
    
    // Indenta de acordo com o nível
    for (int i = 0; i < nivel; i++) {
        printf("  ");
    }
    
    // Exibe o nome da sala
    if (nivel == 0) {
        printf("🏠 %s (Raiz)\n", raiz->nome);
    } else {
        printf("🚪 %s\n", raiz->nome);
    }
    
    // Recursivamente exibe as subárvores
    exibirMapa(raiz->esquerda, nivel + 1);
    exibirMapa(raiz->direita, nivel + 1);
}