#ifndef JOGO_H_
#define JOGO_H_

#include "BinaryTree.h"
#include <iostream>
#include <stdlib.h>
using namespace std;


class Circulo {
 int pontuacao;
 bool estado;
 int nVisitas;
public:
 Circulo(int p=0, bool e=false): pontuacao(p), estado(e), nVisitas(0) {}
 int getPontuacao() const { return pontuacao; }
 bool getEstado() const { return estado; }
 int getNVisitas() const { return nVisitas; }
 friend ostream &operator << (ostream &os, Circulo &c1);
 void changeState() {estado = !estado;}
 void incNVisitas() {nVisitas++;}
};



class Jogo {
	BinaryTree<Circulo> jogo;
public:
	BinaryTree<Circulo> start(int pos, int niv, vector<int> &pontos, vector<bool> &estados);
	Jogo(int niv, vector<int> &pontos, vector<bool> &estados);
	BinaryTree<Circulo> &getJogo();
	string escreveJogo();
	int jogada();
	int maisVisitado();
};


#endif
