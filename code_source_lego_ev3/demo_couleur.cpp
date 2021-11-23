/**
 * @file demo_couleur.cpp
 * @brief Démonstration du fonctionnement du capteur de couleur de l'EV3
 * @author David SALLE
 * @date 25/02/2019
 * @version 0.1
 *
 * Démonstration du fonctionnement du capteur de couleur du robot Lego Mindstorm EV3
 * Méthodes de la classe Robot mises en oeuvre
 *   recupererLumiereReflechie()
 *   recupererLumiereAmbiante()
 *   recupererCouleurCode()
 *   recupererCouleurRouge()
 *   recupererCouleurVerte()
 *   recupererCouleurBleue()
 *   attendre 
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


    // Pendant 10s on affiche l'état du capteur de couleur
    for (int i=0; i<100; i++)
	{
		cout << "reflechie => " << monRobot.recupererLumiereReflechie() << " ";
		cout << "ambiante => " << monRobot.recupererLumiereAmbiante() << " ";
		cout << "code couleur => " << monRobot.recupererCouleurCode() << " ";
		cout << "R => " << monRobot.recupererCouleurRouge() << " ";
		cout << "V => " << monRobot.recupererCouleurVerte() << " ";
		cout << "B => " << monRobot.recupererCouleurBleue() << " ";
		cout << endl;
		monRobot.attendre(100);
	}


	// Fin du programme
	return 0;
}
