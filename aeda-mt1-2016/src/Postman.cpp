/*
 * Postman.cpp
 */
#include "Postman.h"

Postman::Postman(): id(0) {}

Postman::Postman(string name) {

	static int i = 0;
	i++;
	this->name = name;
	this->id = i;

}

void Postman::setName(string nm){
	name = nm;
}

string Postman::getName() const{
	return name;
}

vector<Mail *> Postman::getMail() const {
	return myMail;
}

void Postman::addMail(Mail *m) {
	myMail.push_back(m);
}

void Postman::addMail(vector<Mail *> mails) {
	myMail.insert(myMail.end(),mails.begin(),mails.end());
}

unsigned int Postman::getID() const{
	return id;
}

string NoPostmanException::getName() const {
	return name;
}



