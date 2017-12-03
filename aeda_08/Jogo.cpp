#include "Jogo.h"
#include <sstream>

BinaryTree<Circulo> & Jogo::getJogo() {
	return jogo;
}


ostream &operator << (ostream &os, Circulo &c1)
{
	os << c1.getPontuacao() << "-";
	if(c1.getEstado())
		os << "true";
	else
		os << "false";

	os << "-" << c1.getNVisitas() << endl;
	return os;
}



BinaryTree<Circulo> Jogo::start(int pos, int niv, vector<int> &pontos, vector<bool> &estados) {
	Circulo c(pontos.at(pos), estados.at(pos));

	if (!niv)
		return BinaryTree<Circulo>(c);

	BinaryTree<Circulo> left = start(2*pos+1, niv-1, pontos, estados);
	BinaryTree<Circulo> right = start(2*pos+2, niv-1, pontos, estados);

	return BinaryTree<Circulo>(c, left,right);
}




string Jogo::escreveJogo()
{
	ostringstream result;
	BTItrLevel<Circulo> it(jogo);

	while(!it.isAtEnd()) {

		result << it.retrieve();
		it.advance();

	}

	return result.str();
}


int Jogo::jogada() {
	int score;
	BTItrLevel<Circulo> it(jogo);
	int n = 1;

	while(!it.isAtEnd()) {

		if (it.retrieve().getPontuacao() != n) {
			it.advance();
			continue;
		}

		if (it.retrieve().getEstado())
			n = 2*n+1;
		else n = 2*n;

		it.retrieve().changeState();
		it.retrieve().incNVisitas();
		score = it.retrieve().getPontuacao();
		it.advance();
	}

	return score;
}



int Jogo::maisVisitado() {
	int max = 0;

	BTItrLevel<Circulo> it(jogo);

	if(it.isAtEnd())
		return 0;

	it.advance();

	while(!it.isAtEnd()) {

		if (it.retrieve().getNVisitas() > max)
			max = it.retrieve().getNVisitas();

		it.advance();

	}

	return max;
}

Jogo::Jogo(int niv, vector<int> &pontos, vector<bool> &estados) {
	jogo=start(0, niv, pontos, estados);
}




