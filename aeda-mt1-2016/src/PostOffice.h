/*
 * PostOffice.h
 */

#ifndef SRC_POSTOFFICE_H_
#define SRC_POSTOFFICE_H_

#include "Mail.h"
#include "Postman.h"
#include <vector>


class PostOffice {
	vector<Mail *> mailToSend;
	vector<Mail *> mailToDeliver;
	vector<Postman> postmen;
	string firstZipCode, lastZipCode;
public:
	PostOffice();
	PostOffice(string firstZCode, string lastZCode);
	void addMailToSend(Mail *m);
	void addMailToDeliver(Mail *m);
	void addPostman(const Postman &p);
	vector<Mail *> getMailToSend() const;
	vector<Mail *> getMailToDeliver() const;
	vector<Postman> getPostman() const;
	//-------
	vector<Mail *> removePostman(string name);
	vector<Mail *> endOfDay(unsigned int &balance);
	Postman addMailToPostman(Mail *m, string name);
};

template <typename T>
unsigned int numberDifferent (const vector<T> & v1) {

	bool present;
	vector<T> v2;

	for (size_t i = 0; i < v1.size(); i++) {

		present = false;

		T element = v1.at(i);

		for (size_t t = 0; t < v2.size(); t++) {

			if(v2.at(t) == element)
				present = true;

		}

		if(!present) {

			v2.push_back(element);

		}

	}

	return v2.size();

}

#endif /* SRC_POSTOFFICE_H_ */
