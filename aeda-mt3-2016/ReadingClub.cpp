/*
 * ReadingClub.cpp
 *
 *  Created on: 11/12/2016
 *      Author: RRossetti
 */

#include "ReadingClub.h"

ReadingClub::ReadingClub(): catalogItems(BookCatalogItem("", "", 0)) {
	//do nothing!
}

ReadingClub::ReadingClub(vector<Book*> books): catalogItems(BookCatalogItem("", "", 0)) {
	this->books = books;
}

void ReadingClub::addBook(Book* book) {
	this->books.push_back(book);
}

void ReadingClub::addBooks(vector<Book*> books) {
	this->books = books;
}

vector<Book*> ReadingClub::getBooks() const{
	return this->books;
}

BookCatalogItem ReadingClub::getCatalogItem(string title, string author) {
	BookCatalogItem itemNotFound("", "", 0);
	BSTItrIn<BookCatalogItem> it(catalogItems);
	while (!it.isAtEnd())
	{
		if( it.retrieve().getTitle() == title && it.retrieve().getAuthor() == author) {
			BookCatalogItem bci(it.retrieve().getTitle(), it.retrieve().getAuthor(), 0);
			bci.setItems(it.retrieve().getItems());
			return bci;
		}
		it.advance();
	}
	return itemNotFound;
}

void ReadingClub::addCatalogItem(Book* book) {
	BookCatalogItem itemNotFound("", "", 0);
	BookCatalogItem bci(book->getTitle(), book->getAuthor(), book->getYear());
	BookCatalogItem bciX = catalogItems.find(bci);
	if(bciX == itemNotFound) {
		bci.addItems(book);
		this->catalogItems.insert(bci);
	}
	else {
		this->catalogItems.remove(bciX);
		bciX.addItems(book);
		this->catalogItems.insert(bciX);
	}
	books.push_back(book);
}

BST<BookCatalogItem> ReadingClub::getCatalogItems() const {
	return this->catalogItems;
}

vector<UserRecord> ReadingClub::getUserRecords() const {
	vector<UserRecord> records;
	HashTabUserRecord::const_iterator it1 = this->userRecords.begin();
	HashTabUserRecord::const_iterator it2 = this->userRecords.end();
	for(; it1 != it2; it1++) {
			records.push_back(*it1);
	}
	return records;
}

void ReadingClub::setUserRecords(vector<UserRecord>& urs) {
	for(int i = 0; i < urs.size(); i++) userRecords.insert(urs[i]);
}

priority_queue<User> ReadingClub::getBestReaderCandidates() const {
	return readerCandidates;
}
void ReadingClub::setBestReaderCandidates(priority_queue<User>& candidates) {
	readerCandidates = candidates;
}



//
// TODO: Part I   - BST
//

void ReadingClub::generateCatalog() {
	for (int i = 0; i < books.size(); i++) {

		bool found = false;

		BSTItrIn<BookCatalogItem> it(catalogItems);

		while(!it.isAtEnd()) {

			if (it.retrieve() == BookCatalogItem(books.at(i)->getTitle(), books.at(i)->getAuthor(),0)) {
				it.retrieve().addItems(books.at(i));
				found = true;
				break;
			}
			it.advance();
		}

		if (!found) {
			BookCatalogItem temp = BookCatalogItem(books.at(i)->getTitle(), books.at(i)->getAuthor(),0);
			temp.addItems(books.at(i));
			catalogItems.insert(temp);
		}
	}
}

vector<Book*> ReadingClub::getAvailableItems(Book* book) const {
	vector<Book*> temp;

	BSTItrIn<BookCatalogItem> it(catalogItems);

	while(!it.isAtEnd()) {
		if (it.retrieve().getAuthor() == book->getAuthor() && it.retrieve().getTitle() == book->getTitle()) {

			for (int i = 0; i < it.retrieve().getItems().size(); i++) {
				if (it.retrieve().getItems().at(i)->getReader() == 0)
					temp.push_back(it.retrieve().getItems().at(i));
			}
			return temp;
		}

		it.advance();
	}

	return temp;
}

bool ReadingClub::borrowBookFromCatalog(Book* book, User* reader) {

	vector<Book *> temp = getAvailableItems(book);
	if (temp.empty())
		return false;

	temp.at(0)->setReader(reader);
	reader->addReading(temp.at(0)->getTitle(), temp.at(0)->getAuthor());
	return true;
}


//
// TODO: Part II  - Hash Table
//

void ReadingClub::addUserRecord(User* user) {
	UserRecord record = UserRecord(user);
	userRecords.insert(record);

}

void ReadingClub::changeUserEMail(User* user, string newEMail) {
	user->setEMail(newEMail);
}


//
// TODO: Part III - Priority Queue
//

void ReadingClub::addBestReaderCandidates(const vector<User>& candidates, int min) {
	for (int i = 0; i < candidates.size(); i++) {
		if (candidates.at(i).numReadings() >= min)
			readerCandidates.push(candidates.at(i));
	}

}

int ReadingClub::awardReaderChampion(User& champion) {
	if (readerCandidates.empty()) return 0;
	User temp = readerCandidates.top();
	readerCandidates.pop();
	if (temp.numReadings() == readerCandidates.top().numReadings())
		return 0;
	readerCandidates.push(temp);
	champion = readerCandidates.top();

	return readerCandidates.size();
}
























