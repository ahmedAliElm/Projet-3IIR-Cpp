#include <iostream>
#include <deque>
#include <vector>
#ifndef Panier_virtuel_h
#define Panier_virtuel_h

using namespace std;

int menu();


class Article {

public:

	int quantite;
	string reference;
	double prix;

	Article();
	Article(string ref, double price, int qte);

	Article& operator=(const Article& other);
	friend ostream& operator<<(ostream& os, const Article& obj);
	bool operator<(const Article& other) const;

	bool articlesIdentiques(Article A1, string ref);
	void commande(int qt);
	void remplirArticle(string ref, double pr, int qt);
	void modifierQte(int qte);

};


class Stock {

public:

	vector<Article> V;

	Stock();
	Stock(vector<Article> vec);

	void remplirStock(Article A);
	void afficherStock();
	void diminuerQte(int qte, Stock& S, string ref);

};


class Panier {

public:

	deque<Article> P;

	Panier();
	Panier(deque<Article> D);

	Panier& operator=(const Panier& other);

	bool ajouterArticle(string ref, Stock S, int qte);
	void afficherPanier();
	bool remise();
	void lePlusCher();
	void articlesEntreMinMax(double min, double max);
	void infoArticles(string ref);

};


class Client {

protected:

	string email;
	string nom;

public:

	Client();
	Client(string mail, string name);

	Client& operator=(const Client& other);

};


class Commande : public Client, Panier {

	int numero;

public:

	Commande();
	Commande(int num);

	void totalCmd(Panier& Pa);

};


#endif

