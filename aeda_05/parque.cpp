#include "parque.h"
#include "insertionSort.h"
#include "sequentialSearch.h"
#include <vector>
#include <algorithm>

using namespace std;

bool CompNames(const InfoCartao &c1, const InfoCartao &c2);


ParqueEstacionamento::ParqueEstacionamento(unsigned int lot, unsigned int nMaxCli):
	lotacao(lot), numMaximoClientes(nMaxCli) {
    numClientes = 0;
    vagas=lot; 
}

ParqueEstacionamento::~ParqueEstacionamento() {}

vector<InfoCartao> ParqueEstacionamento::getClientes() const { return clientes; }


bool ParqueEstacionamento::adicionaCliente(const string & nome)
{
 	if ( numClientes == numMaximoClientes ) return false;
	if ( posicaoCliente(nome) != -1 ) return false;
	InfoCartao info;
	info.nome = nome;
    info.presente = false;
    info.frequencia = 0;  // a fazer
	clientes.push_back(info);
	numClientes++;
	return true;
}
 
bool ParqueEstacionamento::retiraCliente(const string & nome)
{
	for (vector<InfoCartao>::iterator it = clientes.begin(); it != clientes.end(); it++)
		if ( it->nome == nome ) {
			if ( it->presente == false ) {
				clientes.erase(it);
				numClientes--;
				return true;
			}
			else return false;
		}
	return false;
}
  
unsigned int ParqueEstacionamento::getNumLugares() const
{
	return lotacao;
}
                   
unsigned int ParqueEstacionamento::getNumLugaresOcupados() const
{
	return lotacao-vagas;
}

bool ParqueEstacionamento::entrar(const string & nome)
{
	if ( vagas == 0 ) return false;
	int pos = posicaoCliente(nome);
	if ( pos == -1 ) return false;
	if ( clientes[pos].presente == true ) return false;
	clientes[pos].presente = true;
	clientes.at(pos).frequencia++;
	vagas--;
	return true;
}

bool ParqueEstacionamento::sair(const string & nome)
{
	int pos = posicaoCliente(nome);
	if ( pos == -1 ) return false;
	if ( clientes[pos].presente == false ) return false;
	clientes[pos].presente = false;
	vagas++;
	return true;
}

// a alterar
int ParqueEstacionamento::posicaoCliente(const string & nome) const {

	InfoCartao cartao = InfoCartao();
	cartao.nome = nome;

	return sequentialSearch(clientes, cartao);
}

int ParqueEstacionamento::getFrequencia(const string &nome) const {

	int pos = posicaoCliente(nome);
	if(pos == -1)
		throw ClienteNaoExistente(nome);
	else return clientes.at(pos).frequencia;
}

void ParqueEstacionamento::ordenaClientesPorFrequencia() {

	insertionSort(clientes);

}

vector<string> ParqueEstacionamento::clientesGamaUso(int n1, int n2) {

	vector<string> names;
	insertionSort(clientes);
	for(size_t i = 0; i < clientes.size(); i++) {
		int freq = clientes.at(i).frequencia;
		if (freq >= n1 && freq <= n2)
			names.push_back(clientes.at(i).nome);
	}

	return names;
}

void ParqueEstacionamento::ordenaClientesPorNome() {

	sort(clientes.begin(), clientes.end(), CompNames);

}

InfoCartao ParqueEstacionamento::getClienteAtPos(vector<InfoCartao>::size_type p) const {

	if( p >= clientes.size()) {
		throw PosicaoNaoExistente(p);
	}
	else {
		return clientes.at(p);
	}
}


bool InfoCartao::operator==(const InfoCartao &ic1) const {

	return (nome == ic1.nome);

}

bool InfoCartao::operator<(const InfoCartao &ic1) const {

	if(frequencia == ic1.frequencia)
		return (nome < ic1.nome);
	else return (frequencia > ic1.frequencia);

}

bool CompNames(const InfoCartao &c1, const InfoCartao &c2) {

	return (c1.nome < c2.nome);
}

ostream& operator<<(ostream &os, const ParqueEstacionamento &pe) {

	for(size_t i = 0; i < pe.clientes.size(); i++) {

		os << "Nome: " << pe.clientes.at(i).nome << " ";

		if (pe.clientes.at(i).presente)
			os << "Presente no parque ";

		os << "Frequencia: " << pe.clientes.at(i).frequencia << endl;
	}

	return os;

}
