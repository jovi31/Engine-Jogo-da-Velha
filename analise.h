#ifndef ANALISE_H_INCLUDED
#define ANALISE_H_INCLUDED
#include "varGlobais.h"
#include "funcMov.h"

void calcularMelhorPont(int *pont, int *melhor, int mov, int *mMov);
int analisarJogo(int vAnterior, int *melhorMov);
int compPontTotal(int atual, int anterior);
int avaliarTab();

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
}

int avaliarTab(){
    int result = 0;

    if(tabuleiro[0] == tabuleiro[1] && tabuleiro[1] == tabuleiro[2] && tabuleiro[0] != 0){
        result = 1;
    }
    if(tabuleiro[3] == tabuleiro[4] && tabuleiro[4] == tabuleiro[5] && tabuleiro[3] != 0){
        result = 1;
    }
    if(tabuleiro[6] == tabuleiro[7] && tabuleiro[7] == tabuleiro[8] && tabuleiro[6] != 0){
        result = 1;
    }

    if(tabuleiro[0] == tabuleiro[3] && tabuleiro[3] == tabuleiro[6] && tabuleiro[0] != 0){
        result = 1;
    }
    if(tabuleiro[1] == tabuleiro[4] && tabuleiro[4] == tabuleiro[7] && tabuleiro[1] != 0){
        result = 1;
    }
    if(tabuleiro[2] == tabuleiro[5] && tabuleiro[5] == tabuleiro[8] && tabuleiro[2] != 0){
        result = 1;
    }

    if(tabuleiro[6] == tabuleiro[4] && tabuleiro[4] == tabuleiro[2] && tabuleiro[6] != 0){
        result = 1;
    }

    if(tabuleiro[0] == tabuleiro[4] && tabuleiro[4] == tabuleiro[8] && tabuleiro[0] != 0){
        result = 1;
    }

    if(vez == 1 && result == 1){
        result = -1;
    }

    return result;
}

void calcularMelhorPont(int *pont, int *melhor, int mov, int *mMov){
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
}

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

#endif // ANALISE_H_INCLUDED
