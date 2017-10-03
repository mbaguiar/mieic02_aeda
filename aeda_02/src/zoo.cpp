#include "zoo.h"

#include <string>
#include <vector>
#include <iostream>

int Animal::maisJovem = -1;

string Animal::getNome() const {
    return nome;
}

string Veterinario::getNome() const {
    return nome;
}

int Animal::getIdade() const {

    return idade;
}

int Zoo::numAnimais() const {
    return animais.size();
}

int Zoo::numVeterinarios() const {
    return veterinarios.size();
}

void Animal::setVet(Veterinario *vet) {

    this->vet = vet;

}

const Veterinario* Animal::getVet() const {

    return vet;
}

Veterinario::Veterinario(string nome, long cod) {

    this->nome = nome;
    this->codOrdem = cod;
}

Animal::Animal(string nome, int idade) {

    if(Animal::getMaisJovem() == -1 || idade < Animal::getMaisJovem())
        Animal::maisJovem = idade;
    this->nome = nome;
    this->idade = idade;
    this->vet = nullptr;
}

Cao::Cao(string nome, int idade, string raca) : Animal(nome, idade) , raca(raca) {

}

Voador::Voador(int vmax, int amax) {

    velocidade_max = vmax;
    altura_max = amax;
}

Morcego::Morcego(string nome, int idade, int vmax, int amax) : Animal(nome, idade), Voador(vmax, amax){

}

int Animal::getMaisJovem() {

    return Animal::maisJovem;
}

bool Cao::eJovem() const {

   return (idade < 5);
}

bool Morcego::eJovem() const {

    return (idade < 4);
}

void Zoo::adicionaAnimal(Animal *a1) {

    animais.push_back(a1);
}

string Veterinario::getInformacao() const {

    string vet;
    vet = nome + ", " + to_string(codOrdem);
    return vet;
}

string Animal::getInformacao() const {

    string animal;
    if(vet == nullptr) {
        return this->nome + ", " + to_string(this->idade);
    } else
        return this->nome + ", " + to_string(this->idade) + ", " + this->vet->getInformacao();
}

string Cao::getInformacao() const {
    string a = ", " + raca;
    return Animal::getInformacao() + a;
}

string Voador::getInformacao() const {

    return to_string(velocidade_max) + ", " + to_string(altura_max);
}

string Morcego::getInformacao() const {

    return Animal::getInformacao() + ", " + Voador::getInformacao();
}

string Zoo::getInformacao() const {

    string informacao;

    for(size_t i = 0; i < animais.size(); i++) {
        informacao = informacao + animais.at(i)->getInformacao() + "\n";
    }

    return informacao;
}

bool Zoo::animalJovem(string nomeA) {

    bool result = false;
    for(size_t i = 0; i < animais.size(); i++) {
        if(animais.at(i)->getNome() == nomeA && animais.at(i)->eJovem())
            result = true;
    }
    return result;
}

void Zoo::alocaVeterinarios(istream &isV) {

    bool isName = true;
    string temp;
    string name, cod;

    while(getline(isV, temp)) {
        if(isName)
            name = temp;
        else {
            cod = temp;
            Veterinario* vet = new Veterinario(name, stoi(cod));
            this->veterinarios.push_back(vet);
        }
        isName = !isName;
    }

    for(size_t i = 0; i < animais.size(); i++){

        animais.at(i)->setVet(veterinarios.at(i % veterinarios.size()));
    }
}

bool Zoo::removeVeterinario(string nomeV) {

    int index = -1;
    int reindex;
    for(size_t i = 0; i < veterinarios.size(); i++) {
        if(veterinarios.at(i)->getNome() == nomeV)
            index = i;
    }

    if(index == -1)
        return false;
    else {
        if(index == veterinarios.size() -1)
            reindex = 0;
        else reindex = index + 1;
        for(size_t i = 0; i < animais.size(); i++) {
            if(animais.at(i)->getVet()->getNome() == nomeV) {
                 animais.at(i)->setVet(veterinarios.at(reindex));
            }
        }

        veterinarios.erase(veterinarios.begin() + index);

       return true;
    }
}

int Zoo::getSumZoo() const {

    int sum = 0;
    for(size_t i = 0; i < animais.size(); i++) {
        sum = sum + animais.at(i)->getIdade();
    }

    return sum;
}

bool Zoo::operator<(Zoo &zoo2) const {

    if(getSumZoo() < zoo2.getSumZoo())
        return true;
    else return false;
    
}