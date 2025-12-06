#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Territorio {
  char nome[30];
  char cor[10];
  int tropas;
};

// limpar dados de entrada
void limparBuffer() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF);
}

// cadastro dos territórios
int main () {
  struct Territorio territorios[5];
  int numTerritorios = 0;
  char escolha;

  do {

 // exibir menu
    printf("1. Cadastrar territorio\n");
    printf("2. Exibir territorios\n");
    printf("3. Sair\n");
    printf("Escolha uma opcao: ");
    
    scanf(" %c", &escolha);
    limparBuffer();

    switch (escolha) {
      case '1':
        if (numTerritorios < 5) {
          printf("Nome do territorio: ");
          fgets(territorios[numTerritorios].nome, sizeof(territorios[numTerritorios].nome), stdin);

          printf("Cor do territorio: ");
          fgets(territorios[numTerritorios].cor, sizeof(territorios[numTerritorios].cor), stdin);

          printf("Numero de tropas: ");
          scanf("%d", &territorios[numTerritorios].tropas);
          limparBuffer();

          numTerritorios++;
          printf("Territorio cadastrado com sucesso!\n");
        } else {
          printf("Limite de territorios atingido.\n");
        }
        break;

      case '2':
        if (numTerritorios == 0) {
          printf("Nenhum territorio cadastrado.\n");
        } else {
          for (int i = 0; i < numTerritorios; i++) {
            printf("Territorio %d:\n", i + 1);
            printf("Nome: %s\n", territorios[i].nome);
            printf("Cor: %s\n", territorios[i].cor);
            printf("Tropas: %d\n", territorios[i].tropas);
            printf("---------------------\n");
          }
        }
        break;

      case '3':
        printf("\nSaindo do programa.\n");
        break;

      default:
        printf("\nOpcao invalida. Tente novamente.\n");
        printf("Pressione Enter para continuar...");
        getchar();
        break;
    }
  } while (escolha != '3');

  return 0;
}
