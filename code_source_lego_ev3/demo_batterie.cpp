/**
 * @file demo_batterie.cpp
 * @brief Démonstration du fonctionnement de la batterie de l'EV3
 * @author David SALLE
 * @date 25/02/2019
 * @version 0.1
 *
 * Démonstration du fonctionnement de la batterie du robot Lego Mindstorm EV3
 * Méthodes de la classe Robot mises en oeuvre
 *   recupererBatterieTension()
 *   recupererBatterieIntensite()
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


    // Affichage de l'état de la batterie
    cout << "tension=" << monRobot.recupererBatterieTension() << " V" << endl;
	cout << "intensite=" << monRobot.recupererBatterieIntensite() << " A" << endl;


	// Fin du programme
	return 0;
}
