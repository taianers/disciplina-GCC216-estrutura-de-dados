#include <iostream>
using namespace std;

typedef int Dado;

class Noh{
    friend class Pilha;
    public:
        Noh(Dado valor);
    private:
        Dado mDado;
        Noh* mPtProximo;
};

class Pilha{
    public:
        Pilha();
        ~Pilha();
        void Empilha(const Dado& valor);
        Dado Desempilha();
        bool Vazia();
        void LimparTudo();
        unsigned Tamanho() { return mTamanho; }
        void Imprimir();
    private:
        Noh* mTopo;
        unsigned mTamanho;
};

Noh::Noh(Dado valor){
    mDado = valor;
    mPtProximo = NULL;
}

Pilha::Pilha(){
    mTopo = NULL;
    mTamanho = 0;
}

Pilha::~Pilha(){
    while (not Vazia()){
        Desempilha();
    }
    mTamanho = 0;
}

void Pilha::Empilha(const Dado& valor){
    Noh* novo = new Noh(valor);
    if (Vazia()){
        mTopo = novo;
    }
    else{
        novo->mPtProximo = mTopo;
        mTopo = novo;
    }
    mTamanho++;
}

Dado Pilha::Desempilha(){
    if (Vazia()){
        cerr <<"Pilha vazia";
    }
    else{
        Noh* mPtAux = mTopo;
        mTopo = mTopo->mPtProximo;
        Dado valor = mPtAux->mDado;
        delete mPtAux;
        mTamanho--;
        return valor;
    }
    return Dado();
}

bool Pilha::Vazia(){
    if (mTopo == NULL){
        return true;
    }
    else{
        return false;
    }
}

void Pilha::LimparTudo(){
    if (Vazia()){
        cout <<"Pilha Vazia" << endl;
    }
    while (not Vazia()){
        Desempilha();
    }
}

void Pilha::Imprimir(){
    Noh* mAux = mTopo;
    cout << "Topo = ";
    while (mAux != NULL){
        cout << mAux->mDado << endl;
        mAux = mAux->mPtProximo;
    }
}

int main(){
    Pilha pilha;
    Dado valor;
    char comando;
    do{
      cin >> comando;
      switch (comando){
        case 'i':
            cin >> valor;
            pilha.Empilha(valor);
            break;
        case 'r':
            if (pilha.Vazia()) {
                cerr << "Não é possível remover elementos\n";
                }
                else {
                    cout << pilha.Desempilha() << endl;
                }
                break;
        case 'l': // limpar tudo
                pilha.LimparTudo();
                break;
        case 't': // escrever tamanho
                cout << pilha.Tamanho() << endl;
                break;
            case 'm': // imprime fila
                pilha.Imprimir();
                break;
            case 'f': // finalizar
                // vai verificar adiante
                break;
            default:
                cerr << "comando inválido\n";
        }
    } while (comando != 'f'); // finalizar execução
    while (not pilha.Vazia()) {
        cout << pilha.Desempilha() << ' ';
    }
    cout << endl;
    return 0;
}
