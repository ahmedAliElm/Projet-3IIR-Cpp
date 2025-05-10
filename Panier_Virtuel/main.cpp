#include <iostream>
#include <sstream>
#include "Panier_virtuel.h"

using namespace std;

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"

int main() {

	int choix, qteStock = 100, quantiteSaisie = 0, newQt, l = 0, llll;
	bool test, temp = true, z;
	string ref, yaw, r;
	int sup{ 0 }, c;
	string qtee;
	Stock S;
	Article A;
	Panier monPanier;
	Commande C;

	S.remplirStock(A);
	S.afficherStock(); // si vou voulez afficher le stock

	cout << R"(                   _____            _        __      ___      _              _ 
                  |  __ \          (_)       \ \    / (_)    | |            | |
                  | |__) |_ _ _ __  _  ___ _ _\ \  / / _ _ __| |_ _   _  ___| |
                  |  ___/ _` | '_ \| |/ _ \ '__\ \/ / | | '__| __| | | |/ _ \ |
                  | |  | (_| | | | | |  __/ |   \  /  | | |  | |_| |_| |  __/ |
                  |_|   \__,_|_| |_|_|\___|_|    \/   |_|_|   \__|\__,_|\___|_|)" << endl;


	while (true) {

		c = menu();

		switch (c) {

		case 1:

			z = false;

			do {
				if (!z) {

					system("cls");
					cout << endl << "Veuillez saisir la reference de l\'article a ajouter dans votre panier: ";
					getline(cin, ref);

				}

				if (ref != "001" && ref != "002" && ref != "003" && ref != "004" && ref != "005") {

					cout << endl << RED << "--> Choix invalide, veuillez ressaisir: " << RESET;
					getline(cin, ref);
					z = true;

				}

			} while (ref != "001" && ref != "002" && ref != "003" && ref != "004" && ref != "005");

			for (const auto& elem : S.V) {

				if (ref == elem.reference) {
					qteStock = elem.quantite; // La quantité du produit commandé dans le stock
					break;
				}
			}

			cout << endl << "Veuillez saisir la quantite desiree: ";

			while (true) {

				getline(cin, qtee);

				// Si l'utilisateur n'a rien saisi

				if (qtee.empty()) {

					cout << endl << RED << "Veuillez saisir un nombre entier: " << RESET;
					continue;

				}

				// Vérifier que chaque caractère est int

				if (qtee.find_first_not_of("0123456789") != string::npos) {

					cout << endl << RED << "--> Veuillez saisir un nombre entier: " << RESET;
					continue;

				}

				// Convertir en int

				stringstream ss(qtee);
				ss >> quantiteSaisie;

				if (quantiteSaisie >= 1 && quantiteSaisie <= qteStock)
					break;
				else
					cout << endl << RED << "--> La quantite saisie doit etre comprise entre 1 et " << qteStock << ": " << RESET;
			}
				
			test = monPanier.ajouterArticle(ref, S, quantiteSaisie);

			if (test)
				S.diminuerQte(quantiteSaisie, S, ref); // Actualiser la quantité du produit dans le stock

			monPanier.afficherPanier();

			break;

		/**********************************************************************/

		case 2: 
				
			if (monPanier.P.empty()) {

				system("cls");
				cout << endl << "Votre panier est vide, veuillez le remplir avant d\'effectuer cette operation." << endl;
				break;

			}
				
			cout << endl << "Veuillez saisir la reference de l\'article: ";
			cin >> yaw;

			cout << endl << "Veuillez saisir la nouvelle quantite: ";
			cin >> newQt;
						
			for (auto& i : monPanier.P) {

				if (i.reference == yaw) {
					i.quantite = newQt;
					break;
				}

			}

			monPanier.afficherPanier();

			break;

		/**********************************************************************/

		case 3: 
				
			if (monPanier.P.empty()) {

				system("cls");
				cout << endl << "Votre panier est vide, veuillez le remplir avant d\'effectuer cette operation." << endl;
				break;

			}

			cout << endl << "Veuillez saisir la reference de l\'article a supprimer: ";
			cin >> yaw;

			for (auto& i : monPanier.P) {

				if (i.reference == yaw) {

					monPanier.P.erase(monPanier.P.begin() + l);
					cout << endl << MAGENTA << "--> Article supprime avec succes." << RESET << endl;
					sup = 1;

				}

				l++; 

			}

			if(sup == 0)
				cout << endl << "--> Article introuvable." << endl;

			monPanier.afficherPanier();

			break;

		/**********************************************************************/

		case 4:

			if (monPanier.P.empty()) {

				system("cls");
				cout << endl << "Votre panier est vide, veuillez le remplir avant d\'effectuer cette operation." << endl;
				break;

			}

			do {
				if (temp) {

					cout << endl << "Voulez-vous vraiment vider votre panier? (1 pour oui et 0 pour non): ";
					cin >> choix;

				}

				if (choix == 1) {

					monPanier.P.clear();
					cout << endl << "--> Votre panier est vide.";
					break;

				}

				else if (choix == 0) {
					break;
				}

				else {
					cout << endl << "Veuillez saisir un choix valide: ";
					cin >> choix;
					temp = false;
				}

				if (choix == 0 || choix == 1) {

					if (choix == 1) {

						monPanier.P.clear();
						cout << endl << "--> Votre panier est vide." << endl;

					}

					monPanier.afficherPanier();

				}

			} while (choix != 0 && choix != 1);

			break;

		/**********************************************************************/

		case 5:

			if (monPanier.P.empty()) {

				system("cls");
				cout << endl << "Votre panier est vide, veuillez le remplir avant d\'effectuer cette operation." << endl;
				break;

			}

			system("cls");

			C.totalCmd(monPanier);

			break;

		/**********************************************************************/

		case 6:

			if (monPanier.P.empty()) {

				system("cls");
				cout << endl << "Votre panier est vide, veuillez le remplir avant d\'effectuer cette operation." << endl;
				break;

			}

			system("cls");
			monPanier.lePlusCher(); 

			break;

		/**********************************************************************/
				
		case 7:

			if (monPanier.P.empty()) {

				system("cls");
				cout << endl << "Votre panier est vide, veuillez le remplir avant d\'effectuer cette operation." << endl;
				break;

			}

			double min, max;

			cout << endl << "Veuillez saisir le min puis le max: ";

			cin >> min;
			cin >> max;

			system("cls");

			monPanier.articlesEntreMinMax(min, max);

			break;

		/**********************************************************************/
				
		case 8:

			if (monPanier.P.empty()) {

				system("cls");
				cout << endl << "Votre panier est vide, veuillez le remplir avant d\'effectuer cette operation." << endl;
				break;

			}

			cout << endl << "Veuillez saisir la reference de l\'article: ";
			getline(cin, r);

			system("cls");
			monPanier.infoArticles(r);

			break;

		/**********************************************************************/

		case 9: exit(0);

		/**********************************************************************/

		default:
			cout << endl << "Veuillez saisir un choix valable!" << endl;

		}
	}

}

