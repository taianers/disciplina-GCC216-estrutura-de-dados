#include <iostream>
using namespace std;

typedef int Dado;

class Noh{
    friend class Lista;
    public:
        Noh(Dado valor);
    private:
        Dado mDado;
        Noh* mProx;
};

class Lista{
    public:
        Lista();
        ~Lista();
        void InsereFim(Dado valor);
        void RemoveIni();
        void RemoveFim();
        void RemoveValor(Dado valor);
        bool Busca(Dado valor, Lista& lista1);
        void Concatena(Lista& lista1, Lista& lista2);
        void Imprime();
        unsigned Tamanho(){ return mTam; }
    private:
        Noh* mIni;
        Noh* mFim;
        unsigned mTam;
};

Noh::Noh(Dado valor){
    mDado = valor;
    mProx = NULL;
}

Lista::Lista(){
    mIni = NULL;
    mFim = NULL;
    mTam = 0;
}

Lista::~Lista(){
    while (mTam != 0){
        RemoveIni();
    }
}

void Lista::InsereFim(Dado valor){
    Noh* novo = new Noh(valor);
    if (mTam == 0){
        mIni = novo;
    }
    else{
        mFim->mProx = novo;
    }
    mFim = novo;
    mTam++;
}

void Lista::RemoveIni(){
    Noh* mAux = mIni;
    if (mTam == 1){
        mIni = NULL;
        mFim = NULL;
    }
    else {
        mIni = mIni->mProx;
    }
    delete mAux;
    mTam--;
}

void Lista::RemoveFim(){
    if (mTam == 1){
        Noh* mAux = mFim;
        mIni = NULL;
        mFim = NULL;
        delete mAux;
    }
    else{
        Noh* mAux = mIni;
        while (mAux->mProx != mFim){
            mAux = mAux->mProx;
        }
        mFim = mAux;
        mFim->mProx = NULL;
        mAux = mAux->mProx;
        delete mAux;
    }
    mTam--;
}

void Lista::RemoveValor(Dado valor){
    if (mTam != 0){
        Noh* mAux = mIni;
        Noh* mAnt = NULL;
        while ((mAux != NULL) and (mAux->mDado != valor)){
            mAnt = mAux;
            mAux = mAux->mProx;
        }
        if (mAux != NULL){
            if (mAux == mIni){
                RemoveIni();
            }
            else if (mAux == mFim){
                RemoveFim();
            }
            else{
                mAnt->mProx = mAux->mProx;
                delete mAux;
                mTam--;
            }
        }
    }
}

bool Lista::Busca(Dado valor, Lista& lista1){
    Noh* mAux = lista1.mIni;
    while (mAux != NULL){
        if (mAux->mDado == valor){
            lista1.RemoveValor(valor);
            return true;
        }
        else{
            mAux = mAux->mProx;
        }
    }
    return false;
}

void Lista::Concatena(Lista& lista1, Lista& lista2){
    Noh* mAux = lista2.mIni;
    while (mAux != NULL){
        if (not lista1.Busca(mAux->mDado, lista1)){
            lista1.InsereFim(mAux->mDado);
        }
        mAux = mAux->mProx;
    }
}

void Lista::Imprime(){
    Noh* mAux = mIni;
    while (mAux != NULL){
        cout << mAux->mDado <<' ';
        mAux = mAux->mProx;
    }
    cout << endl;
}

int main(){
    
    Lista lista1, lista2;
    unsigned tamanho1, tamanho2;
    Dado valor;
    
    cin >> tamanho1;
    for (unsigned i = 0; i < tamanho1; i++){
        cin >> valor;
        lista1.InsereFim(valor);
    }
    cin >> tamanho2;
    for (unsigned i = 0; i < tamanho2; i++){
        cin >> valor;
        lista2.InsereFim(valor);
    }
    lista1.Concatena(lista1, lista2);
    lista1.Imprime();
    
    return 0;
}
