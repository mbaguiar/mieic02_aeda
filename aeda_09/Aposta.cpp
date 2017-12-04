#include "Aposta.h"
#include <iostream>
#include <sstream>

using namespace std;

bool Aposta::contem(unsigned num) const {

	for(auto it = numeros.begin(); it != numeros.end(); it++) {

		if ((*it) == num)
			return true;
	}

	return false;
}


void Aposta::geraAposta(const vector<unsigned> & valores, unsigned n) {

	unsigned num = 0;
	int i = 0;
	numeros.clear();

	while(num < n) {

		if (!contem(valores.at(i))) {

			numeros.insert(valores.at(i));
			num++;
		}

		i++;
	}



}


unsigned Aposta::calculaCertos(const tabHInt & sorteio) const {
	unsigned certos = 0;

	for (auto it = sorteio.begin(); it != sorteio.end(); it++) {

		if (contem((*it)))
			certos++;

	}

	return certos;
}




