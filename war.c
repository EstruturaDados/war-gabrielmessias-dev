#include <stdio.h> // Entrada e saída de dados.
#include <stdlib.h> // Alocação dinâmica de memória.
#include <string.h> // Manipulação de strings (strcpy, strcmp).
#include <time.h> // Funções de tempo (srand, rand).

struct Territorio {
    char nome[30];
    char cor[10];
    int tropas;
};

const char* LISTA_MISSOES[] = {
    "Dominar totalmente o mapa (todos os territorios com a mesma cor).",
    "Ter um territorio com mais de 20 tropas.",
    "Eliminar todas as tropas da cor Vermelha.",
    "Conquistar 3 territorios.",
    "Manter a paz (Sobreviver por 5 rodadas)."
};

// --- PROTÓTIPOS DAS FUNÇÕES ---
// Declaramos as funções antes para organizar o código.
void cadastrarTerritorio(struct Territorio *t);
void exibirMapa(struct Territorio *mapa, int qtd);
void atacar(struct Territorio *atacante, struct Territorio *defensor);
void atribuirMissao(char* destino, const char* missoes[], int totalMissoes);
int verificarMissao(char* missao, struct Territorio *mapa, int qtd);
void liberarMemoria(struct Territorio *mapa, char *missao);

int main() {
    struct Territorio *mapa = NULL; // Ponteiro para o vetor de territórios
    char *missaoJogador = NULL;     // Ponteiro para a string da missão
    
    int qtdTotal, cadastrados = 0;
    int opcao, idAtk, idDef;

    srand(time(NULL)); // Inicializa a semente aleatória

    // 1. Configuração Inicial e Alocação
    printf("--- WAR ESTRUTURADO ---\n");
    printf("Quantos territorios tera o jogo? ");
    scanf("%d", &qtdTotal);

    // Alocação dinâmica do Mapa (calloc limpa a memória com zeros)
    mapa = (struct Territorio*) calloc(qtdTotal, sizeof(struct Territorio));
    
    // Alocação dinâmica da Missão (malloc apenas reserva o espaço)
    missaoJogador = (char*) malloc(100 * sizeof(char)); 

    // Sorteia a missão logo no início
    atribuirMissao(missaoJogador, LISTA_MISSOES, 5);
    
    printf("\n>>> SUA MISSAO SECRETA: %s <<<\n", missaoJogador);
    printf("(Pressione Enter para continuar...)");
    getchar(); getchar(); // Pausa simples para leitura

    // 2. Loop do Jogo
    do {
        printf("\n1. Cadastrar | 2. Mapa | 3. Atacar | 4. Ver Missao | 0. Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                if (cadastrados < qtdTotal) {
                    cadastrarTerritorio(&mapa[cadastrados]);
                    cadastrados++;
                } else {
                    printf("Mapa cheio!\n");
                }
                break;

            case 2:
                exibirMapa(mapa, cadastrados);
                break;

            case 3:
                if (cadastrados < 2) {
                    printf("Precisa de pelo menos 2 territorios.\n");
                } else {
                    printf("ID Atacante: ");
                    scanf("%d", &idAtk);
                    printf("ID Defensor: ");
                    scanf("%d", &idDef);

                    if (idAtk >= 0 && idAtk < cadastrados && idDef >= 0 && idDef < cadastrados) {
                        atacar(&mapa[idAtk], &mapa[idDef]);
                        
                        // Após ataque, verifica se venceu
                        if (verificarMissao(missaoJogador, mapa, cadastrados)) {
                            printf("\n********************************\n");
                            printf("PARABENS! MISSAO CUMPRIDA!\n");
                            printf("Vitoria: %s\n", missaoJogador);
                            printf("********************************\n");
                            opcao = 0; // Encerra o jogo
                        }
                    } else {
                        printf("IDs invalidos.\n");
                    }
                }
                break;
                
            case 4:
                printf("Lembrete da Missao: %s\n", missaoJogador);
                break;
        }
    } while (opcao != 0);

    // 3. Encerramento
    liberarMemoria(mapa, missaoJogador);
    
    return 0;
}

// --- FUNÇÕES DO JOGO MODULARIZADAS ---
/*
Sorteia uma missão da lista e copia para a memória do jogador.
 Parâmetros
 destino: Ponteiro para a memória alocada onde a missão será gravada.
 missoes: O vetor contendo as strings de missões possíveis.
 totalMissoes: Quantidade de missões disponíveis.
 */
void atribuirMissao(char* destino, const char* missoes[], int totalMissoes) {
    int indice = rand() % totalMissoes; // Sorteia entre 0 e total-1
    strcpy(destino, missoes[indice]);   // Copia o texto para o destino
}

// Recebe o endereço de um território específico (&mapa[i]) para modificá-lo diretamente na memória.
void cadastrarTerritorio(struct Territorio *t) {
    printf("Nome (sem espacos): ");
    scanf("%s", t->nome);
    
    printf("Cor (sem espacos): ");
    scanf("%s", t->cor);
    
    printf("Tropas: ");
    scanf("%d", &t->tropas);
    
    printf("Territorio salvo com sucesso!\n");
}


// Itera sobre o vetor e mostra o status atual.
void exibirMapa(struct Territorio *mapa, int qtd) {
    printf("\n--- STATUS DO MAPA ---\n");
    if (qtd == 0) {
        printf("Nenhum territorio cadastrado.\n");
        return;
    }
    for (int i = 0; i < qtd; i++) {
        printf("[%d] %s | Dono: %s | Tropas: %d\n", i, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
    printf("----------------------\n");
}

// Lógica de combate usando dados e atualiza as tropas/donos.
void atacar(struct Territorio *atacante, struct Territorio *defensor) {
    // Validação de Aliados
    if (strcmp(atacante->cor, defensor->cor) == 0) {
        printf("\nERRO: Nao pode atacar aliados (mesma cor)!\n");
        return;
    }

    // Validação de Tropas
    if (atacante->tropas <= 1) {
        printf("\nERRO: Tropas insuficientes (Minimo 2).\n");
        return;
    }

    // Simulação de Dados
    int dadoAtk = (rand() % 6) + 1;
    int dadoDef = (rand() % 6) + 1;

    printf("\n--- Batalha: %s vs %s ---\n", atacante->nome, defensor->nome);
    printf("Dados: Atacante [%d] x Defensor [%d]\n", dadoAtk, dadoDef);

    if (dadoAtk > dadoDef) {
        printf("Vitoria do ATACANTE!\n");
        // Troca o dono do território
        strcpy(defensor->cor, atacante->cor);
        
        // Move metade das tropas
        int mover = atacante->tropas / 2;
        defensor->tropas = mover;
        atacante->tropas -= mover;
        
        printf("Territorio conquistado! Agora pertence a %s.\n", defensor->cor);
    } else {
        printf("Vitoria da DEFESA!\n");
        atacante->tropas -= 1; // Penalidade
        printf("Atacante perdeu 1 tropa.\n");
    }
}

/*
 Objetivo: Analisa se a condição de vitória da missão atual foi atingida.
 Retorno: 1 se venceu, 0 se ainda não.
 */
int verificarMissao(char* missao, struct Territorio *mapa, int qtd) {
    if (strstr(missao, "Dominar totalmente") != NULL && qtd > 0) {
        char primeiraCor[10];
        strcpy(primeiraCor, mapa[0].cor); // Pega a cor do primeiro como base
        
        for (int i = 1; i < qtd; i++) {
            if (strcmp(mapa[i].cor, primeiraCor) != 0) {
                return 0; // Encontrou uma cor diferente, não venceu ainda
            }
        }
        return 1; // Todos tem a mesma cor!
    }
    
    return 0;
}

/*
 Função: liberarMemoria
 Objetivo: Limpa o espaço alocado dinamicamente (Heap) antes de fechar o programa.
 */
void liberarMemoria(struct Territorio *mapa, char *missao) {
    if (mapa != NULL) free(mapa);
    if (missao != NULL) free(missao);
    printf("\nMemoria liberada. Encerrando...\n");
}
