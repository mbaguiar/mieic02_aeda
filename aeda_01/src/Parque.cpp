#include "Parque.h"
#include <iostream>
#include <vector>

using namespace std;

ParqueEstacionamento::ParqueEstacionamento(unsigned int lot, unsigned int nMaxCli) : lotacao(lot), numMaximoClientes(nMaxCli), vagas(lot) {
}

unsigned int ParqueEstacionamento::getNumLugares() const {

    return this->lotacao;
}

unsigned int ParqueEstacionamento::getNumMaximoClientes() const {

    return this->numMaximoClientes;
}

int ParqueEstacionamento::posicaoCliente(const string & nome) const {

    int index = -1;
    for(size_t i=0; i < clientes.size(); i++) {
        if(clientes.at(i).nome == nome)
            index = i;
    }
    return index;
}

bool ParqueEstacionamento::adicionaCliente(const string & nome) {

    if(clientes.size() == numMaximoClientes)
        return false;

    InfoCartao cliente;
    cliente.nome = nome;
    cliente.presente = false;
    clientes.push_back(cliente);
    return true;

}

bool ParqueEstacionamento::entrar(const string & nome) {

    if(this->vagas == 0)
        return false;

    int index = posicaoCliente(nome);
    if(index == -1)
        return false;

    if(this->clientes.at(index).presente)
         return false;
    
    this->clientes.at(index).presente = true;
    this->vagas--;
    return true;
}

bool ParqueEstacionamento::retiraCliente(const string & nome) {

    int index = posicaoCliente(nome);
    if(index == -1)
        return false;

    if(!clientes.at(index).presente) {
        clientes.erase(clientes.begin(), clientes.end());
        return true;
    }
}

bool ParqueEstacionamento::sair(const string & nome) {

    int index = posicaoCliente(nome);
    if(index == -1)
        return false;

    if(!clientes.at(index).presente)
        return false;
    else {
        clientes.at(index).presente = false;
        vagas++;
        return true;
    }
}

unsigned int ParqueEstacionamento::getNumLugaresOcupados() const {

    return lotacao - vagas;
}

unsigned int ParqueEstacionamento::getNumClientesAtuais() const {

    return clientes.size();
}

const ParqueEstacionamento & ParqueEstacionamento::operator += (const ParqueEstacionamento & p2) {

    for(size_t i = 0; i < p2.clientes.size(); i++){
        if(this->clientes.size() >= this->numMaximoClientes)
            break;
        this->clientes.push_back(p2.clientes.at(i));
    }

    return *this;
}