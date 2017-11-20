/*
 * pizzeria.cpp
 *
 *  Created on: 25 Oct 2015
 *      Author: RRossetti
 */

#include "pizzeria.h"

/*
 * CLASS MENU
 */


Menu::Menu() {
	id = 0;
	name = "";
	likes = 0;
}

Menu::Menu(int id1, string n1, vector<string> is1, int lks1) {
	id = id1;
	name = n1;
	ingredients = is1;
	likes = lks1;
}

Menu::Menu(string n1, vector<string> is1) {

	static int  i = 0;
	i++;
	id = i;
	name = n1;
	likes = 0;
	ingredients = is1;

}

int Menu::getId() const { return id; }
void Menu::setId(int id1) { id = id1; }
string Menu::getName() const { return name; }
void Menu::setName(string n1) { name = n1; }
vector<string> Menu::getIngredients() const { return ingredients; }

void Menu::setIngredients(const vector<string> &is1) {

	if (!isSet(is1))
		throw ExceptionIngredientsRepeated();

	ingredients = is1;

}


/*
 * CLASS CUSTOMER
 */

Customer::Customer(int nif1, string n1) {
	nif = nif1;
	name = n1;
}

int Customer::getNIF() const {
	return nif;
}

string Customer::getName() const {
	return name;
}


/*
 * CLASS PIZZERIA
 */

Pizzeria::Pizzeria() { }

Pizzeria::Pizzeria(vector<Menu> ms1) {
	menus = ms1;
}

vector<Menu> Pizzeria::getMenus() const { return menus; }

vector<Customer*> Pizzeria::getCustomers() const { return customers; }

int Pizzeria::addCustomer(Customer* c1) {
	customers.push_back(c1);
	return customers.size();
}

vector<Menu> Pizzeria::optionsWithinIngredientLimits(int i1, int i2) const {

	if (i1 < 1 || i2 < 1 || i1 > i2) throw ExceptionInvalidIngredientLimits();
	vector<Menu> menus1;

	for (auto m : menus) {

		if (m.getIngredients().size() >= i1 && m.getIngredients().size() <= i2)
			menus1.push_back(m);

	}

	return menus1;
}

vector<Menu> Pizzeria::popularityRank() const {

	vector<Menu> popular = menus;
	sort(popular.begin(), popular.end(), aux);
	return popular;

}

Customer *Pizzeria::chefCustomer() {

	float ratio = 0;
	Customer * customer;

	for (auto p : customers) {

		float likes = 0;
		float menu = 0;

		for (auto m : menus) {

			if (m.getName() == p->getName()) {
				menu++;
				likes = likes + m.getLikes();
			}

		}

		if (ratio < likes/menu) {
			ratio = likes/menu;
			customer = p;
		}

	}

	return customer;

}

Menu &Pizzeria::removeIngredient(vector<string> is1, string i1) {

	sort(is1.begin(), is1.end());

	for (auto &m : menus) {

		vector<string> temp;
		temp = m.getIngredients();
		sort(temp.begin(), temp.end());

		if (temp == is1) {

			vector <string> aux = m.getIngredients();
			auto it = find(aux.begin(), aux.end(), i1);
			if (it != aux.end()) {

				aux.erase(it);
				m.setIngredients(aux);
				return m;

			}
			else throw Menu::ExceptionIngredientNotPresent(i1);

		}

	}

	throw ExceptionInexistentMenu();


}

bool aux(Menu m1, Menu m2) {

	if (m1.getLikes() == m2.getLikes()) {

		if (m1.getIngredients() == m2.getIngredients()) {
		return m1.getName() < m2.getName();
		} else return m1.getIngredients() < m2.getIngredients();

	}else return m1.getLikes() > m2.getLikes();

}


