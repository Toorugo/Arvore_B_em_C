#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int* chaves;
    struct Node* antecessor;
    struct Node* filhos;
    int antecessor_index;
} Node;

Node* criar_no();
int buscar_chave(Node** raiz, int chave);
void inserir_chave(Node** raiz, int chave);
Node* dividir_no(Node** no_cheio);


Node* criar_no(){
    Node* ptr = calloc(sizeof(Node), 1);
    ptr->antecessor = NULL;
    ptr->antecessor_index = -1;
    ptr->chaves = NULL;
    ptr->filhos = NULL;

    return ptr;
}


int buscar_chave(Node** raiz, int chave){
    
    int valores[4] = (*raiz)->chaves;
    for(int i = 0; i < 4; i++){
        if(chave == valores[i]) return chave;
    }

    if((*raiz)->filhos == NULL) return -1;

    for(int i = 0; i < 4; i++){

        if(chave < valores[i]){
            Node* next = &((*raiz)->filhos[i]);
            return buscar_chave(&next, chave);
        }
        else if(chave > valores[i]){
            Node* next = &((*raiz)->filhos[i + 1]);
            return buscar_chave(&next, chave);
        }
        else return -1;

    }
}

Node* dividir_no(Node** no_cheio){

    Node* ptr_pai = criar_no();
    ptr_pai->chaves[0] = (*no_cheio)->chaves[1];

    Node* filho_esquerdo = criar_no();
    filho_esquerdo->chaves[0] = (*no_cheio)->chaves[0];
    filho_esquerdo->antecessor = (*no_cheio)->antecessor;

    Node* filho_direito = criar_no();
    filho_direito->chaves[0] = (*no_cheio)->chaves[2];
    filho_direito->chaves[1] = (*no_cheio)->chaves[3];
    filho_direito->antecessor = (*no_cheio)->antecessor;

    ptr_pai->filhos[0] = *filho_esquerdo;
    ptr_pai->filhos[1] = *filho_direito;

    if((*no_cheio)->antecessor_index != -1){
        Node* antecessor = (*no_cheio)->antecessor;
        antecessor->filhos[(*no_cheio)->antecessor_index] = *ptr_pai;
    }

    free(*no_cheio);
    free(no_cheio);

}
