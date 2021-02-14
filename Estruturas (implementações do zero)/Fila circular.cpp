#include <iostream>
using namespace std;

typedef int Dado;

class Fila{
    public:
        Fila(int capacidade);
        ~Fila();
        void Enfilera(const Dado& valor); //inserir na fila
        Dado Desenfilera(); //remover da fila
        void LimparTudo(); //limpa toda fila
        int Tamanho() { return mTamanho; }
        void Imprimir();
        bool Vazia(); //verifica se a fila está vazia
    private:
        Dado* mVetor;
        int mIni;
        int mFim;
        int mTamanho;
        int mCapacidade;
};

Fila::Fila(int capacidade){
    mIni = -1;
    mFim = -1;
    mTamanho = 0;
    mCapacidade = capacidade;
    mVetor = new Dado[mCapacidade];
}

Fila::~Fila(){
    delete[] mVetor;
}

void Fila::Enfilera(const Dado& valor){
    if (mCapacidade == mTamanho){
        cerr <<"Fila Cheia";
    }
    else if (Vazia()){
        mIni++;
    }
    mFim = (mFim + 1) % mCapacidade;
    mVetor[mFim] = valor;
    mTamanho++;
}

Dado Fila::Desenfilera(){
    int mAux = mVetor[mIni];
    mVetor[mIni] = -1;
    if (mFim == mIni){
        mFim = -1;
        mIni = -1;
    }
    else{
        mIni = (mIni + 1) % mCapacidade;
    }
    mTamanho--;
    return mAux;
}

void Fila::LimparTudo(){
    mTamanho = 0;
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
    for (int i = 0; i < mCapacidade; i++){
        cout << mVetor[i] <<' ';
    }
}

int main() {
    int tamanhoVet;
    cin >> tamanhoVet;
    Fila fila(tamanhoVet);
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
                    cerr << "Não é possível remover elementos, fila vazia!\n";
                }
                else {
                    cout << fila.Desenfilera() << endl;
                }
                break;
            case 'l': // limpar tudo
                fila.LimparTudo();
                break;
            case 't': // escrever tamanho
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
