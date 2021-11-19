/**
 * @file demo_tachy.cpp
 * @brief Démonstration du fonctionnement des tachymètres des moteurs de l'EV3
 * @author David SALLE
 * @date 25/02/2019
 * @version 0.1
 *
 * Démonstration du fonctionnement des tachymètres des moteurs du robot Lego Mindstorm EV3
 * Méthodes de la classe Robot mises en oeuvre
 *   changerPuissanceMoteurs()
 *   recupererPositionDuMoteur()
 *   recupererPositionsDesMoteurs()
 *   attendre()
 * Une énumération permet de choisir le moteur dont on souhaite connaître la position
 *   Robot::GAUCHE
 *   Robot::CENTRE
 *   Robot::DROITE
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


    // Affichage de la position des 3 moteurs (1ère solution)
    cout << "MG => " << monRobot.recupererPositionDuMoteur(Robot::GAUCHE) << " ";
	cout << "MC => " << monRobot.recupererPositionDuMoteur(Robot::CENTRE) << " ";
	cout << "MD => " << monRobot.recupererPositionDuMoteur(Robot::DROITE) << endl;

    // Le robot bouge
	monRobot.changerPuissanceMoteurs(100, 50, -100);
	monRobot.attendre(1000);
	monRobot.changerPuissanceMoteurs(0, 0, 0);

    // Affichage de la position des 3 moteurs (2nde solution)
    int positionFinaleGauche = 0;
    int positionFinaleCentrale = 0;
    int positionFinaleDroite = 0;
    monRobot.recupererPositionsDesMoteurs(positionFinaleGauche, positionFinaleCentrale, positionFinaleDroite);
	cout << "MG => " << positionFinaleGauche << " ";
	cout << "MC => " << positionFinaleCentrale << " ";
	cout << "MD => " << positionFinaleDroite << endl;


	// Fin du programme
	return 0;
}
