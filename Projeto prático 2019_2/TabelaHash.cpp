#include "TabelaHash.h"
#include "Noh.h"
#include "Arduino.h"

typedef int Dado;

int Fun(int chave){
  int h = (2*((chave-(chave%10))/10)) % 10;
  return h;
}

int W(int chave){
  int  k = (chave%10)-1;
  return k;
}

int TabelaHash::Posicao(int chave){
  int pos = Fun(chave) + W(chave);
  return pos;
}

int TabelaHash::DivideChave(Dado chave){
    int k = chave % 10000;
    k = k/100;
    return k;
}

TabelaHash::TabelaHash(int cap){
  elementos = new Noh*[cap];
  capacidade = cap;
  tamanho = 0;
  for(int i = 0; i < cap; i++){
    elementos[i] = nullptr;
  }
}

TabelaHash::~TabelaHash(){
  for(int i = 0; i < capacidade; i++){
    Noh* atual = elementos[i];
    while(atual != nullptr){
      Noh* aux = atual;
      atual = atual->proximo;
      delete aux;
    }
  }
  delete[] elementos;
}
  
void TabelaHash::Inserir(Dado c, int v, int hash){
  if(Recuperar(c, hash) == -1){ // checa se o usuario nao existe no sistema.
    Noh* novo = new Noh(c, v);
    if(elementos[hash] == nullptr){ // primeira posicao do vetor nula.
      elementos[hash] = novo;
      Serial.println("\nUSUARIO INSERIDO COM SUCESSO \n");
    }
    else{ // posicao ocupada, encontra a proxima posicao nula.
      Noh* atual = elementos[hash];
      while(atual->proximo != nullptr){
        atual = atual->proximo;
      }
      atual->proximo = novo;
      Serial.println("\nUSUARIO INSERIDO COM SUCESSO \n");
    } 
    tamanho++;
  }
  else{ // matricula ja cadastrada.
    Serial.println("Falha na insercao, matricula ja cadastrada!");
  }
}

int TabelaHash::Recuperar(Dado c, int hash){
  if((elementos[hash] != nullptr ) and (elementos[hash]->matricula == c)){ // testa se a posicao nao Ã© nula, e se a matricula buscada Ã© a mesma na primeira posicao.
    return elementos[hash]->creditos;
  }
  else{ // primeira matricula da posicao nao Ã© a desejada, percorre a lista.
    Noh* atual = elementos[hash];
    while((atual != nullptr) and (atual->matricula != c)){ // percorre enquanto a lista nao for nula, e atÃ© encontrar a matricula desejada.
      atual = atual->proximo;
    }
    if((atual != nullptr) and (atual->matricula == c)){ // encontrou a matricula, retorna quantidade de creditos.
      return atual->creditos;
    }
    else{ //matricula nao encontrada
      return -1;
    }
  }
}

void TabelaHash::Remover(Dado c){
  int hash = Posicao(DivideChave(c)); // calcula posicao
  if((elementos[hash] != nullptr) and (elementos[hash]->matricula == c)){ // matricula buscada e a primeira da posicao, deleta matricula.
    Noh* removido = elementos[hash];
    elementos[hash] = elementos[hash]->proximo;
    delete removido;
    Serial.println("\nUSUARIO DELETADO COM SUCESSO \n");
    tamanho--;
  }
  else{ //matricula nao e a primeira, percorre a lista.
    Noh* atual = elementos[hash];
    Noh* anterior;
    while((atual != nullptr) and (atual->matricula != c)){ // enquanto o atual for diferente de nulo, e a matricula diferente da buscada, recebe proxima matricula.
      anterior = atual;
      atual = atual->proximo;
    }
    if((atual != nullptr) and (atual->matricula == c)){ //encontrou a matricula, agora deleta.
      anterior->proximo = atual->proximo;
      delete atual;
      tamanho--;
      Serial.println("\nUSUARIO DELETADO COM SUCESSO \n");
    }
    else{ // matricula nao encontrada
      Serial.println("Falha na remocao, matricula nao encontrada!");
    }
  }
}

void TabelaHash::Percorrer(){ // imprime todos os usuarios, em suas respectivas posicoes, com matricula e quantidade de creditos.
  Noh* atual;
  for(int i = 0; i < 10; i++){
    Serial.print(i);
    Serial.print(":");
    atual = elementos[i];
    while(atual != nullptr){
      Serial.print("[");
      Serial.print(atual->matricula);
      Serial.print("/");
      Serial.print(atual->creditos);
      Serial.print("]->");
      atual = atual->proximo;
    }
    Serial.println("NULL " );
  }
  Serial.print("Quantidade de usuarios cadastrados: ");
  Serial.println(tamanho );
}
