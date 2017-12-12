/*
 * Cinema.cpp
 */
#include "Cinema.h"

Cinema::Cinema(string nm, unsigned d, unsigned nr): name(nm), distance(d),
		numberOfRooms(nr),timetable(FilmTime(0,NULL, 0))
{}

Cinema::Cinema(string nm, unsigned d, unsigned nr, list<string> ls): name(nm), distance(d),
		numberOfRooms(nr),services(ls), timetable(FilmTime(0,NULL,0))
{}

Cinema::~Cinema() { }

string Cinema::getName() const
{ return name; }

unsigned Cinema::getDistance() const
{ return distance; }

list<string> Cinema::getServices() const
{ return services; }

BST<FilmTime> Cinema::getTimetable() const
{ return timetable; }

void Cinema::addService(string service1)
{ services.push_back(service1); }

void Cinema::addFilmTime(const FilmTime &ft1)
{ timetable.insert(ft1); }




bool Cinema::operator<(const Cinema & cr) const
{
	return distance > cr.getDistance();
}


//a1
Film *Cinema::filmAtHour(unsigned &h1) const {
	Film *res = NULL;


	BSTItrIn<FilmTime> it (timetable);
	if(timetable.isEmpty()) return res;
	if(it.retrieve().getHour() > h1) return res;
	while(!it.isAtEnd()) {

		if (it.retrieve().getHour() == h1)
			return it.retrieve().getFilm();

		it.advance();
	}
	it = timetable;
	while (!it.isAtEnd()) {
		FilmTime temp = it.retrieve();
		it.advance();
		if (!it.isAtEnd()) {
			if (temp.getHour() < h1 && it.retrieve().getHour() > h1) {
				h1 = temp.getHour();
				return temp.getFilm();
			}
		}else{
			h1 = temp.getHour();
			return temp.getFilm();
		}
	}

}


//a2
bool Cinema::modifyHour(unsigned h1, unsigned room1, unsigned h2) {
	BSTItrIn<FilmTime> it(timetable);
	while(!it.isAtEnd()) {
		if (it.retrieve().getRoomID() == room1 && it.retrieve().getHour() == h2)
			return false;
		it.advance();
	}
	it = timetable;
	while(!it.isAtEnd()) {
		if (it.retrieve().getRoomID() == room1 && it.retrieve().getHour() == h1) {
			FilmTime film = FilmTime(h2, it.retrieve().getFilm(), it.retrieve().getRoomID());
			timetable.remove(it.retrieve());
			timetable.insert(film);
			return true;
		}
		it.advance();
	}

	return false;
}


//a3
unsigned Cinema::addFilm(Film *f1, unsigned h1) {
	unsigned roomToUse = 0;

	for (int i = 1; i <= numberOfRooms; i++) {

		BSTItrIn<FilmTime> it(timetable);
		bool found = false;
		while(!it.isAtEnd()) {
			if (it.retrieve().getRoomID() == i && it.retrieve().getHour() == h1)
				found = true;

			it.advance();
		}
		if(!found) {
			timetable.insert(FilmTime(h1,f1,i));
			return i;
		}
	}

	return roomToUse;
}






