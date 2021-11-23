/**
 * @file demo_son.cpp
 * @brief Démonstration du fonctionnement du son dans l'EV3
 * @author David SALLE
 * @date 25/02/2019
 * @version 0.1
 *
 * Démonstration du fonctionnement du son dans le robot Lego Mindstorm EV3
 * Méthodes de la classe Robot mises en oeuvre
 *   emettreSon()
 *   parler()
 *   lireFichierSon()
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


    // Le robot émet un son de fréquence 440Hz pendant 1000ms
    monRobot.emettreSon(440, 1000, true);

    // Le robot parle
	monRobot.parler("Hello world", true);

    // Le robot lit un fichier MP3 (préalablement téléversé dans le robot avec scp)
    monRobot.lireFichierSon("./meuh.mp3", true);


	// Fin du programme
	return 0;
}
