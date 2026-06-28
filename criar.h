#ifndef CRIAR_H
#define CRIAR_H

#define ordem 5
#define minimo 2

typedef struct Node Node;
typedef struct key key;

typedef struct posicao{
    Node* no;
    int chave;
    int M_m;
}posicao;

struct key{
    int valor;
    Node *maior;
    Node *menor;
};

struct Node{
    key chaves[ordem-1];
    posicao antecessor;
    int qtd_chaves;
    int folha;
};

Node* criar_node();

#endif