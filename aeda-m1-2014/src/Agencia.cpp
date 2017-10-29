/*
 * Agencia.cpp
 */

#include "Agencia.h"


//Conta
Conta::Conta(int nConta, float sd, int nTrans): numConta(nConta), saldo(sd), numTransacoes(nTrans), titular2(NULL)
{ }

int Conta::getNumConta() const
{ return numConta; }

float Conta::getSaldo() const
{ return saldo; }

int Conta::getNumTransacoes() const
{ return numTransacoes; }


void Conta::setTitular2(Cliente *cli2)
{ titular2=cli2; }

Cliente *Conta::getTitular2() const
{ return titular2; }

bool Conta::levantamento(float valor) {
	return false;
}

string Conta::getType() const{
	return "";
}


Normal::Normal(int nConta, float sd, int nTrans): Conta(nConta, sd, nTrans)
{}

DeOperacao::DeOperacao(int nConta, float tx, float sd, int nTrans): Conta(nConta, sd, nTrans), taxa(tx)
{}

bool Normal::levantamento(float valor) {

	if (valor <= saldo) {
		saldo = saldo - valor;
		numTransacoes++;
		return true;
	} else return false;
}

string Normal::getType() const {
	return "normal";
}

void Normal::addTax() {

	saldo = saldo - 1.5;

}

bool DeOperacao::levantamento(float valor) {

	if (valor <= saldo) {
		saldo = saldo - valor - taxa;
		numTransacoes++;
		return true;
	} else false;
}

string DeOperacao::getType() const {
	return "deoperacao";
}

void Conta::deposito(float valor) {

	numTransacoes++;
	saldo = saldo + valor;

}


//Cliente
Cliente::Cliente (string nm): nome(nm)
{}

string Cliente::getNome() const
{ return nome; }

vector<Conta *> Cliente::getContas() const
{ return contas; }

void Cliente::adicionaConta(Conta *c1)
{ contas.push_back(c1); }


//Agencia
Agencia::Agencia(string desig): designacao(desig)
{}

string Agencia::getDesignacao() const
{ return designacao; }

vector<Cliente *> Agencia::getClientes() const
{ return clientes; }

vector<Gerente> Agencia::getGerentes() const
{ return gerentes; }

void Agencia::adicionaCliente(Cliente *cli1)
{ clientes.push_back(cli1); }

Conta* Agencia::levantamento(string nomeCli, float valor) {

	for (size_t i = 0; i < clientes.size(); i++) {

		if(clientes.at(i)->getNome() == nomeCli) {

			for (size_t j = 0; j < clientes.at(i)->getContas().size(); j++) {

				Conta * conta = clientes.at(i)->getContas().at(j);
				if (conta->levantamento(valor))
					return conta;
			}
		}
	}

	Conta *c1 = new Conta(-1, 0, 0);
	return c1;
}

float Agencia::fimMes() const {

	float soma = 0;
	for (size_t i = 0; i < clientes.size(); i++) {
		for (size_t j = 0; j < clientes.at(i)->getContas().size(); j++) {
			Conta * conta = clientes.at(i)->getContas().at(j);
			if (conta->getType() == "normal") {
				conta->addTax();
			}

			soma = soma + conta->getSaldo();
		}
	}

	return soma;
}

bool Agencia::operator <(const Agencia& a1) {

	float soma1 = 0, soma2 = 0;

	for (size_t i = 0; i < clientes.size(); i++) {

		for (size_t j = 0; j < clientes.at(i)->getContas().size(); j++) {

			soma1 = soma1 + clientes.at(i)->getContas().at(j)->getSaldo();
		}
	}

	for (size_t i = 0; i < a1.getClientes().size(); i++) {

		for (size_t j = 0; j < a1.getClientes().at(i)->getContas().size(); j++) {

			soma2 = soma2 + a1.getClientes().at(i)->getContas().at(j)->getSaldo();
		}
	}

	soma1 = soma1 / (float) clientes.size();
	soma2 = soma2 / (float) a1.getClientes().size();

	return soma1 < soma2;

}

float Agencia::operator ()(string name) {

	float soma = 0;
	int index = -1;

	for (size_t i = 0; i < clientes.size(); i++) {
		if (clientes.at(i)->getNome() == name) {
			index = i;
		}
	}

	if (index != -1) {
		for (size_t i = 0; i < clientes.at(index)->getContas().size(); i++) {
			soma = soma + clientes.at(index)->getContas().at(i)->getSaldo();
		}
		return soma;
	} else return -1;

}

int Agencia::IDgerente = 0;

void Agencia::setGerenteID(int IDinicio) {

	IDgerente = IDinicio;

}

void Gerente::setID(int id) {

	ID = id;

}

void Agencia::adicionaGerente(string nomeGer) {

	Gerente g1 = Gerente(nomeGer);
	g1.setID(IDgerente);

	IDgerente++;

	gerentes.push_back(g1);

}




//Gerente
int Gerente::getID() const
{ return ID; }

string Gerente::getNome() const
{ return nome; }

Gerente::Gerente(string nm) {
	nome = nm;
}


