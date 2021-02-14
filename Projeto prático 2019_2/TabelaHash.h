#ifndef TABELAHASH_H
#define TABELAHASH_H

#include "Noh.h"
typedef int Dado;

class TabelaHash{
  private:
    Noh** elementos;
    int capacidade;
    int tamanho;
  public:
    TabelaHash(int cap = 100);
    ~TabelaHash();
    void Inserir(Dado c, int v, int hash);
    int Recuperar(Dado c, int hash);
    void Remover(Dado c);
    void Percorrer();
    int Posicao(int chave);
    int DivideChave(Dado chave);
};
#endif
