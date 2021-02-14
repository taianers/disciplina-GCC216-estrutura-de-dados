#ifndef NOH_H
#define NOH_H

typedef int Dado;

class Noh{
  friend class TabelaHash;
  private:
    Dado matricula;
    int creditos;
    Noh* proximo;
  public:
    Noh(Dado c, int v);
};
#endif
