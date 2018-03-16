#ifndef FUNCMOV_H_INCLUDED
#define FUNCMOV_H_INCLUDED
#include "varGlobais.h"

int ehDisponivel(int num);
void fazerJogada(int num);
void voltarUmLance();
void trocarVez();

int ehDisponivel(int num){
    if(tabuleiro[num] == 0){
        return 1;
    }else{
        return 0;
    }
}

void trocarVez(){
    if(vez == 1){
        vez = 2;
    }else{
        vez = 1;
    }
}

void fazerJogada(int num){
    tabuleiro[num] = vez;
    histJogadas[prof] = num;
    prof++;
    trocarVez();
}

void voltarUmLance(){
    int ultJogada;

    prof--;
    ultJogada = histJogadas[prof];
    histJogadas[prof] = 9;
    tabuleiro[ultJogada] = 0;
    trocarVez();
}

#endif // FUNCMOV_H_INCLUDED
