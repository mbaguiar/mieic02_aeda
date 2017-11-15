#include <queue>
#include <cstdlib>
#include "Balcao.h"
#include "exceptions.h"

using namespace std;


Cliente::Cliente() {
	numPresentes = rand() % 5 + 1;
}


int Cliente::getNumPresentes() const {

	return numPresentes;
}


Balcao::Balcao(int te): tempo_embrulho(te) {

	tempo_atual = 0;
	prox_chegada = rand() % 20 + 1;
	prox_saida = 0;
	clientes_atendidos = 0;
}


void Balcao:: proximoEvento()
{
	if (clientes.empty()) {

		tempo_atual = prox_chegada;
		chegada();
		return;
	}

	if (prox_chegada <= prox_saida) {

		tempo_atual = prox_chegada;
		chegada();
		return;

	}else {

		tempo_atual = prox_saida;
		saida();
		return;

	}
}


void Balcao::chegada()
{
	Cliente newclient;

	if (clientes.empty()) {

		prox_saida = tempo_atual + newclient.getNumPresentes() * tempo_embrulho;

	}

	prox_chegada = rand() % 20 + 1;

	clientes.push(newclient);

	cout << "tempo= " << tempo_atual << endl;
	cout << "chegou novo cliente com " << newclient.getNumPresentes() << " presentes.\n";
}   


void Balcao::saida()
{
	Cliente client = getProxCliente();

	clientes.pop();

	prox_saida = clientes.front().getNumPresentes() * tempo_embrulho + tempo_atual;

	cout << "tempo= " << tempo_atual << endl;
	cout << "saiu novo cliente com " << client.getNumPresentes() << " presentes.\n";

	clientes_atendidos++;
}


int Balcao::getTempoAtual() const { return tempo_atual; }


int Balcao::getProxChegada() const { return prox_chegada; }


ostream & operator << (ostream & out, const Balcao & b1)
{
	out << b1.getClientesAtendidos() << " " << b1.clientes.size() << endl;
     return out;
}


int Balcao::getTempoEmbrulho() const {
	return tempo_embrulho;
}


int Balcao::getProxSaida() const {
	return prox_saida;
}


int Balcao::getClientesAtendidos() const {
	return clientes_atendidos;
}


Cliente & Balcao::getProxCliente() {

	if (clientes.empty())
		throw FilaVazia();

	return clientes.front();
}

      
