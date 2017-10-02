#include "zoo.h"

string Animal::getNome() const {
	return nome;
}



string Veterinario::getNome() const {
	return nome;
}


int Zoo::numAnimais() const {
	return animais.size();
}

int Zoo::numVeterinarios() const {
	return veterinarios.size();
}
