/**
 * @file demo_contact.cpp
 * @brief Démonstration du fonctionnement du capteur de contact de l'EV3
 * @author David SALLE
 * @date 25/02/2019
 * @version 0.1
 *
 * Démonstration du fonctionnement du capteur de contact du robot Lego Mindstorm EV3
 * Méthodes de la classe Robot mises en oeuvre
 *   recupererEtatCapteurContact()
 *   attendre()
 */

// Librairies utilisées
#include <iostream>
#include "robot.hpp"

// Espaces de noms utilisés
using namespace std;


// Point d'entrée du programme
int main()
{
	// Instanciation de l'objet robot
	Robot monRobot;


    // Pendant 5s on affiche l'état du capteur de contact
    for (int i=0; i<50; i++)
	{
		if (monRobot.recupererEtatCapteurContact() == true)
		{
			cout << "enfoncé" << endl;
		}
		else
		{
			cout << "relâché" << endl;
		}
		monRobot.attendre(100);
	}


	// Fin du programme
	return 0;
}
