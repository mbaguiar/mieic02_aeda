/*
 * Restaurant.cpp
 *
 *  Created on: 17/11/2015
 *      Author: hlc
 */

#include "Restaurant.h"

using namespace std;

Restaurant::Restaurant() { }

Restaurant::Restaurant(vector< stack<Dish*> >* cl, queue<Dish*>* di, list<Dish*>* dr) {
	if(cl != NULL) clean = *cl;
	if(di != NULL) dirty = *di;
	if(dr != NULL) drying = *dr;
}

void Restaurant::addTable(unsigned int n_places) {
	tables.push_back(Table(n_places));
}

void Restaurant::addTable(Table& t) {
	tables.push_back(t);
}

const Table& Restaurant::getTable(vector<Table>::size_type idx) const {
	return tables[idx];
}

/**
 * Gets the clean dishes stack for a given collection and type.
 * If there is none, adds and returns an empty stack.
 */
stack<Dish*>& Restaurant::getCleanDishStack(string collection, TypeOfDish type) {

	for(vector< stack<Dish*> >::iterator it = clean.begin(); it != clean.end(); ++it) {
		if((*it).empty() || ((*it).top()->getCollection() == collection && (*it).top()->getType() == type)) {
			return *it;
		}
	}

	stack<Dish*> st;
	clean.push_back(st);
	return clean.back();
}

const queue<Dish*>& Restaurant::getDirty() const {
	return dirty;
}

const list<Dish*>& Restaurant::getDrying() const {
	return drying;
}

/**
 * Adds a number of dishes of a collection/type to the respective clean stack.
 */
void Restaurant::addDishes(unsigned int n, string collection, TypeOfDish type) {

	for (size_t i = 0; i < n ; i++) {

		Dish * temp = new Dish(collection, type);
		getCleanDishStack(collection, type).push(temp);

	}

}

/**
 * Washes a dish, getting if from the dirty queue and putting it in the wet list.
 * Returns the washed dish.
 */
Dish* Restaurant::washDish() {
	Dish* d;

	d = dirty.front();
	dirty.pop();
	drying.push_back(d);

	return d;
}

/**
 * Clears a table, placing all dishes that are on it in the dirty queue.
 */
void Restaurant::clearTable(vector<Table>::size_type idx) {

	if (idx >= tables.size() || idx < 0) return;

	vector<Dish * > temp = tables.at(idx).clear();

	for (int i = 0; i < temp.size(); i++) {

		dirty.push(temp.at(i));
	}


}

/**
 * Stores in the respective clean stack all drying dishes of a given collection and type.
 */
void Restaurant::storeDryDishes(string collection, TypeOfDish type) {

	for (list<Dish*>::iterator it = drying.begin(); it != drying.end(); it++) {

		if ((*it)->getType() == type && (*it)->getCollection() == collection) {

			getCleanDishStack(collection, type).push(*it);
			drying.erase(it);

		}

	}

}

/**
 * Puts Plates of a given collection in a table.
 * Throws TableNotReadyException when the table is not empty.
 * Throws NotEnoughDishesException when there are not enough clean plates of the collection.
 */
void Restaurant::setupTable(vector<Table>::size_type idx, string collection) {

	vector<Dish *> dishes;

	if (idx < 0 || idx >= tables.size()) return;

	for (int i = 0; i < tables.at(idx).getPlaces().size(); i++) {

		if (!tables.at(idx).getPlaces().at(i).empty())
			throw TableNotReadyException();

	}

	if (getCleanDishStack(collection, Plate).size() < tables.at(idx).getPlaces().size())
		throw NotEnoughDishesException();


	for (int i = 0; i < tables.at(idx).getPlaces().size(); i++) {

		dishes.push_back(getCleanDishStack(collection, Plate).top());
		getCleanDishStack(collection, Plate).pop();

	}

	tables.at(idx).putOn(dishes);
}

/**
 * Picks the dry dishes and groups them.
 * Returns the grouped dishes.
 */
list<Dish*> Restaurant::pickupAndGroupDryDishes() {
	list<Dish*> dry_grouped;

	while(!drying.empty()) {

		list<Dish*>::iterator it = drying.begin();
		TypeOfDish t = (*it)->getType();
		string c = (*it)->getCollection();
		dry_grouped.push_back(*it);
		drying.pop_front();

		for (it = drying.begin(); it != drying.end(); it++) {

			if ((*it)->getCollection() == c && (*it)->getType() == t) {

				dry_grouped.push_back(*it);
				drying.pop_front();
			}

		}
	}

	return dry_grouped;
}

/**
 * Stores grouped dishes in the respective clean stacks.
 * Returns the number of stacks that have been updated.
 */
int Restaurant::storeGroupedDishes(list<Dish*> grouped_dishes) {

	int i = 0;

	while(!grouped_dishes.empty()) {

		list<Dish*>::iterator it = grouped_dishes.begin();
		TypeOfDish t = (*it)->getType();
		string c = (*it)->getCollection();
		i++;

		for (it = grouped_dishes.begin(); it != grouped_dishes.end(); it++) {

			if (((*it)->getCollection() == c && (*it)->getType() == t)) {
				if (grouped_dishes.empty()) return i;
				getCleanDishStack(c, t).push(*it);
				grouped_dishes.pop_front();
			}

		}

	}

	return i;
}

