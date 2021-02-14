/* avl - Árvore Binária de Busca com Balanceamento AVL
 *
 * -> tratamento de exceção
 * -> usa pokemon na forma id/valor
 * -> uso de métodos recursivos
 * -> sem duplo encadeamento
 * -> invés de transplanta, usa removeMenor
 */

#include <iostream>
#include <stdexcept>
using namespace std;

struct pokemon {
    unsigned id;
    string nome;
    string tipo;
    int nivel;
};

ostream& operator<<(ostream& saida, const pokemon& e) {
    saida << "(" << e.id << "," << e.nome << "," << e.tipo << "," << e.nivel << ")";
    return saida;
}

istream& operator>>(istream& entrada, pokemon& e) {
    entrada >> e.id >> e.nome >> e.tipo >> e.nivel;
    return entrada;
}

class noh {
    friend class avl;
    private:
        pokemon elemento;
        noh* esq;
        noh* dir;
        unsigned altura;
    public:
        noh(const pokemon& umPokemon):
            elemento(umPokemon),  esq(NULL), dir(NULL), altura(1) { }
        ~noh() { }
        int informaAltura();
        void atualizaAltura();
        int fatorBalanceamento();
};

int noh::informaAltura(){
    noh* umNoh = this;
    if (umNoh == NULL){
        return 0;
    }
    else{
        return umNoh->altura;
    }
}

void noh::atualizaAltura(){
    unsigned altEsq = this->esq->informaAltura();
    unsigned altDir = this->dir->informaAltura();
    altura = 1 + max(altEsq, altDir);
}

int noh::fatorBalanceamento() {
    unsigned altEsq = this->esq->informaAltura();
    unsigned altDir = this->dir->informaAltura();
    int fator = altEsq - altDir;
    return fator;
}

typedef unsigned tipoChave;

class avl {
    friend ostream& operator<<(ostream& output, avl& arvore);
    private:
        noh* raiz;
        // função auxiliar para inserção usando método recursivo
        noh* insereAux(noh* umNoh, const pokemon& umPokemon);
        // função auxiliar do destrutor, usa percorrimento pós-ordem
        void destruirRecursivamente(noh* umNoh);
        // métodos para manutenção do balanceamento
        noh* rotacaoEsquerda(noh* umNoh);
        noh* rotacaoDireita(noh* umNoh);
        noh* arrumaBalanceamento(noh* umNoh);
        // funções auxiliares para remoção
        noh* encontraMenor(noh* raizSub);
        noh* removeMenor(noh* raizSub);
        // função auxiliar para remoção usando método recursivo
        noh* removeAux(noh* umNoh, tipoChave id);
        // busca, método iterativo
        int levantamentoAux(noh* umNoh, string& umTipo, int nivel);
        noh* buscaAux(tipoChave id);
        void imprimirDir(const std::string& prefixo, const noh* meuNoh);
        void imprimirEsq(const std::string& prefixo, const noh* meuNoh, bool temIrmao);
    public:
        avl() { raiz = NULL; }
        ~avl();
        // inserção e remoção são recursivos
        void insere(const pokemon& umPokemon);
        void remove(tipoChave id);
        // efetua levantamento de quantos pokemons existem de um dado tipo e nível
        int levantamento(string umTipo, int nivel);
        // busca retorna uma cópia do objeto armazenado
        pokemon busca(tipoChave id);
        void imprimir();
};

// destrutor
avl::~avl() {
    destruirRecursivamente(raiz);
}

// destrutor é recursivo, fazendo percorrimento pós-ordem
void avl::destruirRecursivamente(noh* umNoh) {
    if (umNoh != NULL){
        destruirRecursivamente(umNoh->esq);
        destruirRecursivamente(umNoh->dir);
        delete umNoh;
    }
}

void avl::insere(const pokemon& umPokemon) {
    raiz = insereAux(raiz, umPokemon);
}

// inserção recursiva, devolve nó para atribuição de pai ou raiz
noh* avl::insereAux(noh* umNoh, const pokemon& umPokemon) {
    if (umNoh == NULL){
        noh* novo = new noh(umPokemon);
        return novo;
    }
    else{
        if (umNoh->elemento.id > umPokemon.id){
            umNoh->esq = insereAux(umNoh->esq,umPokemon);
        }
        else if (umNoh->elemento.id < umPokemon.id){
            umNoh->dir = insereAux(umNoh->dir,umPokemon);
        }
        else{
            throw runtime_error("Erro ao inserir: o id já existe!");
        }
    }
    return arrumaBalanceamento(umNoh);
}

// rotação à esquerda na subárvore com raiz em umNoh
// retorna o novo pai da subárvore
noh* avl::rotacaoEsquerda(noh* umNoh) {
    noh* aux = umNoh->dir;
    umNoh->dir = aux->esq;
    aux->esq = umNoh;
    umNoh->atualizaAltura();
    aux->atualizaAltura();
    return aux;
}

// rotação à direita na subárvore com raiz em umNoh
// retorna o novo pai da subárvore
noh* avl::rotacaoDireita(noh* umNoh) {
    noh* aux = umNoh->esq;
    umNoh->esq = aux->dir;
    aux->dir = umNoh;
    umNoh->atualizaAltura();
    aux->atualizaAltura();
    return aux;
}

// checa e arruma, se necessário, o balanceamento em umNoh,
// fazendo as rotações e ajustes necessários
noh* avl::arrumaBalanceamento(noh* umNoh) {
    if (umNoh == NULL){
        return umNoh;
    }
    umNoh->atualizaAltura();
    int bal = umNoh->fatorBalanceamento();
    if ((bal >= -1) and (bal <= 1)){
        return umNoh;
    }
    if ((bal > 1) and (umNoh->esq->fatorBalanceamento() >= 0)){
        return rotacaoDireita(umNoh);
    }
    if ((bal > 1) and (umNoh->esq->fatorBalanceamento() < 0)){
        umNoh->esq = rotacaoEsquerda(umNoh->esq);
        return rotacaoDireita(umNoh);
    }
    if ((bal < -1) and (umNoh->dir->fatorBalanceamento() <= 0)){
        return rotacaoEsquerda(umNoh);
    }
    if ((bal < -1) and (umNoh->dir->fatorBalanceamento() > 0)){
        umNoh->dir = rotacaoDireita(umNoh->dir);
        return rotacaoEsquerda(umNoh);
    }
    return umNoh;
}

// nó mínimo (sucessor) de subárvore com raiz em raizSub (folha mais à esquerda)
noh* avl::encontraMenor(noh* raizSub) {
    while (raizSub->esq != NULL){
        raizSub = raizSub->esq;
    }
    return raizSub;
}

// procedimento auxiliar para remover o sucessor substituíndo-o pelo
// seu filho à direita
noh* avl::removeMenor(noh* raizSub) {
    if (raizSub->esq == NULL){
        return raizSub->dir;
    }
    else{
        raizSub->esq = removeMenor(raizSub->esq);
        return arrumaBalanceamento(raizSub);
    }
}

// remoção recursiva
void avl::remove(tipoChave id) {
    raiz = removeAux(raiz, id);
}

noh* avl::removeAux(noh* umNoh, tipoChave id) {
    if (umNoh == NULL) {
        throw runtime_error("Erro ao remover: id não encontrado!");
    }
    noh* novaRaizSub = umNoh;
    if (umNoh->elemento.id > id){ 
        umNoh->esq = removeAux(umNoh->esq, id);
    }
    else if (umNoh->elemento.id < id){ 
        umNoh->dir = removeAux(umNoh->dir, id);
    }
    else{
        if (umNoh->dir == NULL){
            novaRaizSub = umNoh->esq;
        }
        else if (umNoh->esq == NULL){
            novaRaizSub = umNoh->dir;
        }
        else{ 
            novaRaizSub = encontraMenor(umNoh->dir);
            novaRaizSub->dir = removeMenor(umNoh->dir);
            novaRaizSub->esq = umNoh->esq;
        }
        delete umNoh;
    }
    return arrumaBalanceamento(novaRaizSub);
}

int avl::levantamento(string umTipo, int nivel){
    return levantamentoAux(raiz, umTipo, nivel);
}

int avl::levantamentoAux(noh* umNoh, string& umTipo, int nivel){
    int contador = 0;
    if (umNoh != NULL){
        if ((umNoh->elemento.tipo == umTipo) and (umNoh->elemento.nivel == nivel)){
            contador++;
        }
        contador += levantamentoAux(umNoh->esq,umTipo, nivel);
        contador += levantamentoAux(umNoh->dir,umTipo, nivel);
    }
    return contador;
}

// método de busca auxiliar (retorna o nó), iterativo
noh* avl::buscaAux(tipoChave id) {
    noh* umNoh = raiz;
    while (umNoh != NULL){
        if (umNoh->elemento.id == id){
            return umNoh;
        }
        else if (umNoh->elemento.id > id){
            umNoh = umNoh->esq;
        }
        else{
            umNoh = umNoh->dir;
        }
    }
    return umNoh;
}

// busca elemento com uma dada chave na árvore e retorna o registro completo
pokemon avl::busca(tipoChave id) {
    noh* resultado = buscaAux(id);
    if (resultado != NULL)
        return resultado->elemento;
    else
        throw runtime_error("Erro na busca: elemento não encontrado!");
}

ostream& operator<<(ostream& output, avl& arvore) {
    arvore.imprimir();
    return output;
}

// imprime formatado seguindo o padrao tree as subarvores direitas de uma avl
void avl::imprimirDir(const std::string& prefixo, const noh* meuNoh)
{
    if( meuNoh != nullptr )
    {
        std::cout << prefixo
                  << "└d─"
                  << "(" << meuNoh->elemento.id << "," << meuNoh->elemento.nome << ")"
                  << std::endl;

        // Repassa o prefixo para manter o historico de como deve ser a formatacao e chama no filho direito e esquerdo
        imprimirEsq( prefixo + "    " , meuNoh->esq , meuNoh->dir==nullptr );
        imprimirDir( prefixo + "    " , meuNoh->dir );
    }
}

// imprime formatado seguindo o padrao tree as subarvores direitas de uma avl
void avl::imprimirEsq(const std::string& prefixo, const noh* meuNoh, bool temIrmao)
{
    if( meuNoh != nullptr )
    {
        std::cout << prefixo ;

        // A impressao da arvore esquerda depende da indicacao se existe o irmao a direita
        if (temIrmao)
            std::cout << "└e─" ;
        else
            std::cout << "├e─";

        std::cout << "(" << meuNoh->elemento.id << "," << meuNoh->elemento.nome << ")"
                  << std::endl;

        // Repassa o prefixo para manter o historico de como deve ser a formatacao e chama no filho direito e esquerdo
        imprimirEsq( prefixo + "│   " , meuNoh->esq, meuNoh->dir==nullptr );
        imprimirDir( prefixo + "│   " , meuNoh->dir );
    }
}

// imprime formatado seguindo o padrao tree uma avl
void avl::imprimir()
{
    if( this->raiz != nullptr )
    {
        std::cout << "(" << this->raiz->elemento.id << "," << this->raiz->elemento.nome << ")" << std::endl;
        // apos imprimir a raiz, chama os respectivos metodos de impressao nas subarvore esquerda e direita
        // a chamada para a impressao da subarvore esquerda depende da existencia da subarvore direita
        imprimirEsq( " " , this->raiz->esq, this->raiz->dir==nullptr );
        imprimirDir( " " , this->raiz->dir );
    } else
        std::cout << "*arvore vazia*" << std::endl;
}

int main() {
    avl arvore;
    tipoChave id;
    pokemon umPokemon;
    string tipo;
    int nivel;
    int quantidade;

    char operacao;

    do {
        try {
            cin >> operacao;
            switch (operacao) {
                case 'i': // Inserir recursivamente
                    // objeto recebe id, nome, tipo e nível
                    cin >> umPokemon;
                    arvore.insere(umPokemon);
                    break;
                case 'r': // Remover recursivamente
                    cin >> id;
                    arvore.remove(id);
                    break;
                case 'b': // Buscar
                    cin >> id; // ler o id
                    umPokemon = arvore.busca(id); // escrever dados do pokemon
                    cout << "Elemento buscado: " << umPokemon << endl;
                    break;
                case 'l': // Levantamento por tipo e nível
                    cin >> tipo >> nivel;
                    quantidade = arvore.levantamento(tipo, nivel);
                    cout << "Levantamento de pokemons tipo " << tipo
                         << " e nível " << nivel << ": " << quantidade << endl;
                    break;
                case 'e': // Escrever tudo (em ordem)
                    cout << arvore;
                    break;
                case 'f': // Finalizar execução
                    break;
                default:
                    cout << "Comando invalido!\n";
            }
        } catch (runtime_error& e) {
            cout << e.what() << endl;
        }
    } while (operacao != 'f');

    return 0;
}
