#include <stdio.h>
#include <stdlib.h>
#include "inserir.h"

void extrair_filhos(Node *no, Node *filhos[])
{
    if(no->qtd_chaves == 0)
        return;

    filhos[0] = no->chaves[0].menor;

    for(int i=0;i<no->qtd_chaves;i++)
        filhos[i+1] = no->chaves[i].maior;
}

void reconstruir_ponteiros(Node *no, Node *filhos[])
{
    for(int i=0;i<no->qtd_chaves;i++)
    {
        no->chaves[i].menor = filhos[i];
        no->chaves[i].maior = filhos[i+1];
    }
}

int encontrar_posicao(Node *no,int valor)
{
    int i=0;

    while(i<no->qtd_chaves &&
          valor>no->chaves[i].valor)
        i++;

    return i;
}

void inserir_ordenado(Node *no, key nova)
{
    Node *filhos[ordem + 1];
    extrair_filhos(no, filhos);

    int pos = encontrar_posicao(no, nova.valor);

    for(int i = no->qtd_chaves; i > pos; i--)
        no->chaves[i] = no->chaves[i-1];

    for(int i = no->qtd_chaves + 1; i > pos + 1; i--)
        filhos[i] = filhos[i-1];

    no->chaves[pos] = nova;
    
    filhos[pos] = nova.menor;
    filhos[pos + 1] = nova.maior;

    no->qtd_chaves++;

    reconstruir_ponteiros(no, filhos);
}

void montar_temporario(Node *no,
                       key nova,
                       key temp[])
{
    for(int i=0;i<no->qtd_chaves;i++)
        temp[i]=no->chaves[i];

    temp[no->qtd_chaves]=nova;

    for(int i=1;i<=no->qtd_chaves;i++)
    {
        key atual=temp[i];

        int j=i-1;

        while(j>=0 &&
              temp[j].valor>atual.valor)
        {
            temp[j+1]=temp[j];
            j--;
        }

        temp[j+1]=atual;
    }
}

Node *buscar_no_folha(Node *no, int valor)
{
    if(no->folha)
        return no;

    int pos = encontrar_posicao(no, valor);

    Node *filhos[ordem + 1]; 
    extrair_filhos(no, filhos);

    return buscar_no_folha(filhos[pos], valor);
}

void copiar_chaves(Node *destino,
                   key origem[],
                   int inicio,
                   int fim)
{
    destino->qtd_chaves = 0;

    for(int i=inicio;i<=fim;i++)
    {
        destino->chaves[destino->qtd_chaves++] =
            origem[i];
    }
}

void copiar_filhos(Node *destino,
                   Node *filhos[],
                   int inicio)
{
    Node *temp[ordem + 1];

    for(int i=0;i<=destino->qtd_chaves;i++) {
        temp[i]=filhos[inicio+i];
        if(temp[i] != NULL) {
            temp[i]->antecessor.no = destino; // Garante o vínculo do pai
        }
    }

    reconstruir_ponteiros(destino,temp);
}

key split_node(Node *no, key nova) {

    key temp_chaves[ordem]; 
    montar_temporario(no, nova, temp_chaves);

    Node *filhos_completos[ordem + 1];
    extrair_filhos(no, filhos_completos);

    int pos = encontrar_posicao(no, nova.valor);
    for (int i = ordem; i > pos + 1; i--) {
        filhos_completos[i] = filhos_completos[i - 1];
    }
    filhos_completos[pos + 1] = nova.maior;

    int meio = ordem / 2;
    key chave_subindo = temp_chaves[meio];

    Node *novo_irmao = criar_node();
    novo_irmao->folha = no->folha;
    novo_irmao->antecessor.no = no->antecessor.no; 

    copiar_chaves(no, temp_chaves, 0, meio - 1);
    copiar_chaves(novo_irmao, temp_chaves, meio + 1, ordem - 1);

    if (!no->folha) {
        copiar_filhos(no, filhos_completos, 0);
        copiar_filhos(novo_irmao, filhos_completos, meio + 1);
    }

    chave_subindo.menor = no;
    chave_subindo.maior = novo_irmao;

    return chave_subindo;
}

Node* inserir(Node *raiz, int valor) {

    if (raiz == NULL) {
        raiz = criar_node();
        raiz->chaves[0].valor = valor;
        raiz->chaves[0].menor = NULL;
        raiz->chaves[0].maior = NULL;
        raiz->qtd_chaves = 1;
        raiz->antecessor.no = NULL;
        return raiz;
    }

    Node *folha = buscar_no_folha(raiz, valor);
    
    key nova_chave;
    nova_chave.valor = valor;
    nova_chave.menor = NULL;
    nova_chave.maior = NULL;

    while (folha != NULL) {
        if (folha->qtd_chaves < ordem - 1) {
            inserir_ordenado(folha, nova_chave);
            return raiz; 
        } else {
            nova_chave = split_node(folha, nova_chave);
            
            if (folha == raiz) {
                Node *nova_raiz = criar_node();
                nova_raiz->folha = 0; 
                nova_raiz->chaves[0] = nova_chave;
                nova_raiz->qtd_chaves = 1;
                nova_raiz->antecessor.no = NULL;
                
                nova_chave.menor->antecessor.no = nova_raiz;
                nova_chave.maior->antecessor.no = nova_raiz;
                
                reconstruir_ponteiros(nova_raiz, (Node*[]){nova_chave.menor, nova_chave.maior});
                return nova_raiz;
            }
            
            folha = folha->antecessor.no; 
        }
    }

    return raiz;
}
