/*
 * Jogo.cpp
 *
 */

#include "Jogo.h"
#include <iostream>
#include <sstream>
using namespace std;


unsigned Jogo::numPalavras(string frase)
{
  if ( frase.length() == 0 ) return 0;
  int n=1;
  int pos = frase.find(' ');
  while ( pos != string::npos ) {
    frase = frase.substr(pos+1);
    pos = frase.find(' ');
    n++;
  }
  return n;
}


Jogo::Jogo()
{
	// a alterar
}

Jogo::Jogo(list<Crianca>& lc2)
{
	criancas = lc2;
}

void Jogo::insereCrianca(const Crianca &c1)
{
	criancas.push_back(c1);
}

list<Crianca> Jogo::getCriancasJogo() const
{
	return this->criancas;
}


string Jogo::escreve() const {

	string res;

	for (auto &c : criancas) {
		res = res + c.escreve() + "\n";
	}

	return res;
}


Crianca& Jogo::perdeJogo(string frase) {

	unsigned int numeroPalavras = numPalavras(frase);
	unsigned int numAdvances;
	auto it = criancas.begin();

	// Repeat until there is only one child left -> the losing one
	while (criancas.size() > 1){
		numAdvances = (numeroPalavras-1)%criancas.size() ;
		it = criancas.begin();
		advance(it, numAdvances);
		criancas.erase(it);
	}

	return criancas.front();
}


list<Crianca>& Jogo::inverte()
{
	criancas.reverse();
	return criancas;
}


list<Crianca> Jogo::divide(unsigned id)
{
	list<Crianca> criancasErased;
	list<Crianca>::iterator it2;

	for (auto it = criancas.begin(); it != criancas.end(); )  {

		if (it->getIdade() > id) {

			criancasErased.push_back(*it);
			it2  = it;
			it2++;
			criancas.erase(it);
			it = it2;

		}

		it++;
	}
	cout << criancasErased.size();
	return criancasErased;


}


void Jogo::setCriancasJogo(const list<Crianca>& l1)
{
	this->criancas = l1;
}


bool Jogo::operator==(Jogo& j2)
{
	if (criancas.size() != j2.getCriancasJogo().size())
		return false;

	list<Crianca> criancas2 = j2.getCriancasJogo();

	auto it1 = criancas2.begin();
	auto it2 = criancas.begin();

	while(it2 != criancas.end()) {

		if(!(*it2 == *it1))
			return false;

		it1++;
		it2++;
	}

	return true;
}


list<Crianca> Jogo::baralha() const
{
	// a alterar
	list<Crianca> res;
	return res;
}
