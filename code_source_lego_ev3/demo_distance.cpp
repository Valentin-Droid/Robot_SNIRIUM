/**
 * @file demo_distance.cpp
 * @brief Démonstration du fonctionnement du capteur de distance de l'EV3
 * @author David SALLE
 * @date 25/02/2019
 * @version 0.1
 *
 * Démonstration du fonctionnement du capteur de distance (ultra-son) du robot Lego Mindstorm EV3
 * Méthodes de la classe Robot mises en oeuvre
 *   recupererDistance()
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


    // Pendant 10s on affiche l'état du capteur de distance
    for (int i=0; i<100; i++)
	{
		cout << "distance =>" << monRobot.recupererDistance() << " cm" << endl;
		monRobot.attendre(100);
	}


	// Fin du programme
	return 0;
}
