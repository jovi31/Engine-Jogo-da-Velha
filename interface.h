#ifndef INTERFACE_H_INCLUDED
#define INTERFACE_H_INCLUDED
#include "varGlobais.h"
#define VAZIO ' '
#define X 'X'
#define O 'O'

void exibirTabuleiro();
int escolherJogada();
void preencherHist();
void converterTab();
void mensagem(int pont, int vezJogador);
int escolherVez();

void preencherHist(){
    int i;

    for(i = 0; i <= 8; i++){
        histJogadas[i] = 9;
    }
}

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

void mensagem(int pont, int vezJogador){
    if(pont == 1){
        if(vezJogador != 1){
            printf("\nVoce perdeu.\n");
        }else{
            printf("\nVoce ganhou!\n");
        }
    }else{
        if(pont == -1){
            if(vezJogador != 1){
                printf("\nVoce ganhou.\n");
            }else{
                printf("\nVoce perdeu!\n");
            }
        }else{
            printf("\nDeu velha!\n");
        }
    }

    system("PAUSE");
    system("CLS");
}

int escolherVez(){
    int escolha;

    printf("Escolha a sua vez (1/2): ");
    scanf("%d", &escolha);
    getchar();
    system("CLS");

    return escolha;
}

#endif // INTERFACE_H_INCLUDED
