#include <stdio.h>
#include <stdlib.h>
#include "inserir.h"

void inserir_chave(Node** raiz, int chave){
    int i =0;

    while(chave > (*raiz)->chaves[i].valor) i++;

    key next = (*raiz)->chaves[i];

    if((*raiz)->chaves[i].maior == NULL || (*raiz)->chaves[i].menor == NULL){
        
    }

    else inserir_chave(&next.menor, chave);
    
    
}