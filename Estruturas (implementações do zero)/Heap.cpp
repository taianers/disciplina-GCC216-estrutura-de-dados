#include <iostream>
using namespace std;

typedef int Dado;

class Heap{
    public:
        Heap(int capacidade);
        ~Heap();
        void Inserir(const Dado& valor);
        Dado RemoverRaiz();
        void CorrigeDes(int pos);
        void CorrigeSub(int pos);
        void Heapify();
        void Imprimir();
        bool Vazia();
        void LimparTudo();
        unsigned Tamanho() { return mTamanho; }
    private:
        Dado* mHeapVet;
        int mPai;
        int mFilhoE;
        int mFilhoD;
        int mTamanho;
        int mCapacidade;
};

Heap::Heap(int capacidade){
    mCapacidade = capacidade;
    mHeapVet = new Dado[mCapacidade];
    mTamanho = 0;
    mHeapVet[0] = -1;
}

Heap::~Heap(){
    delete[] mHeapVet;
}

void Heap::Inserir(const Dado& valor){
    if (mTamanho == mCapacidade){
        cerr <<"Heap Cheio!";
    }
    else{
        mHeapVet[mTamanho + 1] = valor;
        CorrigeSub(mTamanho + 1);
        mTamanho++;
    }
}

Dado Heap::RemoverRaiz(){
    int mAux = mHeapVet[0];
    swap(mHeapVet[0], mHeapVet[mTamanho]);
    mTamanho--;
    CorrigeDes(0);
    return mAux;
}

void Heap::CorrigeDes(int pos){
    mFilhoE = (2*pos) + 1;
    mFilhoD = (2*pos) + 2;
    int maior = pos;
    if ((mFilhoE <= mTamanho) and (mHeapVet[mFilhoE] > mHeapVet[pos])){
        maior = mFilhoE;
    }
    if ((mFilhoD <= mTamanho) and (mHeapVet[mFilhoD] > mHeapVet[maior])){
        maior = mFilhoD;
    }
    if (maior != pos){
        swap(mHeapVet[pos], mHeapVet[maior]);
        CorrigeDes(maior);
    }
}

void Heap::CorrigeSub(int pos){
    mPai = (pos - 1)/2;
    if ((mPai >= mHeapVet[0]) and (mHeapVet[pos] > mHeapVet[mPai])){
        swap(mHeapVet[pos], mHeapVet[mPai]);
        CorrigeSub(mPai);
    }
}

void Heap::Heapify(){
    for (int i = ((mTamanho - 1)/2); i > 0; i--){
        CorrigeDes(i);
    }
}

bool Heap::Vazia(){
    if (mTamanho == 0){
        return true;
    }
    else{
        return false;
    }
}

void Heap::Imprimir(){
    for (int i = 0; i < mCapacidade; i++){
        cout << mHeapVet[i] << ' ';
    }
}

void Heap::LimparTudo(){
    mTamanho = 0;
}

int main (){
    
    int tamanhoVet;
    cin >> tamanhoVet;
    Heap heap(tamanhoVet);
    Dado valor;
    char comando;
    do {
        cin >> comando;
        switch (comando) {
            case 'i': // inserir
                cin >> valor;
                heap.Inserir(valor);
                break;
            case 'r': // remover
                if (heap.Vazia()){
                    cerr <<"Impossível remoção, heap vazio!";
                }
                else {
                    cout << heap.RemoverRaiz() << endl;
                }
                break;
            case 'l': // limpar tudo
                heap.LimparTudo();
                break;
            case 't': // escrever tamanho
                cout << heap.Tamanho() << endl;
                break;
            case 'm': // imprime heap
                if (heap.Vazia()){
                    cerr <<"Heap vazio!";
                }
                else{
                    heap.Imprimir();
                }
                break;
            case 'f': // finalizar
                // vai verificar adiante
                break;
            default:
            cerr << "comando inválido\n";
        }
    } while (comando != 'f'); // finalizar execução
    while (not heap.Vazia()) {
        cout << heap.RemoverRaiz() << ' ';
    }
    cout << endl;
    return 0;
}
