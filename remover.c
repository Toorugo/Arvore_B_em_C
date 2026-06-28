#include "remover.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct posicao{
    Node* no;
    int chave;
}posicao;

posicao busca(Node* raiz, int chave){

    posicao elemento;
    int achou = 0;

    while(raiz != NULL && achou == 0){

        for(int a = 0; a < ordem-1; a++){
            if(raiz->chaves[a].valor == chave){
                achou = 1;
                elemento.no = raiz;
                elemento.chave = a;
            }
            else if(raiz->chaves[a].valor < chave){
                
            }
        }

    }
}

void remover_chave(Node** raiz, int chave){

}
