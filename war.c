#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> // Para func rand()

struct Territorio {
    char nome[30];
    char cor[10];
    int tropas;
};

// Simula o ataque usando ponteiros
void atacar(struct Territorio *atacante, struct Territorio *defensor) {
    // Verifica se são aliados (mesma cor)
    if (strcmp(atacante->cor, defensor->cor) == 0) {
        printf("\nERRO: Nao pode atacar aliados (mesma cor)!\n");
        return;
    }

    // Verifica se tem tropas para atacar
    if (atacante->tropas <= 1) {
        printf("\nERRO: Tropas insuficientes para atacar.\n");
        return;
    }

    // Sorteia dados (1 a 6)
    int dadosAtacante = (rand() % 6) + 1;
    int dadosDefensor = (rand() % 6) + 1;

    printf("\n--- Batalha ---\n");
    printf("Atacante (%d) vs Defensor (%d)\n", dadosAtacante, dadosDefensor);

    if (dadosAtacante > dadosDefensor) {
        printf("Vitoria do Atacante! Territorio conquistado.\n");
        
        // Troca a cor do defensor para a do atacante
        strcpy(defensor->cor, atacante->cor);
        
        // Move metade das tropas
        int mover = atacante->tropas / 2;
        defensor->tropas = mover;
        atacante->tropas = atacante->tropas - mover;
    } else {
        printf("Vitoria da Defesa! Atacante perdeu 1 tropa.\n");
        atacante->tropas = atacante->tropas - 1;
    }
}

int main() {
    struct Territorio *mapa; // Ponteiro para o vetor dinâmico
    int qtdTotal, cadastrados = 0;
    int opcao, idAtk, idDef;

    srand(time(NULL)); // Inicializa aleatoriedade

    // 1. Alocação Dinâmica
    printf("Quantos territorios no jogo? ");
    scanf("%d", &qtdTotal);

    // Cria o vetor na memória
    mapa = (struct Territorio*) calloc(qtdTotal, sizeof(struct Territorio));

    do {
        printf("\n1. Cadastrar | 2. Listar | 3. Atacar | 0. Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: // Cadastro
                if (cadastrados < qtdTotal) {
                    printf("Nome (sem espacos): ");
                    scanf("%s", mapa[cadastrados].nome);
                    
                    printf("Cor (sem espacos): ");
                    scanf("%s", mapa[cadastrados].cor);
                    
                    printf("Tropas: ");
                    scanf("%d", &mapa[cadastrados].tropas);
                    
                    cadastrados++;
                    printf("Salvo!\n");
                } else {
                    printf("Mapa cheio!\n");
                }
                break;

            case 2: // Listagem
                for (int i = 0; i < cadastrados; i++) {
                    printf("[%d] %s | Cor: %s | Tropas: %d\n", i, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
                }
                break;

            case 3: // Ataque
                if (cadastrados < 2) {
                    printf("Precisa de 2 territorios para atacar.\n");
                } else {
                    printf("ID do Atacante: ");
                    scanf("%d", &idAtk);
                    printf("ID do Defensor: ");
                    scanf("%d", &idDef);

                    // Validação simples se o ID existe
                    if (idAtk >= 0 && idAtk < cadastrados && idDef >= 0 && idDef < cadastrados) {
                        // Passa os endereços de memória (ponteiros)
                        atacar(&mapa[idAtk], &mapa[idDef]); 
                    } else {
                        printf("IDs invalidos.\n");
                    }
                }
                break;
        }
    } while (opcao != 0);

    // Limpeza de memória
    free(mapa);
    return 0;
}
