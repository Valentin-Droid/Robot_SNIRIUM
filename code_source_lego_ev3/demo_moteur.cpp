/**
 * @file demo_moteur.cpp
 * @brief Démonstration du fonctionnement des moteurs de l'EV3
 * @author David SALLE
 * @date 25/02/2019
 * @version 0.1
 *
 * Démonstration du fonctionnement des moteurs du robot Lego Mindstorm EV3
 * Méthodes de la classe Robot mises en oeuvre
 *   changerPuissanceMoteurs()
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


	// Initialisation des moteurs et des tachymètres à 0
	monRobot.initialiserMoteurs();

	// Le robot tourne sur lui-même pendant 2s puis s'arrête
	monRobot.changerPuissanceMoteurs(100, 0, -100);
	monRobot.attendre(2000);
	monRobot.changerPuissanceMoteurs(0, 0, 0);


	// Fin du programme
	return 0;
}
