#include "Escritorio.h"
#include <iostream>


//Documento
Documento::Documento(int nPag, float pP, float pA):
			numPaginas(nPag), pPreto(pP), pAmarelo(pA)
{ }
Documento::~Documento() {}

int Documento::getNumPaginas() const { return numPaginas; }

float Documento::getPercentagemPreto() const { return pPreto; }

float Documento::getPercentagemAmarelo() const { return pAmarelo; }



//Impressora
Impressora::Impressora(string cod, int a): codigo(cod), ano(a)
{}
Impressora::~Impressora() {}

string Impressora::getCodigo() const
{ return codigo; }

int Impressora::getAno() const
{ return ano; }

vector<Documento> Impressora::getDocumentosImpressos() const
{ return docsImpressos; }



//ImpressoraPB
ImpressoraPB::ImpressoraPB(string cod, int a, int toner): Impressora(cod, a), numPagImprimir(toner)
{}

int ImpressoraPB::getNumPaginasImprimir() const
{ return numPagImprimir; }



//ImpressoraCores
ImpressoraCores::ImpressoraCores(string cod, int a, int toner): Impressora(cod, a),
		numPagImprimirPreto(toner), numPagImprimirAmarelo(toner)
{}

int ImpressoraCores::getNumPaginasImprimir() const {
	if (numPagImprimirPreto < numPagImprimirAmarelo) return (int)numPagImprimirPreto;
	return (int)numPagImprimirAmarelo;
}



//Funcionario
Funcionario::Funcionario(string cod): codigo(cod)
{}
Funcionario::~Funcionario() {}

void Funcionario::adicionaImpressora(Impressora *i1)
{ impressoras.push_back(i1); }

vector<Impressora *> Funcionario::getImpressoras() const
{ return impressoras; }

string Funcionario::getCodigo() const
{ return codigo; }



//Escritorio
Escritorio::Escritorio() {}
Escritorio::~Escritorio() {}

void Escritorio::adicionaImpressora(Impressora *i1)
{ impressoras.push_back(i1); }

void Escritorio::adicionaFuncionario(Funcionario f1)
{ funcionarios.push_back(f1); }

vector<Impressora *> Escritorio::getImpressoras() const
{ return impressoras; }

int Escritorio::numImpressorasSemResponsavel() const {

	int counter = 0;
	 for (size_t i = 0; i < impressoras.size(); i++) {
		 for (size_t j = 0; j < funcionarios.size(); j++) {
			 for (size_t k = 0; k < funcionarios.at(j).getImpressoras().size(); k++) {
				 if (impressoras.at(i)->getCodigo() == funcionarios.at(j).getImpressoras().at(k)->getCodigo())
					 counter ++;
			 }
		 }
	 }

	 return (impressoras.size() - counter);
}

vector<Impressora *> Escritorio::retiraImpressoras(int ano1) {

	vector<Impressora *> removidas;

	for (size_t i = 0; i < impressoras.size(); i++) {

		if (impressoras.at(i)->getAno() < ano1) {
			removidas.push_back(impressoras.at(i));
			impressoras.erase(impressoras.begin() + i);
			i--;
		}
	}

	return removidas;

}

bool Impressora::imprime(Documento doc1) {
	return false;
}

bool ImpressoraPB::imprime(Documento doc1) {

	int npags = doc1.getNumPaginas();
	if (npags < numPagImprimir) {
		numPagImprimir = numPagImprimir - npags;
		docsImpressos.push_back(doc1);
		return true;
	} else return false;
}

bool ImpressoraCores::imprime(Documento doc1) {

	int npags = doc1.getNumPaginas();
	float ppreto = doc1.getPercentagemPreto();
	float pamarelo = doc1.getPercentagemAmarelo();

	if ((npags*ppreto < numPagImprimirPreto) && (npags*pamarelo < numPagImprimirAmarelo)) {
		numPagImprimirPreto -= npags*ppreto;
		numPagImprimirAmarelo -= npags*pamarelo;
		docsImpressos.push_back(doc1);
		return true;
	} else return false;
}

Impressora * Escritorio::imprimeDoc(Documento doc1) const {

	for (size_t i = 0; i < impressoras.size(); i++) {

		if (impressoras.at(i)->imprime(doc1)) {
			return impressoras.at(i);
		}
	}

	Impressora *imp = new Impressora("inexistente", 0);
	return imp;
}

bool Impressora::tonerBaixo() const {
	return false;
}

bool ImpressoraPB::tonerBaixo() const {

	if (numPagImprimir < 30)
		return true;
	else return false;

}

bool ImpressoraCores::tonerBaixo() const {

	if((numPagImprimirPreto < 20) || (numPagImprimirAmarelo < 20))
		return true;
	else return false;
}

vector<Impressora *> Escritorio::tonerBaixo() const {

	vector<Impressora *> imps;

	for (size_t i = 0; i < impressoras.size(); i++) {

		if(impressoras.at(i)->tonerBaixo())
			imps.push_back(impressoras.at(i));
	}

	return imps;
}

Documento& Documento::operator+(const Documento &d1) {


	float preto = (pPreto*numPaginas + d1.getPercentagemPreto()*d1.getNumPaginas())/(numPaginas + d1.getNumPaginas());
	float amarelo = (pAmarelo*numPaginas + d1.getPercentagemAmarelo()*d1.getNumPaginas())/(numPaginas + d1.getNumPaginas());
	int paginas = numPaginas + d1.getNumPaginas();

	Documento *d = new Documento(paginas, preto, amarelo);

	return *d;
}

string Escritorio::operator()(string imp) {

	for (size_t i = 0; i < funcionarios.size(); i++) {
		for (size_t j = 0; j < funcionarios.at(i).getImpressoras().size(); j++) {
			if (imp == funcionarios.at(i).getImpressoras().at(j)->getCodigo())
				return funcionarios.at(i).getCodigo();
		}
	}

	return "nulo";

}
