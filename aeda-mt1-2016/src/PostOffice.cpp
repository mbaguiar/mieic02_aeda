/*
 * PostOffice.cpp
 */

#include "PostOffice.h"
#include <iostream>
#include <string>
#include <vector>


PostOffice::PostOffice(string firstZCode, string lastZCode):
firstZipCode(firstZCode), lastZipCode(lastZCode)
{}
PostOffice::PostOffice() {}

void PostOffice::addMailToSend(Mail *m) {
	mailToSend.push_back(m);
}

void PostOffice::addMailToDeliver(Mail *m) {
	mailToDeliver.push_back(m);
}

void PostOffice::addPostman(const Postman &p){
	postmen.push_back(p);
}

vector<Mail *> PostOffice::getMailToSend() const {
	return mailToSend;
}

vector<Mail *> PostOffice::getMailToDeliver() const {
	return mailToDeliver;
}

vector<Postman> PostOffice::getPostman() const {
	return postmen;
}

vector<Mail *> PostOffice::removePostman(string name) {

	vector<Mail *> mail;
	int index = -1;

	for (size_t i = 0; i < postmen.size(); i++) {

		if (postmen.at(i).getName() == name) {
			index = i;
		}

	}

	if (index != -1) {

		mail = postmen.at(index).getMail();
		postmen.erase(postmen.begin() + index);
		return mail;

	} else return mail;

}

vector<Mail *> PostOffice::endOfDay(unsigned int &balance) {

	balance = 0;
	vector<Mail *> mail;
	for (size_t i = 0; i < mailToSend.size(); i++) {

		balance = balance + mailToSend.at(i)->getPrice();

	}

	for (size_t i = 0; i < mailToSend.size(); i++) {

		string zipcode = mailToSend.at(i)->getZipCode();
		if ((zipcode >= firstZipCode) && (zipcode <= lastZipCode)) {
			addMailToDeliver(mailToSend.at(i));
		} else mail.push_back(mailToSend.at(i));
	}

	mailToSend.clear();

	return mail;

}

bool Postman::operator< (const Postman &p1) {

	vector<string> z1, z2;

	for (size_t i = 0; i < p1.getMail().size(); i++) {

		z1.push_back( p1.getMail().at(i)->getZipCode());

	}

	for (size_t i = 0; i < getMail().size(); i++) {

		z2.push_back(getMail().at(i)->getZipCode());

	}

	unsigned int n1 = numberDifferent(z1);
	unsigned int n2 = numberDifferent(z2);

	return (n2 < n1);

}

Postman PostOffice::addMailToPostman(Mail *m, string name) {

	bool found = false;
	int index = 0;

	for (size_t i = 0; i < postmen.size(); i++) {

		if (postmen.at(i).getName() == name) {
			found = true;
			index = i;
		}
	}

	if (!found)
		throw NoPostmanException(name);
	else{
		postmen.at(index).addMail(m);
		return postmen.at(index);
	}
}

