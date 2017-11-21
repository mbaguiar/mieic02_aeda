#include "ClubeVideo.h"
#include <iostream>
using namespace std;

ostream& operator<<(ostream& os, const Filme& umFilme) {
	os << umFilme.titulo << " " << umFilme.emprestimos;
	return os;
}

Filme::Filme() {

	titulo = "";
	emprestimos = 0;
}

ostream& operator<<(ostream& os, const PedidoCliente& pc) {
	os << "Cliente " << pc.nome << " em espera para " << pc.titulo << endl;
	return os;
}

PedidoCliente::PedidoCliente() {

	nome = "";
	titulo = "";

}

ostream& operator<<(ostream& os, const Cliente& c1) {
	os << c1.nome << " tem " << c1.filmesEmprestados.size() << " filmes!\n";
	return os;
}

Filme Cliente::devolver(string umTitulo) {

	Filme removido;
	stack<Filme> temp;

	while(!filmesEmprestados.empty()) {

		if (filmesEmprestados.top().getTitulo() == umTitulo) {
			removido = filmesEmprestados.top();
			filmesEmprestados.pop();
			continue;
		}

		temp.push(filmesEmprestados.top());
		filmesEmprestados.pop();

	}

	while(!temp.empty()) {

		filmesEmprestados.push(temp.top());
		temp.pop();

	}

	return removido;

}


bool ClubeVideo::existeCliente(string umNome) const {

	for (auto &c : clientes) {

		if (c.getNome() == umNome)
			return true;

	}

	return false;

}

bool ClubeVideo::existeFilme(string umTitulo) const {

	for (auto &f : filmes) {

		if (f.getTitulo() == umTitulo)
			return true;

	}

	for (auto &c : clientes) {

		stack<Filme> temp = c.getFilmesEmprestados();

		while(!temp.empty()) {

			if (temp.top().getTitulo() == umTitulo)
				return true;

			temp.pop();

		}
	}

	return false;
}

string ClubeVideo::imprimirFilmes() const {

	stringstream ss;
	for (auto &f : filmes) {

		ss << f << endl;

	}

	for (auto &c : clientes) {

		stack<Filme> temp = c.getFilmesEmprestados();

		while(!temp.empty()) {

			ss << temp.top() << endl;

			temp.pop();

		}
	}

	return ss.str();

}

list<string> ClubeVideo::titulosDisponiveis() const {

	vector<string> temp;
	list<string> result;

	for (auto &f : filmes) {

		if (temp.empty() || find(temp.begin(), temp.end(), f.getTitulo()) == temp.end()) {

			temp.push_back(f.getTitulo());

		}

	}

	sort(temp.begin(), temp.end());

	while(!temp.empty()) {

		result.push_back(temp.front());
		temp.erase(temp.begin());

	}

	return result;

}

bool ClubeVideo::tituloDisponivel(string umTitulo) const {

	for (auto &f : filmes) {

		if (f.getTitulo() == umTitulo)
			return true;

	}

	return false;
}

string ClubeVideo::imprimirListaDeEspera() const {

	queue<PedidoCliente> temp = pedidos;
	vector<string> titulos;
	string s;

	while(!temp.empty()) {

		titulos.push_back(temp.front().getTituloFilme());
		temp.pop();

	}

	sort(titulos.begin(), titulos.end());

	for (auto &t : titulos) {

		s = s + t + "\n";

	}

	return s;

}

void ClubeVideo::alugar(string umNome, string umTitulo) {

	if (!existeFilme(umTitulo)) throw FilmeInexistente(umTitulo);

	vector<Cliente>::iterator it2;

	if (!existeCliente(umNome)) clientes.push_back(Cliente(umNome));

	for (it2 = clientes.begin(); it2 != clientes.end(); it2++) {

		if ((*it2).getNome() == umNome) {

			break;
		}

	}

	if (!tituloDisponivel(umTitulo)) pedidos.push(PedidoCliente(umNome, umTitulo));

	for (auto it = filmes.begin(); it != filmes.end(); it++) {

		if ((*it).getTitulo() == umTitulo) {

			(*it).addEmprestimos();
			(*it2).addFilme((*it));
			filmes.erase(it);
			break;

		}

	}



}

void ClubeVideo::devolver(string umNome, string umTitulo) {

	Filme devolvido;

	for (auto &c : clientes) {

		if (c.getNome() == umNome) {

			devolvido = c.devolver(umTitulo);
		}
	}

	PedidoCliente p;
	queue<PedidoCliente> temp;
	bool alugado = false;

	filmes.push_back(devolvido);


	while(!pedidos.empty()) {

		if (!alugado) {

			if (pedidos.front().getTituloFilme() == umTitulo) {

				alugar(pedidos.front().getNomeCliente(), pedidos.front().getTituloFilme());
				pedidos.pop();
				alugado = true;
				continue;

			}

		}

		temp.push(pedidos.front());
		pedidos.pop();
		cout << ".";
	}

	while(!temp.empty()) {

		pedidos.push(temp.front());
		temp.pop();

	}


}






