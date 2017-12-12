/*
 * CinemaFinder.cpp
 */

#include "CinemaFinder.h"
#include "Cinema.h"
#include "Film.h"
#include <algorithm>

CinemaFinder::CinemaFinder() { }

CinemaFinder::~CinemaFinder() { }

void CinemaFinder::addFilm(Film *f1) {
	FilmPtr fp1;
	fp1.film = f1;
	films.insert(fp1);
}

void CinemaFinder::addCinema(const Cinema &c1)
{ cinemas.push(c1); }

tabHFilm CinemaFinder::getFilms() const
{ return films; }

priority_queue<Cinema> CinemaFinder::getCinemas() const
{ return cinemas; }


// TODO


//b1
list<string> CinemaFinder::filmsWithActor(string actorName) const {
	list<string> res;

	for (auto it = films.begin(); it != films.end(); it++) {
		list<string> aux = (*it).film->getActors();
		for (auto it2 = aux.begin(); it2 != aux.end(); it2++){
			if ((*it2) == actorName)
				res.push_back((*it).film->getTitle());
		}
	}
	return res;
}


//b2
void CinemaFinder::addActor(string filmTitle, string actorName) {

	for (auto it = films.begin(); it != films.end(); it++) {
		if ((*it).film->getTitle() == filmTitle) {
			(*it).film->addActor(actorName);
			return;
		}
	}

	list<string> temp;
	Film *filme = new Film(filmTitle, temp);
	filme->addActor(actorName);
	FilmPtr f;
	f.film = filme;
	films.insert(f);


}


//c1
string CinemaFinder::nearestCinema(string service1) const {
	string cName="";
	priority_queue<Cinema> temp = cinemas;

	while(!temp.empty()) {
		list<string> s = temp.top().getServices();
		for (auto it = s.begin(); it != s.end(); it++) {
			if ((*it) == service1)
				return temp.top().getName();
		}
		temp.pop();
	}

	return cName;
}


//c2
void CinemaFinder::addServiceToNearestCinema(string service1, unsigned maxDistance) {

	if (cinemas.empty()) throw CinemaNotFound();
	Cinema temp = cinemas.top();
	cinemas.pop();
	if (temp.getDistance() > maxDistance) {
		cinemas.push(temp);
		throw CinemaNotFound();
	}

	temp.addService(service1);
	cinemas.push(temp);

}
