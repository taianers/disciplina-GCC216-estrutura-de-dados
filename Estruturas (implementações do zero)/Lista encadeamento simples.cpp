#include <iostream>
using namespace std;

typedef int Dado;

class Noh{
    friend class Lista;
    public:
        Noh(Dado valor);
    private:
        Dado mDado;
        Noh* mPtProx;
};

class Lista{
    public:
        Lista();
        ~Lista();
        void InserirEmListaVazia(Dado valor);
        void InserirNoIni(Dado valor);
        void InserirNoFim(Dado valor);
        void InserirNaPos(Dado valor, unsigned int pos);
        Dado RemoverNoIni();
        Dado RemoverNoFim();
        Dado RemoverNaPos(Dado valor);
        unsigned Tamanho() { return mTamanho; }
        bool Vazia();
        void Imprimir();
        int Busca(Dado valor);
        void LimparTudo();
    private:
        Noh* mPtIni;
        Noh* mPtFim;
        unsigned mTamanho;
};

Noh::Noh(Dado valor){
    mDado = valor;
    mPtProx = NULL;
}

Lista::Lista(){
    mPtIni = NULL;
    mPtFim = NULL;
    mTamanho = 0;
}

Lista::~Lista(){
    Noh* iter = mPtIni;
    Noh* mPtProx = NULL;
    while (iter != NULL){
        mPtProx = iter->mPtProx;
        delete iter;
        iter = mPtProx;
    }
    mPtIni = NULL;
    mPtFim = NULL;
    mTamanho = 0;
}

void Lista::InserirEmListaVazia(Dado valor){
    Noh* novo = new Noh(valor);
    if (Vazia()){
        mPtIni = novo;
        mPtFim = novo;
    }
    mTamanho = 1;
}

void Lista::InserirNoIni(Dado valor){
    if (Vazia()){
        InserirEmListaVazia(valor);
    }
    else{
        Noh* novo = new Noh(valor);
        novo->mPtProx = mPtIni;
        mPtIni = novo;
    }
    mTamanho++;
}

void Lista::InserirNoFim(Dado valor){
    if (Vazia()){
        InserirEmListaVazia(valor);
    }
    else{
        Noh* novo = new Noh(valor);
        mPtFim->mPtProx = novo;
        mPtFim = novo;
    }
    mTamanho++;
}

void Lista::InserirNaPos(Dado valor, unsigned int pos){
    if (Vazia()){
        InserirEmListaVazia(valor);
    }
    else if (pos == 0){
        InserirNoIni(valor);
    }
    else if (pos == mTamanho){
        InserirNoFim(valor);
    }
    else{
        Noh* novo = new Noh(valor);
        Noh* mPtAux = mPtIni;
        unsigned int posAux = 0;
        while (posAux < pos - 1){
            mPtAux = mPtAux->mPtProx;
            posAux++;
        }
        novo->mPtProx = mPtAux->mPtProx;
        mPtAux->mPtProx = novo;
        mTamanho++;
    }
}

Dado Lista::RemoverNoIni(){
    if (Vazia()){
        cerr <<"Erro: Não há elementos na lista!";
    }
    else{
        Noh* mPtAux = mPtIni;
        Dado  valor = mPtAux->mDado;
        mPtIni = mPtAux->mPtProx;
        delete mPtAux;
        mTamanho--;
        return valor;
    }
    mPtFim = NULL;
    return Dado();
}

Dado Lista::RemoverNoFim(){
    if (Vazia()){
        cerr <<"Erro: Não há elementos na lista!";
    }
    else{
        Noh* mPtAux = mPtIni;
        while (mPtAux->mPtProx != NULL){
            mPtAux = mPtAux->mPtProx;
            Dado valor = mPtAux->mDado;
            delete mPtAux;
            mTamanho--;
            mPtAux->mPtProx = NULL;
            return valor;
        }
    }
    mPtIni = NULL;
    return Dado();
}

Dado Lista::RemoverNaPos(Dado valor){
    if (Vazia()){
        cerr <<"Erro: Não há elementos na lista!";
    }
    else{
        Noh* mPtAux = mPtIni;
        Dado valor = mPtAux->mDado;
        while ((mPtAux != NULL) and (mPtAux->mDado != valor)){
            mPtAux = mPtAux->mPtProx;
        
        if (mPtAux != NULL){
        Noh* mPtAnt = mPtAux;
            if (mPtAux == mPtIni){
                RemoverNoIni();
            }
            else if (mPtAux == mPtFim){
                RemoverNoFim();
            }
            else{
                mPtAnt->mPtProx = mPtAux->mPtProx;
            }
            mTamanho--;
            mPtAux->mPtProx = NULL;
            delete mPtAux;
            return valor;
        }
    }
    }
    return Dado();
}

int Lista::Busca(Dado valor){
    Noh* mPtAux = mPtIni;
    int contador = 0;
    while (mPtAux != NULL){
        if (mPtAux->mDado == valor){
            return contador;
        }
        mPtAux = mPtAux->mPtProx;
        contador++;
    }
    // mPtAux->mDado != valor;
    return -1;
}

void Lista::Imprimir(){
    Noh* mPtAux = mPtIni;
    while (mPtAux != NULL) {
        cout << mPtAux->mDado <<' ';
        mPtAux = mPtAux->mPtProx;
    }
    cout << endl;
}
bool Lista::Vazia() {
    if (mTamanho == 0){
        return true;
    }
    else{
        return false;
    }
}

void Lista::LimparTudo() {
    Noh* iter = mPtIni;
    Noh* mPtProx = NULL;
    while (iter != NULL){
        mPtProx = iter->mPtProx;
        delete iter;
        iter = mPtProx;
    }
    mPtIni = NULL;
    mPtFim = NULL;
    mTamanho = 0;
}

int main(){
    Lista lista;
    char comando;
    int valor;
    do{
        cin >> comando;
        switch (comando){
            case 'i':
                cin >> valor;
                lista.InserirNoIni(valor);
                break;
            case 'e':
                cin >> valor;
                lista.InserirNoFim(valor);
                break;
            case 'r':
                lista.RemoverNoIni();
                break;
            case 'f':
                lista.RemoverNoFim();
                break;
            case 'p':
                cin >> valor;
                lista.RemoverNaPos(valor);
                break;
            case 'c':
                lista.Imprimir();
                break;
            case 'b':
                cin >> valor;
                cout << lista.Busca(valor) << endl;
                break;
            case 't':
                cout << lista.Tamanho();
                break;
            case 'l':
                lista.LimparTudo();
                break;
            default:
                cout << "Comando inválido!";
        }
    } while (comando != 's');
    return 0;
}
