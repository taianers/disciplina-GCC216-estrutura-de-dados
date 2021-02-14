#include <iostream>
using namespace std;

typedef int Dado;

class Noh{
    friend class ABB;
    public:
        Noh(Dado valor);
    private:
        Dado mDado;
        Noh* mEsq;
        Noh* mDir;
};

class ABB{
    public:
        ABB();
        ~ABB();
        void Insere(Dado valor);
        int PercorrePosOrdem();
        int Diferenca();
    private:
        Noh* mRaiz;
        Noh* InsereRecursivo(Noh* mRaiz, Dado valor);
        void DestruirNohRecursivamente(Noh* mNoh);
        int PercorrePosOrdemAux(Noh* mNoh);
};

Noh::Noh(Dado valor){
    mDado = valor;
    mEsq = NULL;
    mDir = NULL;
}

ABB::ABB(){
    mRaiz = NULL;
}

ABB::~ABB(){
    DestruirNohRecursivamente(mRaiz);
}

void ABB::DestruirNohRecursivamente(Noh* mNoh){
    if (mNoh != NULL) {
        DestruirNohRecursivamente(mNoh->mEsq);
        DestruirNohRecursivamente(mNoh->mDir);
        delete mNoh;
    }
}

void ABB::Insere(Dado valor){
    mRaiz = InsereRecursivo(mRaiz, valor);
}

Noh* ABB::InsereRecursivo(Noh* mNoh, Dado valor){
    if (mNoh == NULL){
        Noh* novo = new Noh(valor);
        return novo;
    }
    else{
        if (valor < mNoh->mDado){
            mNoh->mEsq = InsereRecursivo(mNoh->mEsq, valor);
        }
        else{
            mNoh->mDir = InsereRecursivo(mNoh->mDir, valor);
        }
    }
    return mNoh;
}

int ABB::PercorrePosOrdem(){
    return PercorrePosOrdemAux(mRaiz);
}

int ABB::PercorrePosOrdemAux(Noh* mNoh){
    if (mNoh == NULL){
        return 0;
    }
    return 1 + PercorrePosOrdemAux(mNoh->mEsq) + PercorrePosOrdemAux(mNoh->mDir);
}

int ABB::Diferenca(){
    return PercorrePosOrdemAux(mRaiz->mEsq) - PercorrePosOrdemAux(mRaiz->mDir);
}

int main(){

    ABB abb;
    int valor;
    do{
        cin >> valor;
        if (valor != -1){
            abb.Insere(valor);
        }
    } while (valor != -1);
    cout << abb.PercorrePosOrdem() << ' ' << abb.Diferenca();
    return 0;
}
