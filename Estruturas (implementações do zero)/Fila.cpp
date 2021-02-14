#include <iostream>
using namespace std;

typedef int Dado;

class Noh{
    friend class Fila;
    public:
        Noh(Dado valor);
    private:
        Dado mDado;
        Noh* mPtProximo;
};

class Fila{
    public:
        Fila();
        ~Fila();
        void Enfilera(Dado valor); //inserir na fila
        Dado Desenfilera(); //remover da fila
        void LimparTudo(); //limpa toda fila
        unsigned Tamanho() { return mTamanho; }
        void Imprimir();
        bool Vazia(); //verifica se a fila está vazia
    private:
        Noh* mPtPrimeiro;
        Noh* mPtUltimo;
        unsigned mTamanho;
};

Noh::Noh(Dado valor){
    mDado = valor;
    mPtProximo = NULL;
}

Fila::Fila(){
    mPtPrimeiro = NULL;
    mPtUltimo = NULL;
    mTamanho = 0;
}

Fila::~Fila(){
    Noh* iter = mPtPrimeiro;
    Noh* proximo = NULL;
    while (iter != NULL) {
        proximo = iter->mPtProximo;
        delete iter;
        iter = proximo;
    }
    mTamanho = 0;
}

void Fila::Enfilera(Dado valor){
    Noh* novo = new Noh(valor);
    if (Vazia()){
        mPtPrimeiro = novo;
        mPtUltimo = novo;
    }
    else{
        mPtUltimo->mPtProximo = novo;
        mPtUltimo = novo;
    }
    mTamanho++;
}

Dado Fila::Desenfilera(){
    if (Vazia()){
        cerr << "Não é possível remover elementos\n";
    }
    else{
        Noh* mPtAux = mPtPrimeiro;
        mPtPrimeiro = mPtPrimeiro->mPtProximo;
        Dado valor = mPtAux->mDado;
        delete mPtAux;
        mTamanho--;
        return valor;
    }
    /*if (mTamanho == 0){
        mPtPrimeiro = NULL;
        mPtUltimo = NULL;
    }*/
    return Dado();
}

void Fila::LimparTudo(){
    if (Vazia()){
        cout <<"Fila Vazia" << endl;
    }
    while (not Vazia()){
        Desenfilera();
    }
}

bool Fila::Vazia(){
    if (mTamanho == 0){
        return true;
    }
    else{
        return false;
    }
}

void Fila::Imprimir(){
    Noh* mPtAux = mPtPrimeiro;
    while (mPtAux != NULL){
        cout << mPtAux->mDado <<' ';
        mPtAux = mPtAux->mPtProximo;
    }
}

int main() {
    Fila fila;
    Dado valor;
    char comando;
    do {
        cin >> comando;
        switch (comando) {
            case 'i': // inserir
                cin >> valor;
                fila.Enfilera(valor);
                break;
            case 'r': // remover
                if (fila.Vazia()) {
                    cerr << "Não é possível remover elementos\n";
                }
                else {
                    cout << fila.Desenfilera() << endl;
                }
                break;
            case 'l': // limpar tudo
                fila.LimparTudo();
                break;
            case 't' and 'i': // escrever tamanho
                cout << fila.Tamanho() << endl;
                break;
            case 'm': // imprime fila
                fila.Imprimir();
                break;
            case 'f': // finalizar
                // vai verificar adiante
                break;
            default:
            cerr << "comando inválido\n";
        }
    } while (comando != 'f'); // finalizar execução
    while (not fila.Vazia()) {
        cout << fila.Desenfilera() << ' ';
    }
    cout << endl;
    return 0;
}
