#include <iostream>
#include <vector>

using namespace std;

/**
 * Vers�o da classe generica Grafo usando a classe vector
 */

template<class N>
class NoRepetido;

template<class N>
class NoInexistente;

template<class N>
class ArestaRepetida;

template<class N>
class ArestaInexistente;

template<class N, class A>
class Aresta;

template<class N, class A>
class No {
public:
    N info;
    vector<Aresta<N, A> > arestas;

    No(N inf) {
        info = inf;
    }
};

template<class N, class A>
class Aresta {
public:
    A valor;
    No<N, A> *destino;

    Aresta(No<N, A> *dest, A val) {
        valor = val;
        destino = dest;
    }
};

template<class N, class A>
class Grafo {
    vector<No<N, A> *> nos;
public:
    Grafo();

    ~Grafo();

    Grafo &inserirNo(const N &dados);

    Grafo &inserirAresta(const N &inicio, const N &fim, const A &val);

    Grafo &eliminarAresta(const N &inicio, const N &fim);

    A &valorAresta(const N &inicio, const N &fim);

    int numArestas(void) const;

    int numNos(void) const;

    void imprimir(std::ostream &os) const;
};

template<class N, class A>
Grafo<N, A>::Grafo() {};

template<class N, class A>
Grafo<N, A>::~Grafo() {

    for (size_t i = 0; i < nos.size(); i++) {
        delete (nos.at(i));
    }

    nos.clear();

};

template<class N, class A>
int Grafo<N, A>::numArestas(void) const {

    int arestas = 0;
    for (size_t i = 0; i < nos.size(); i++) {
        arestas = arestas + nos.at(i)->arestas.size();
    }
    return arestas;
};

template<class N, class A>
int Grafo<N, A>::numNos(void) const {

    return nos.size();

};

template<class N, class A>
Grafo<N, A> &Grafo<N, A>::inserirNo(const N &dados) {

    for (size_t i = 0; i < nos.size(); i++) {
        if (nos.at(i)->info == dados)
            throw NoRepetido<N>(dados);
    }

    No<N, A> *temp_no = new No<N, A>(dados);
    nos.push_back(temp_no);
    return *this;
};

template<class N, class A>
Grafo<N, A> &Grafo<N, A>::inserirAresta(const N &inicio, const N &fim, const A &val) {

    No<N, A> *start = nullptr, *end = nullptr;

    for (size_t i = 0; i < nos.size(); i++) {
        if (nos.at(i)->info == inicio)
            start = nos.at(i);
        if (nos.at(i)->info == fim)
            end = nos.at(i);
    }

    if (start == nullptr)
        throw NoInexistente<N>(inicio);

    if (end == nullptr)
        throw NoInexistente<N>(fim);

    for (size_t i = 0; i < start->arestas.size(); i++) {
        if(start->arestas.at(i).destino == end)
            throw ArestaRepetida <N> (inicio, fim);
    }

    start->arestas.emplace_back(end, val);
    return *this;
}

template<class N, class A>
A &Grafo<N, A>::valorAresta(const N &inicio, const N &fim) {

    No<N,A> *start = nullptr, *end = nullptr;

    for (size_t i = 0; i < nos.size(); i++) {
        if (nos.at(i)->info == inicio)
            start = nos.at(i);
        if (nos.at(i)->info == fim)
            end = nos.at(i);
    }

    if (start == nullptr)
        throw NoInexistente<N>(inicio);

    if (end == nullptr)
        throw NoInexistente<N>(fim);

    for (size_t i = 0; i < start->arestas.size(); i++) {
        if ( start->arestas.at(i).destino == end)
            return start->arestas.at(i).valor;
    }

    throw ArestaInexistente<N>(inicio, fim);

};

template<class N, class A>
Grafo<N, A> &Grafo<N, A>::eliminarAresta(const N &inicio, const N &fim) {

    No<N, A> *start = nullptr, *end = nullptr;

    for (size_t i = 0; i < nos.size(); i++) {
        if (nos.at(i)->info == inicio)
            start = nos.at(i);
        if(nos.at(i)->info == fim)
            end = nos.at(i);
    }

    if (start == nullptr)
        throw NoInexistente<N>(inicio);

/*
    if (end == nullptr)
        throw NoInexistente<N>(fim);
*/

    for (size_t i = 0; i < start->arestas.size(); i++) {
        if ( start->arestas.at(i).destino == end) {
            start->arestas.erase(start->arestas.begin() + i);
            return *this;
        }
    }

    throw ArestaInexistente<N>(inicio, fim);

}

template<class N, class A>
void Grafo<N, A>::imprimir(std::ostream &os) const {

    for (size_t i = 0; i < nos.size(); i++) {
        os << "( " << nos.at(i)->info;

        for(size_t t = 0; t < nos.at(i)->arestas.size(); t++) {
            os << "[ " << nos.at(i)->arestas.at(t).destino->info << " " << nos.at(i)->arestas.at(t).valor << "] ";
        }

        os << ") ";
    }

}

template<class N, class A>
std::ostream &operator<<(std::ostream &out, const Grafo<N, A> &g);

// excecao  NoRepetido
template<class N>
class NoRepetido {
public:
    N info;

    NoRepetido(N inf) { info = inf; }
};

template<class N>
std::ostream &operator<<(std::ostream &out, const NoRepetido<N> &no) {
    out << "No repetido: " << no.info;
    return out;
}

template <class N, class A>
std::ostream &operator<<(std::ostream &out, const Grafo<N, A> &grafo) {
    grafo.imprimir(out);
    return out;
};

// excecao NoInexistente
template<class N>
class NoInexistente {
public:
    N info;

    NoInexistente(N inf) {
        info = inf;
    }
};

// excecao ArestaRepetida
template<class N>
class ArestaRepetida {
public:
    N start;
    N destination;

    ArestaRepetida(N startinfo, N destinationinfo) : start(startinfo), destination(destinationinfo) {}
};

// excecao ArestaInexistente
template< class N >
class ArestaInexistente {
public:
    N start;
    N destination;

    ArestaInexistente (N startinfo, N destinationinfo) : start(startinfo), destination(destinationinfo) {}
};

template<class N>
std::ostream &operator<<(std::ostream &out, const NoInexistente<N> &ni) {
    out << "No inexistente: " << ni.info;
    return out;
}

template <class N>
std::ostream &operator<< (std::ostream &out, const ArestaRepetida<N> &a) {
    out << "Aresta repetida: " << a.start << " , " << a.destination;
    return out;
}

template <class N>
std::ostream &operator<<(std::ostream &out, const ArestaInexistente<N> &a) {
    out << "Aresta inexistente: " <<  a.start << " , " << a.destination;
    return out;
}

