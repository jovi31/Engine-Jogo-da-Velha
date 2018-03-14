#include<stdio.h>
#include<stdlib.h>
#define X 'X'
#define O 'O'
#define VAZIO ' '

/*Variáveis globais*/

int     tabuleiro[9] = { 0, 0, 0,
                         0, 0, 0,
                         0, 0, 0};
int     tabuleiroPont[9] = { 3, 2, 3, 2, 4, 2, 3, 2, 3};
char    tabuleiroJogador[9];
char    tabuleiroExp[9] = "012345678";
int     histJogadas[9];
int     prof = 0;
int     profIni = 0;
int     vez = 1;                            // 1 - x | 2 - o

/*Funções e procedimentos*/

int     analisarJogo(int vAnterior, int *melhorMov);
void    preencherHist();
int     avaliarTab();                       // Retorna o estado do jogo.
int     compPontTotal(int atual,int anterior);
void    calcularMelhorPont(int *pont,
                           int *melhor,
                           int mov,
                           int *mMov);
int     ehDisponivel(int num);              // Verifica se a jogada está disponível. -> 1 - V
void    trocarVez();
void    fazerJogada(int num);               // Registra a jogada.
void    voltarUmLance();                    // Volta para uma posição anterior.
void    converterTab();
void    exibirTabuleiro();
int     escolherJogada();

int main(){
    int opc;
    int pont = 0;
    int melhorMovimento;

    preencherHist();

    while(prof < 9 && pont == 0){
        analisarJogo(3, &melhorMovimento);
        fazerJogada(melhorMovimento);
        pont = avaliarTab();
        if(pont == 0 && prof < 9){
            fazerJogada(escolherJogada());
            profIni = prof;
            pont = avaliarTab();
        }
    }

    exibirTabuleiro();

    if(pont == 1){
        printf("\nVoce perdeu.\n");
    }else{
        if(pont == -1){
            printf("\nVoce ganhou!\n");
        }else{
            printf("\nDeu velha!\n");
        }
    }

    system("PAUSE");
    system("CLS");

    return 0;
}//Fim do main

int analisarJogo(int vAnterior, int *melhorMov){
    int i;
    int pontuacao = 0;
    int melhorPont = 3;
    int melhorLance = 0;
    int vAtual = 3;

    pontuacao = avaliarTab();

    if(pontuacao != 0){
        voltarUmLance();
        return pontuacao;
    }else{
        if(prof == 9){
            voltarUmLance();
            return pontuacao;
        }
    }

    for(i = 0; i <= 8; i++){
        if(ehDisponivel(i) == 1){
            fazerJogada(i);

            pontuacao = analisarJogo(vAtual, melhorMov);

            calcularMelhorPont(&pontuacao, &melhorPont, i, &melhorLance);

            vAtual = melhorPont;

            if(vAnterior != 3){
                if(vez == 1){
                    if(vAtual >= vAnterior){
                        voltarUmLance();
                        return melhorPont;
                    }
                }else{
                    if(vAtual <= vAnterior){
                        voltarUmLance();
                        return melhorPont;
                    }
                }
            }
        }
    }

    if(prof != profIni){
        voltarUmLance();
    }

    *melhorMov = melhorLance;

    return melhorPont;
}//Fim de analisarJogo

void preencherHist(){
    int i, j;

    for(i = 0; i <= 8; i++){
        histJogadas[i] = 9;
    }
}//Fim de preencherHist

int avaliarTab(){
    int result = 0;

    //Linha
    if(tabuleiro[0] == tabuleiro[1] && tabuleiro[1] == tabuleiro[2] && tabuleiro[0] != 0){
        result = 1;
    }
    if(tabuleiro[3] == tabuleiro[4] && tabuleiro[4] == tabuleiro[5] && tabuleiro[3] != 0){
        result = 1;
    }
    if(tabuleiro[6] == tabuleiro[7] && tabuleiro[7] == tabuleiro[8] && tabuleiro[6] != 0){
        result = 1;
    }

    //Coluna
    if(tabuleiro[0] == tabuleiro[3] && tabuleiro[3] == tabuleiro[6] && tabuleiro[0] != 0){
        result = 1;
    }
    if(tabuleiro[1] == tabuleiro[4] && tabuleiro[4] == tabuleiro[7] && tabuleiro[1] != 0){
        result = 1;
    }
    if(tabuleiro[2] == tabuleiro[5] && tabuleiro[5] == tabuleiro[8] && tabuleiro[2] != 0){
        result = 1;
    }

    //Diagonal /
    if(tabuleiro[6] == tabuleiro[4] && tabuleiro[4] == tabuleiro[2] && tabuleiro[6] != 0){
        result = 1;
    }

    //Diagonal
    if(tabuleiro[0] == tabuleiro[4] && tabuleiro[4] == tabuleiro[8] && tabuleiro[0] != 0){
        result = 1;
    }

    if(vez == 1 && result == 1){
        result = -1;
    }

    return result;
}//Fim de avaliarTab

int compPontTotal(int atual,int anterior){
    int i, totAtual = 0, totAnterior = 0;

    tabuleiro[atual] = vez;

    for(i = 0; i <= 8; i++){
        if(tabuleiro[i] == vez){
            totAtual += tabuleiroPont[i];
        }
    }

    tabuleiro[atual] = 0;
    tabuleiro[anterior] = vez;

    for(i = 0; i <= 8; i++){
        if(tabuleiro[i] == vez){
            totAnterior += tabuleiroPont[i];
        }
    }

    tabuleiro[anterior] = 0;

    if(totAtual >= totAnterior){
        return 1;
    }else{
        return 0;
    }
}

void calcularMelhorPont(int *pont, int *melhor, int mov, int *mMov){
    int pontMelhor = 0, pontAtual = 0;

    if(*melhor != 3){
        if(*melhor != *pont){
            if(vez == 1){
                if(*pont >= *melhor){
                    *melhor = *pont;
                    *mMov = mov;
                }
            }else{
                if(*pont <= *melhor){
                    *melhor = *pont;
                    *mMov = mov;
                }
            }
        }else{
            if(compPontTotal(mov, *mMov) == 1){
                *mMov = mov;
            }
        }
    }else{
        *melhor = *pont;
        *mMov = mov;
    }
}//Fim de calcularMelhorPont

int ehDisponivel(int num){
    int i;

    if(tabuleiro[num] == 0){
        return 1;
    }else{
        return 0;
    }
}//Fim de ehDisponivel

void trocarVez(){
    if(vez == 1){
        vez = 2;
    }else{
        vez = 1;
    }
}//Fim de trocarVez

void fazerJogada(int num){
    tabuleiro[num] = vez;
    histJogadas[prof] = num;
    prof++;
    trocarVez();
}//Fim de fazerJogada

void voltarUmLance(){
    int ultJogada;

    prof--;

    ultJogada = histJogadas[prof];

    histJogadas[prof] = 9;

    tabuleiro[ultJogada] = 0;

    trocarVez();
}//Fim de voltarUmLace

void converterTab(){
    int i;

    for(i = 0; i <= 8; i++){
        if(tabuleiro[i] == 0){
            tabuleiroJogador[i] = VAZIO;
        }
        if(tabuleiro[i] == 1){
            tabuleiroJogador[i] = X;
        }
        if(tabuleiro[i] == 2){
            tabuleiroJogador[i] = O;
        }
    }
}

void exibirTabuleiro(){
    int i;

    converterTab();

    for(i = 0; i <= 6; i+=3){
        printf(" %c | %c | %c \n", tabuleiroJogador[0 + i],
                                   tabuleiroJogador[1 + i],
                                   tabuleiroJogador[2 + i]);
        if(i != 6){
            printf("---+---+---\n");
        }
    }

    printf("\n");

    for(i = 0; i <= 6; i+=3){
        printf(" %c | %c | %c \n", tabuleiroExp[0 + i],
                                   tabuleiroExp[1 + i],
                                   tabuleiroExp[2 + i]);
        if(i != 6){
            printf("---+---+---\n");
        }
    }
}

int escolherJogada(){
    int jogada;

    exibirTabuleiro();

    printf("\nEscolha a jogada (0 - 8): ");
    scanf("%d", &jogada);

    system("CLS");

    return jogada;
}
