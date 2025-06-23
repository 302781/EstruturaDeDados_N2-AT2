#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// naipes e valores das cartas.

typedef enum{
    COPAS, OUROS, PAUS, ESPADAS
} Naipe;

typedef enum{
    AS = 1, DOIS, TRES, QUATRO, CINCO, SEIS, SETE, OITO, NOVE, DEZ, VALETE, DAMA, REI
} Rosto;

typedef struct{
    Naipe naipe;
    Rosto rosto;
} Carta;

typedef struct No{
    Carta carta;
    struct No* proximo;
} No;

typedef struct{
    char nome[50];
    No* mao; // a mao é uma lista encadeada das cartas
    int pontuacao;
} Jogador;

void adicionarCarta(No** cabeca, Carta carta);
void liberarLista(No* cabeca);
void criarBaralho(No** baralho);
void embaralhar(Carta* array, int n);
Carta comprarDoBaralho(No** baralho);

int calcularPontuacao(No* mao);
void imprimirMao(const char* nome, No* mao, int ocultarPrimeira);
void registrarPlacar(const char* vencedor, int pontuacaoJogador, int pontuacaoComputador);
void exibirPlacar();

int main(){
    srand(time(NULL));
    int opcao;

    while(1){
        printf("\n");
        printf("  ____  _        _    ____ _  __   _   _    ____ _  __         \n");
        printf(" | __ )| |      / \\  / ___| |/ /  | | / \\  / ___| |/ /       \n");
        printf(" |  _ \\| |     / _ \\| |   | ' /_  | |/ _ \\| |   | ' /       \n");
        printf(" | |_) | |___ / ___ \\ |___| . \\ |_| / ___ \\ |___| . \\      \n");
        printf(" |____/|_____/_/   \\_\\____|_|\\_\\___/_/   \\_\\____|_|\\_\\ \n");
        printf("========================================================       \n");
        printf("                       1- Jogar                                \n");
        printf("                       2- Veja o placar!                       \n");
        printf("                       3- Sair                                 \n");
        printf("\n");
        printf(" Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch(opcao){
            case 1:{
                No* baralho = NULL;
                criarBaralho(&baralho);

                Jogador jogador = {"Jogador", NULL, 0};
                Jogador computador = {"Computador", NULL, 0};

                adicionarCarta(&jogador.mao, comprarDoBaralho(&baralho));
                adicionarCarta(&computador.mao, comprarDoBaralho(&baralho));
                adicionarCarta(&jogador.mao, comprarDoBaralho(&baralho));
                adicionarCarta(&computador.mao, comprarDoBaralho(&baralho));

                char escolha = ' ';
                while(1){
                    jogador.pontuacao = calcularPontuacao(jogador.mao);
                    system("clear || cls");
                    printf("--- Vez do Computador ---\n\n");
                    imprimirMao(computador.nome, computador.mao, 1);
                     printf("\n\n--- Sua vez ---\n\n");
                    imprimirMao(jogador.nome, jogador.mao, 0);
                    printf("\nSua pontuacao: %d\n", jogador.pontuacao);
                    if(jogador.pontuacao >= 21){
                        break;
                    }
                    printf("\n(C)omprar outra carta ou (P)arar? ");
                    scanf(" %c", &escolha);
                    if(escolha == 'c' || escolha == 'C'){
                        adicionarCarta(&jogador.mao, comprarDoBaralho(&baralho));
                    } else{
                        break;
                    }
                }

                jogador.pontuacao = calcularPontuacao(jogador.mao);
                if(jogador.pontuacao <= 21){
                    computador.pontuacao = calcularPontuacao(computador.mao);
                    while(computador.pontuacao < 17){
                        adicionarCarta(&computador.mao, comprarDoBaralho(&baralho));
                        computador.pontuacao = calcularPontuacao(computador.mao);
                    }
                } else{
                     computador.pontuacao = calcularPontuacao(computador.mao);
                }

                system("clear || cls");
                printf("\n--- Resultado Final ---\n");
                imprimirMao(computador.nome, computador.mao, 0);
                printf("Pontuacao do Computador: %d\n\n", computador.pontuacao);
                imprimirMao(jogador.nome, jogador.mao, 0);
                printf("Sua pontuacao: %d\n\n", jogador.pontuacao);

                const char* vencedor;
                if(jogador.pontuacao > 21){
                    printf("Voce estourou os 21 (%d pontos)! o Computador venceu! :( \n", jogador.pontuacao);
                    vencedor = "Computador";
                } else if(computador.pontuacao > 21){
                    printf("o Computador estourou os 21 (%d pontos)! Voce venceu!\n", computador.pontuacao);
                    vencedor = "Jogador";
                } else if(jogador.pontuacao > computador.pontuacao){
                    printf("Voce venceu com %d pontos contra %d do Computador!\n", jogador.pontuacao, computador.pontuacao);
                    vencedor = "Jogador";
                } else if(computador.pontuacao > jogador.pontuacao){
                    printf("o Computador venceu com %d pontos contra %d pontos seus!\n", computador.pontuacao, jogador.pontuacao);
                    vencedor = "Computador";
                } else{
                    printf("Empatou! Ambos com %d pontos\n", jogador.pontuacao);
                    vencedor = "Empate";
                }
                
                registrarPlacar(vencedor, jogador.pontuacao, computador.pontuacao);

                liberarLista(baralho);
                liberarLista(jogador.mao);
                liberarLista(computador.mao);
                break;
            }
            case 2:
                exibirPlacar();
                break;
            case 3:
                printf("Obrigado por jogar! Ate mais!\n");
                return 0;
            default:
                printf("Opcao invalida. Tente novamente.\n");
                break;
        }
        printf("\nPressione Enter para continuar...");
        getchar();
        getchar();
        system("clear || cls");
    }

    return 0;
}


void adicionarCarta(No** cabeca, Carta carta){
    No* novoNo = (No*)malloc(sizeof(No));
    if(!novoNo){
        printf("Erro de alocacao de memoria!\n");
        exit(1);
    }
    novoNo->carta = carta;
    novoNo->proximo = *cabeca;
    *cabeca = novoNo;
}


void liberarLista(No* cabeca){
    No* atual = cabeca;
    No* proximo;
    while(atual != NULL){
        proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
}


int getValorCarta(Rosto rosto){
    if(rosto >= VALETE) return 10;
    if(rosto == AS) return 11;
    return rosto;
}


int calcularPontuacao(No* mao){
    int total = 0;
    int ases = 0;
    No* atual = mao;
    while(atual != NULL){
        int valor = getValorCarta(atual->carta.rosto);
        if(valor == 11){
            ases++;
        }
        total += valor;
        atual = atual->proximo;
    }

    while(total > 21 && ases > 0){
        total -= 10;
        ases--;
    }
    return total;
}



void trocar(Carta* a, Carta* b){
    Carta temp = *a;
    *a = *b;
    *b = temp;
}


void embaralhar(Carta* array, int n){
    for(int i = n - 1; i > 0; i--){
        int j = rand() % (i + 1);
        trocar(&array[i], &array[j]);
    }
}


void criarBaralho(No** baralho){
    Carta deckTemporario[52];
    int i = 0;
    for(Naipe n = COPAS; n <= ESPADAS; n++){
        for(Rosto r = AS; r <= REI; r++){
            deckTemporario[i].naipe = n;
            deckTemporario[i].rosto = r;
            i++;
        }
    }

    embaralhar(deckTemporario, 52);

    for(i = 0; i < 52; i++){
        adicionarCarta(baralho, deckTemporario[i]);
    }
}


Carta comprarDoBaralho(No** baralho){
    if(*baralho == NULL){
        printf("O baralho acabou! Algum erro aconteceu.\n");
        exit(1);
    }
    No* topo = *baralho;
    Carta c = topo->carta;
    *baralho = topo->proximo;
    free(topo);
    return c;
}


void imprimirNomeCarta(Carta carta){
    char* rostos[] = {"", "As", "2", "3", "4", "5", "6", "7", "8", "9", "10", "Valete", "Dama", "Rei"};
    char* naipes[] = {"Copas", "Ouros", "Paus", "Espadas"};
    printf("  %s de %s\n", rostos[carta.rosto], naipes[carta.naipe]);
}


void imprimirMao(const char* nome, No* mao, int ocultarPrimeira) {
    printf("Mao do %s:\n", nome);
    No* atual = mao;
    if(ocultarPrimeira){
        printf("  [Carta Oculta]\n");
        atual = atual->proximo;
    }
    while(atual != NULL){
        imprimirNomeCarta(atual->carta);
        atual = atual->proximo;
    }
}

// salvar pontuacao no txt
void registrarPlacar(const char* vencedor, int pontuacaoJogador, int pontuacaoComputador) {
    FILE* arquivo = fopen("placar.txt", "a");
    if(arquivo == NULL){
        printf("Ops, parece que nao existe arquivo do placar!\n");
        return;
    }

    if(strcmp(vencedor, "Empate") == 0){
        fprintf(arquivo, "Resultado: Empate (Jogador: %d, Computador: %d)\n", pontuacaoJogador, pontuacaoComputador);
    } else{
        fprintf(arquivo, "Vencedor: %s (Jogador: %d, Computador: %d)\n", vencedor, pontuacaoJogador, pontuacaoComputador);
    }
    
    fclose(arquivo);
    printf("\nPontuacao salvo em placar.txt\n");
}


void exibirPlacar(){
    FILE* arquivo = fopen("placar.txt", "r");
    char linha[100];

    system("clear || cls");
    printf("--- PLACAR GERAL ---\n");
    if(arquivo == NULL){
        printf("Não há placar registrado ainda. Jogue uma partida.\n");
        return;
    }

    while(fgets(linha, sizeof(linha), arquivo) != NULL){
        printf("%s", linha);
    }

    fclose(arquivo);
    printf("--------------------\n");
}