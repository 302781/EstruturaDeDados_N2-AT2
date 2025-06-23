# 21 / Blackjack Simples

## 🃏 Descrição do Jogo

Este é um jogo de cartas clássico implementado em linguagem C baseado na versão simplificada do Blackjack (o famoso "21"). O objetivo é somar cartas com valor total o mais próximo possível de 21, sem ultrapassar esse número.

### Regras básicas:
- Cada jogador (usuário e computador) recebe inicialmente duas cartas.
- O jogador pode optar por comprar mais cartas (pressionando C) ou parar (P).
- Cartas com figuras (Valete, Dama, Rei) valem 10 pontos.
- O Ás pode valer 1 ou 11 pontos, dependendo da pontuação total da mão.
- O computador compra cartas automaticamente até atingir pelo menos 17 pontos.
- Quem tiver a maior pontuação sem ultrapassar 21 vence.
- Simples 👍

---

## Instruções de Compilação e Execução

### Pré-requisitos:
- Compilador C (como GCC) (instale ele clicando [`aqui`](https://sourceforge.net/projects/mingw/files/latest/download))
- Sistema Windows, Linux ou compatível com terminal

### Estrutura da pasta:

```
├── Blackjack
│   ├── output
│   │   └── blackjack.exe
│   │   └── placar.txt
│   └── blackjack.c

```
### 🔧 Compilação (Windows):
Só executar o botão **play** do programa que estiver usando para testar!

### 🔧 Compilação (Linux):
Abra o terminal e execute:
```gcc
gcc blackjack.c -o output/blackjack
```
Navegue para a pasta `output` no seu terminal:

```powershell
cd output
```
Dai só executar o comando abaixo:
```powershell
./organizador.exe
```
## Organização do Código
### Arquivo principal: blackjack.c
Contém toda a lógica do jogo. Os principais componentes são:

1. Estruturas (Structs)

- `enum Naipe`, `enum Rosto`: Representam os naipes e valores das cartas.
- `struct Carta`: Representa uma carta de baralho.
- `struct No`: Nó da lista encadeada usada para representar o baralho e mãos.
- `struct Jogador`: Contém nome, mão e pontuação do jogador.

2. Funções principais

- `criarBaralho`, `embaralhar`, `comprarDoBaralho`: Gerenciam o baralho embaralhado.
- `adicionarCarta`, `liberarLista`: Operam sobre as listas encadeadas de cartas.
- `calcularPontuacao`: Calcula a pontuação da mão, considerando regras do Ás.
- `imprimirMao`, `imprimirNomeCarta`: Exibem as cartas na tela.
- `registrarPlacar`: Salva o resultado da rodada em placar.txt.
- `exibirPlacar`: Mostra todos os resultados anteriores.
