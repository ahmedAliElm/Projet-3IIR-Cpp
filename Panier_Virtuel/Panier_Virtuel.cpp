#include <iostream>
#include <deque>
#include <vector>
#include <string>
#include <algorithm>
#include "Panier_Virtuel.h"

using namespace std;

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"

// Fonction menu:

int menu() {

	string choix;

	cout << endl << "\033[1m" << "Bienvenu cher(e) client(e)" << RESET << endl << endl;
	cout << "\t 1 - Ajouter un article a votre panier." << endl << endl;
	cout << "\t 2 - Modifier la quantite commandee d\'un article deja commande." << endl << endl;
	cout << "\t 3 - Supprimer un article du panier." << endl << endl;
	cout << "\t 4 - Vider votre panier." << endl << endl;
	cout << "\t 5 - Afficher le montant total de ma commande." << endl << endl;
	cout << "\t 6 - Afficher l\'article le plus cher." << endl << endl;
	cout << "\t 7 - Afficher les articles dont le prix est compris entre deux valeurs." << endl << endl;
	cout << "\t 8 - Afficher les informations d\'un article." << endl << endl;
	cout << "\t 9 - Quitter." << endl << endl;
	cout << "\t    Veuillez entrer votre choix: "; 

	while (true) {

		getline(cin, choix);

		// Check if the input consists only of digits
		if (choix.find_first_not_of("0123456789") == string::npos) {
			// If input consists only of digits, convert it to an integer
			int choice = stoi(choix);

			// Check if the integer falls within the range 1-9
			if (choice >= 1 && choice <= 9)
				// If valid choice, return it
				return choice;

			else 
				// If not in the range, display error message and prompt again
				cout << endl << RED << "--> Veuillez saisir un choix valide: " << RESET;
		}
		else 
			// If input contains non-digit characters, display error message and prompt again
			cout << endl << RED << "--> Veuillez saisir un choix valide: " << RESET;
	}

}




// Classe Article:

Article::Article() : reference(""), prix(0), quantite(0) {}  // Constructeur par défaut 

Article::Article(string ref, double price, int qte) {  // Constructeur avec paramètres 

	reference = ref;
	prix = price;
	quantite = qte;

}

Article& Article::operator=(const Article& other) {  // Surcharge de l'opérateur =

	if (this != &other) {

		reference = other.reference;
		prix = other.prix;
		quantite = other.quantite;

	}

	return *this;

}

ostream& operator<<(ostream& os, const Article& obj) {  // Surcharge de l'opérateur <<

	os << "Reference: " << obj.reference << endl;
	os << "Prix: " << obj.prix << "dhs" << endl;
	os << "Quantite: " << obj.quantite << endl;

	return os;

}

bool Article::operator<(const Article& other) const {
	return prix < other.prix;
}

bool Article::articlesIdentiques(Article A1, string ref) {

	if (A1.reference == ref)
		return true;

	return false;

}

void Article::remplirArticle(string ref, double pr, int qt) {

		reference = ref;
		prix = pr;
		quantite = qt;

}

void Article::modifierQte(int qte) {

	quantite -= qte;

}



// Classe Stock:

Stock::Stock() {}  // Constructeur par défaut 

Stock::Stock(vector<Article> vec) {  // Constructeur avec paramètres 

	for (auto& i : V)
		V.push_back(i);

}

void Stock::remplirStock(Article A) {

	string reference = "001";
	double pr = 100;
	int qt = 10;

	for (int i = 0; i < 5; i++) {

		A.remplirArticle(reference, pr, qt);

		int ctr = 0; // Compteur pour parcourir la liste

		for (char c : reference) {

			if ((ctr == reference.length() - 1))

				reference.erase(ctr, 1);

			ctr++;

		}

		reference += to_string(i + 2); // Ajouter à la fin de la liste le prochain chiffre (2-3-4-5)
		pr -= 10;
		qt += 10;

		this->V.push_back(A);

	}

}

void Stock::afficherStock() {
	
	cout << endl << "-- Stock --" << endl << endl;

	for (auto& i : V)
		cout << i << endl;

}

void Stock::diminuerQte(int qte, Stock& S, string ref) {

	for (auto& i : S.V) {

		if (i.reference == ref) {
			i.modifierQte(qte);
			break;
		}

	}

}



// Classe Panier:

Panier::Panier() {}  // Constructeur par défaut 

Panier::Panier(deque<Article> D) {  // Constructeur avec paramètres 

	for (auto& i : P)
		P.push_back(i);

}

Panier& Panier::operator=(const Panier& other) {  // Surcharge de l'opérateur =

	if (this != &other) {

		for (auto& i : other.P)
			P.push_back(i);

	}

	return *this;

}

bool Panier::ajouterArticle(string ref, Stock S, int qte) {

	bool articleTrouve = false;

	for (auto& article : S.V) {
		
		if (article.articlesIdentiques(article, ref)) {

			article.quantite = qte;

			this->P.push_back(article);

			articleTrouve = true;
			break; 

		}
	}

	if (articleTrouve) {

		cout << endl << CYAN << "--> Article ajoute avec succes." << RESET << endl;
		return true;

	}

	else {

		cout << endl << "--> Article non disponible!" << endl;
		return false;

	}
}

void Panier::afficherPanier() {

	string choix; bool temp = false; int convertirInt{ 0 };

	sort(P.begin(), P.end());

	do {

		if (!temp) {

			cout << endl << "Voulez-vous afficher votre panier? (1 pour oui et 0 pour non): ";
			getline(cin, choix);

		}

		if (choix.length() == 1) {

			try {

				system("cls");

				convertirInt = stoi(choix);

				if (convertirInt == 1) {

					cout << endl << YELLOW << "--- Mon panier: ---" << endl;

					if (!(P.empty())) {

						for (auto& i : P)
							cout << endl << i;

						cout << RESET;

					}

					else
						cout << endl << "Votre panier est vide." << endl;

					temp = true;
					break;

				}

				else if (convertirInt == 0) 
					break;

			}

			catch (const exception& e) {

				cout << endl << RED << "--> Choix invalide, veuillez saisir 1 ou 0: " << RESET;
				getline(cin, choix);
				temp = true;

			}

		}

		else {

			cout << endl << RED << "--> Choix invalide, veuillez saisir 1 ou 0: " << RESET;
			getline(cin, choix);

		}

	} while (convertirInt != 1 || convertirInt != 0);
	
}

void Panier::lePlusCher() {

	double max = P[0].prix;

	for (auto& article : P) {

		if (article.prix > max) 

			max = article.prix;

	}

	if (!(P.empty())) {

		for (auto& article : P) {

			if (max == article.prix) {

				cout << endl << "L\'article le plus cher est: " << endl;
				cout << endl << article << endl;
				break;

			}

		}

	}

	else 

		cout << endl << "Votre panier est vide." << endl;

}

void Panier::articlesEntreMinMax(double min, double max) {

	for (auto& article : P) {

		if (article.prix >= min && article.prix <= max)
			cout << endl << article << endl;

	}

}

void Panier::infoArticles(string ref) {

	bool temp = false;

	for (auto& article : P) {

		if (article.reference == ref) {

			cout << endl << article << endl;
			temp = true;
			break;

		}

	}

	if (!temp)
		cout << endl << "L\'article que vous souhaiter afficher n\'existe pas dans votre panier." << endl;

}




// Classe Client:

Client::Client() : email(""), nom("") {}  // Constructeur par défaut 

Client::Client(string mail, string name) {  // Constructeur avec paramètres 

	email = mail;
	nom = name;

}

Client& Client::operator=(const Client& other) {  // Surcharge de l'opérateur =

	if (this != &other) {

		email = other.email;
		nom = other.nom;

	}

	return *this;
	
}



// Classe Commande:

Commande::Commande() : numero(0) {}  // Constructeur par défaut

Commande::Commande(int num) {  // Constructeur avec paramètres 

	numero = num;

}

void Commande::totalCmd(Panier& Pa) {

	double somme = 0; bool temp = false;

	for (auto& article : Pa.P) {

		if (article.quantite > 10) {
			somme += article.prix * 0.2;
			temp = true;
		}

		else
			somme += article.prix;

	}

	if (temp)
		cout << endl << "Le montant total de votre commande avec remise est: " << somme << " dhs." << endl;
	else
		cout << endl << "Le montant total de votre commande sans remise est: " << somme << " dhs." << endl;

}

