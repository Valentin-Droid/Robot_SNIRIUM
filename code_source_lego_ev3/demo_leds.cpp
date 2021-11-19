/**
 * @file demo_leds.cpp
 * @brief Démonstration du fonctionnement des leds de l'EV3
 * @author David SALLE
 * @date 25/02/2019
 * @version 0.1
 *
 * Démonstration du fonctionnement des leds du robot Lego Mindstorm EV3
 * Méthodes de la classe Robot mises en oeuvre
 *   allumerLed()
 *   eteindreLed()
 *   attendre() 
 * Une première énumération permet de choisir l'emplacement de la led
 *   Robot::GAUCHE
 *   Robot::DROITE
 * Un seconde énumération permet de choisir la couleur de la led
 *   Robot::ROUGE
 *   Robot::VERTE
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


	// Boucle pour faire clignoter les leds
	for (int i=0; i<5; i++)
	{
		// On allume la led gauche rouge
		monRobot.allumerLed(Robot::GAUCHE, Robot::ROUGE);

		// Attente de 1000ms = 1s
		monRobot.attendre(1000);

		// On éteind la led droite rouge
		monRobot.eteindreLed(Robot::GAUCHE, Robot::ROUGE);

		// Attente de 1000ms = 1s
		monRobot.attendre(1000);
	}


	// Fin du programme
	return 0;
}
