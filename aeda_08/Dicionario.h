#ifndef _DIC
#define _DIC
#include <string>
#include <fstream>
#include "BST.h"


class PalavraSignificado {
      string palavra;
      string significado;
public:
       PalavraSignificado(string p, string s): palavra(p), significado(s) {}
       string getPalavra() const { return palavra; }
       string getSignificado() const { return significado; }
       void setSignificado(string sig) { significado = sig; }
       bool operator < (const PalavraSignificado &ps1) const;
};

class Dicionario {
      BST<PalavraSignificado> palavras;
public:
      Dicionario(): palavras(PalavraSignificado("","")){};
      BST<PalavraSignificado> getPalavras() const;
      void lerDicionario(ifstream &fich);
      string consulta(string palavra) const;
      bool corrige(string palavra, string significado);
      void imprime() const;
};


// a alterar
class PalavraNaoExiste {
private:
    PalavraSignificado pBefore;
    PalavraSignificado pAfter;
public:
    PalavraNaoExiste(PalavraSignificado pBefore, PalavraSignificado pAfter) : pBefore(pBefore), pAfter(pAfter) {}
	string getPalavraAntes() const { return pBefore.getPalavra(); }
	string getSignificadoAntes() const { return pBefore.getSignificado(); }
	string getPalavraApos() const { return pAfter.getPalavra(); }
	string getSignificadoApos() const { return pAfter.getSignificado(); }
};



#endif
