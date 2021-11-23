/**
 * @file demo_ecran.cpp
 * @brief Démonstration du fonctionnement de l'écran LCD de l'EV3
 * @author David SALLE
 * @date 25/02/2019
 * @version 0.1
 *
 * Démonstration du fonctionnement de l'écran LCD du robot Lego Mindstorm EV3
 * Méthodes de la classe Robot mises en oeuvre
 *   allumerPixel()
 *   eteindrePixel()
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


    // Dessin d'un carré de 50x50 pixels en haut à gauche de l'écran
    for (int i=0; i<50; i++)
	{
		for (int j=0; j<50; j++)
		{
			monRobot.allumerPixel(i, i);
		}
	}

    // Attente de 5s pour avoir le temps de voir le résultat
	monRobot.attendre(5000);


	// Fin du programme
	return 0;
}
