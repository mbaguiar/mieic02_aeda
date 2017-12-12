
#include "Clinica.h"

//Animal

Animal::Animal(string umNome, string umaEspecie, int numeroConsultas):
nome(umNome), especie(umaEspecie), numConsultas(numeroConsultas)
{}

string Animal::getNome() const
{ return nome; }

string Animal::getEspecie() const
{ return especie; }

int Animal::getNumConsultas() const
{ return numConsultas; }

void Animal::incNumConsultas()
{ numConsultas++; }


// Veterinario

Veterinario::Veterinario(string umNome):nome(umNome)
{}

string Veterinario::getNome() const
{ return nome; }

list<string> Veterinario::getAnimais() const
{ return meusAnimais; }

void Veterinario::addAnimal(string umNomeAnimal)
{ meusAnimais.push_back(umNomeAnimal); }


// Consulta

Consulta::Consulta(int umaHora, int umDia, int umMes, string umNomeAnimal):
	hora(umaHora), dia(umDia), mes(umMes), nomeAnimal(umNomeAnimal)
{}

string Consulta::getNomeAnimal() const
{ return nomeAnimal; }

int Consulta::getHora() const { return hora; }
int Consulta::getDia() const { return dia; }
int Consulta::getMes() const { return mes; }


void ConsultasVet::addConsulta(const Consulta &c1)
{ minhasConsultas.insert(c1); }


//Clinica

Clinica::Clinica()
{}

list<ConsultasVet> Clinica::getConsultasDisponiveis() const
{ return consultasDisponiveis; }

hashAnimal Clinica::getAnimais() const
{ return animais; }

priority_queue<Veterinario> Clinica::getVeterinarios() const
{ return veterinarios; }

void Clinica::addConsultasDisponiveisVet(const ConsultasVet &v1)
{ consultasDisponiveis.push_front(v1); }

void Clinica::addAnimal(const Animal &a1)
{ animais.insert(a1); }

void Clinica::addVeterinario(const Veterinario &v1)
{ veterinarios.push(v1); }

void Clinica::addConsultas(const vector<Consulta> consultas1, string nomeVet) {
	for (auto it = consultasDisponiveis.begin(); it != consultasDisponiveis.end(); it++) {
		if ((*it).nomeVeterinario == nomeVet) {
			for (auto c : consultas1) {
				(*it).addConsulta(c);
			}
			return;
		}
	}
	ConsultasVet temp = ConsultasVet(nomeVet);
	for (auto c : consultas1) {
		temp.addConsulta(c);
	}
	consultasDisponiveis.push_front(temp);
}

list<Consulta> Clinica::veConsultasDisponiveis(int dia1, int dia2, int mesC, string nomeVet) const {
	list<Consulta> aux;
	for (auto it = consultasDisponiveis.begin(); it != consultasDisponiveis.end(); it++) {
		if ((*it).nomeVeterinario == nomeVet) {
			BSTItrIn<Consulta> it2 = (*it).minhasConsultas;
			while(!it2.isAtEnd()) {

				if (it2.retrieve().getMes() == mesC && it2.retrieve().getDia() >= dia1 && it2.retrieve().getDia() <= dia2) {
					aux.push_back(it2.retrieve());
				}

				it2.advance();

			}
		}
	}
	return aux;
}

bool Clinica::marcaConsulta(int &horaC, int &diaC, int &mesC, string nomeAnimal, string nomeVet) {
	Consulta c = Consulta(horaC, diaC, mesC);
	for (auto it = consultasDisponiveis.begin(); it != consultasDisponiveis.end(); it++) {
		if ((*it).nomeVeterinario == nomeVet) {
			BSTItrIn<Consulta> it2 = (*it).minhasConsultas;
			while(!it2.isAtEnd()) {
				if (it2.retrieve().getNomeAnimal() == "") {
					if (it2.retrieve().getHora() == horaC && it2.retrieve().getDia() == diaC && it2.retrieve().getMes() == mesC) {
						(*it).minhasConsultas.remove(it2.retrieve());
						return true;

					}
				}
				it2.advance();
			}
			it2 = (*it).minhasConsultas;
			while(!it2.isAtEnd()) {
				if (it2.retrieve().getNomeAnimal() == "" && c < it2.retrieve()) {
					horaC = it2.retrieve().getHora();
					diaC = it2.retrieve().getDia();
					mesC = it2.retrieve().getMes();
					(*it).minhasConsultas.remove(it2.retrieve());
					return true;
				}

				it2.advance();
			}
		}
	}
	return false;
}

Animal Clinica::fimConsulta(string umNomeAnimal, string umNomeEspecie) {
	for (auto it = animais.begin(); it != animais.end(); it++) {
		Animal temp = Animal("","");
		if ((*it).getNome() == umNomeAnimal && (*it).getEspecie() == umNomeEspecie) {
			temp = (*it);
			animais.erase(it);
			temp.incNumConsultas();
			animais.insert(temp);
			return temp;
		}
	}
	Animal animal = Animal(umNomeAnimal, umNomeEspecie, 1);
	animais.insert(animal);
	return animal;
}

int Clinica::numAnimaisEspecie(string umNomeEspecie) const {
	int n = 0;
	for (auto it = animais.begin(); it != animais.end(); it++) {
		if ((*it).getEspecie() == umNomeEspecie)
			n++;
	}
	return n;
}

Veterinario Clinica::alocaVeterinario(string umNomeAnimal) {
	Veterinario temp = veterinarios.top();
	veterinarios.pop();
	temp.addAnimal(umNomeAnimal);
	veterinarios.push(temp);
	return temp;
}

list<string> Clinica::veterinariosMaisN(int n) const {
	list<string> temp;
	priority_queue<Veterinario> aux = veterinarios;
	while(!aux.empty()) {
		if (aux.top().getAnimais().size() > n) {
			temp.push_front(aux.top().getNome());
		}
		aux.pop();
	}
	return temp;
}


/////////////////////////////////////////////////////////////////////////


//TODO: Implementar corretamente o construtor e inicializacao da BST!
ConsultasVet::ConsultasVet(string umNomeVet): nomeVeterinario(umNomeVet),
		minhasConsultas(Consulta(0,0,0))
{}


bool Consulta::operator < (const Consulta &c2) const {
	if (mes == c2.getMes()) {
		if (dia == c2.getDia()) {
			return hora < c2.getHora();
		} else return dia < c2.getDia();
	} else return mes < c2.getMes();
}

bool Veterinario::operator<(const Veterinario& v1) const {
	if (meusAnimais.size() == v1.getAnimais().size()) {
		return nome > v1.getNome();
	} else
		return meusAnimais.size() > v1.getAnimais().size();
}

