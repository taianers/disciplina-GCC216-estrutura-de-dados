#include <iostream>
using namespace std;

typedef int Dado;

class Pilha{
    public:
        Pilha(int capacidade);
        ~Pilha();
        void Empilha(const Dado& valor);
        Dado Desempilha();
        Dado DesempilhaPos(unsigned int pos);
        bool Vazia();
        void LimparTudo();
        void Imprimir();
        unsigned Tamanho() { return mTamanho; }
    private:
        int mPtTopo;
        Dado* mVetor;
        unsigned mTamanho;
        unsigned mCapacidade;
};

Pilha::Pilha(int capacidade){
    mCapacidade = capacidade;
    mPtTopo = -1;
    mVetor = new Dado[mCapacidade];
    mTamanho = 0;
}

Pilha::~Pilha(){
    delete[] mVetor;
}

void Pilha::Empilha(const Dado& valor){
    if (Vazia()){
        mVetor[0] = valor;
        mPtTopo = -1;
    }
    else if (mCapacidade == mTamanho){
        cerr <<"Pilha Cheia";
    }
    else{
        mVetor[mTamanho] = valor;
    }
    
    mTamanho++;
}

Dado Pilha::Desempilha(){
    Dado valor = mVetor[mPtTopo];
    mPtTopo -= 1;
    mTamanho--;
    return valor;
}

bool Pilha::Vazia(){
    if (mTamanho == 0){
        return true;
    }
    else{
        return false;
    }
}

void Pilha::LimparTudo(){
    mTamanho = 0;
}

void Pilha::Imprimir(){
    for (unsigned int i = 0; i < mCapacidade; i++){
        cout << mVetor[i] << endl;
    }
}

int main(){
    unsigned int tamanhoVet;
    cin >> tamanhoVet;
    Pilha pilha(tamanhoVet);
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
