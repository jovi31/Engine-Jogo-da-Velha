#include<stdio.h>
#include<stdlib.h>
#include "varGlobais.h"
#include "analise.h"
#include "funcMov.h"
#include "interface.h"

int main(){
    int escolha;
    int pont = 0;
    int melhorMovimento;

    preencherHist();
    escolha = escolherVez();

    if(escolha == 1){
        fazerJogada(escolherJogada());
        profIni = prof;
    }

    while(prof < 9 && pont == 0){
        analisarJogo(3, &melhorMovimento);
        fazerJogada(melhorMovimento);
        pont = avaliarTab();
        if(prof < 9 && pont == 0){
            fazerJogada(escolherJogada());
            profIni = prof;
            pont = avaliarTab();
        }
    }

    exibirTabuleiro();

    mensagem(pont, escolha);

    return 0;
}
