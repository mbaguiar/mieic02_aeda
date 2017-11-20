/*
 * Purchase.cpp
 *
 *  Created on: Nov 16, 2016
 *      Author: hlc
 */

#include "Purchase.h"
#include <iostream>

using namespace std;

Purchase::Purchase(long cli) : client (cli) {

}

long Purchase::getClient() const {
	return client;
}

list< stack<Article*> > Purchase::getBags() const {
	return bags;
}

/**
 * Create an Article associated with the client of this purchase.
 */
Article* Purchase::createArticle(long barCode, bool present, bool deliverHome) {

	Article * article = new Article(client, barCode);
	article->setPresent(present);
	article->setDeliverHome(deliverHome);
	return article;

}

/**
 * Add an Article to the bags of this purchase. A new bag is added when the last bag is full.
 */
void Purchase::putInBag(Article* article) {

	if (bags.back().size() >= Purchase::BAG_SIZE) {

		stack<Article *> newbag;

		newbag.push(article);

		bags.push_back(newbag);

	} else
		bags.back().push(article);

}

/**
 * Pop from the bags all articles that are presents.
 * All other articles are pushed back into the bags where they were, maintaining order.
 */
vector<Article*> Purchase::popPresents() {

	vector<Article*> presents;

	for (auto &b : bags) {

		stack <Article *> t;

		while(!b.empty()) {

			if (b.top()->getPresent()) presents.push_back(b.top());
			else
				t.push(b.top());
			b.pop();
			}

			while(!t.empty()) {

				b.push(t.top());
				t.pop();
		}
	}
	return presents;

}

