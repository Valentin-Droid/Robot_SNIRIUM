/**
 * @file demo_angle.cpp
 * @brief Démonstration du fonctionnement du capteur d'angle de l'EV3
 * @author David SALLE
 * @date 25/02/2019
 * @version 0.1
 *
 * Démonstration du fonctionnement du capteur d'angle (gyroscopique) du robot Lego Mindstorm EV3
 * Méthodes de la classe Robot mises en oeuvre
 *   recupererGyroscopeAngle()
 *   attendre()
 */

// Librairies utilisées
#include <iostream>
#include "robot.h"

// Espaces de noms utilisés
using namespace std;


// Point d'entrée du programme
int main()
{
	// Instanciation de l'objet robot
	Robot monRobot;


	// Initialisation du gyroscope pour remettre la valeur à 0
	monRobot.initialiserGyroscope();

    // Pendant 10s on affiche l'état du capteur d'angle (gyroscopique)
    for (int i=0; i<100; i++)
	{
		cout << "angle => " << monRobot.recupererGyroscopeAngle() << " degrés" << endl;
		monRobot.attendre(100);
	}


	// Fin du programme
	return 0;
}
