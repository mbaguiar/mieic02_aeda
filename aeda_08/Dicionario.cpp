#include <iostream>
#include <string>
#include <fstream>
#include "Dicionario.h"
#include "BST.h"

using namespace std;


BST<PalavraSignificado> Dicionario::getPalavras() const {
    return palavras;
}



bool PalavraSignificado::operator < (const PalavraSignificado &ps1) const
{
	return palavra < ps1.getPalavra();
}


void Dicionario::lerDicionario(ifstream &fich)
{
	string word, meaning;

	while(getline(fich, word)) {

		getline(fich, meaning);
		PalavraSignificado ps(word, meaning);
		palavras.insert(ps);
	}
}


string Dicionario::consulta(string palavra) const {

    BSTItrIn<PalavraSignificado> it(palavras);
    PalavraSignificado before("","");
    PalavraSignificado temp("","");

    while(!it.isAtEnd()) {

        temp = it.retrieve();

        if (temp.getPalavra() == palavra)
            return temp.getSignificado();

        if (temp.getPalavra() > palavra)
            throw (PalavraNaoExiste(before, temp));

        before = it.retrieve();
        it.advance();
    }

    throw PalavraNaoExiste(temp, PalavraSignificado("",""));

}


bool Dicionario::corrige(string palavra, string significado) {

    BSTItrIn<PalavraSignificado> it(palavras);

    while(!it.isAtEnd()) {

        if (it.retrieve().getPalavra() == palavra) {
            it.retrieve().setSignificado(significado);
            return true;
        }

        it.advance();
    }

    palavras.insert(PalavraSignificado(palavra,significado));
    return false;
}


void Dicionario::imprime() const
{
	BSTItrIn<PalavraSignificado> it(palavras);

    while(!it.isAtEnd()) {

        cout << it.retrieve().getPalavra() << endl;
        cout << it.retrieve().getSignificado() << endl;
        it.advance();

    }
}
