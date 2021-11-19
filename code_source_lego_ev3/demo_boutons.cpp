/**
 * @file demo_boutons.cpp
 * @brief Démonstration du fonctionnement des boutons de l'EV3
 * @author David SALLE
 * @date 25/02/2019
 * @version 0.1
 *
 * Démonstration du fonctionnement des boutons du robot Lego Mindstorm EV3
 * Méthodes de la classe Robot mises en oeuvre
 *   recupererEtatBoutonHaut()
 *   recupererEtatBoutonBas()
 *   recupererEtatBoutonDroite()
 *   recupererEtatBoutonGauche()
 *   recupererEtatBoutonCentral()
 *   recupererEtatBoutonRetour()
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


    // Boucle pour tester les boutons pendant 5s
    for (int i=0; i<50; i++)
	{
		if (monRobot.recupererEtatBoutonHaut() == true)
		{
			cout << "Bouton [HAUT] enfoncé" << endl;
		}
		if (monRobot.recupererEtatBoutonBas() == true)
		{
			cout << "Bouton [BAS] enfoncé" << endl;
		}
		if (monRobot.recupererEtatBoutonDroite() == true)
		{
			cout << "Bouton [DROITE] enfoncé" << endl;
		}
		if (monRobot.recupererEtatBoutonGauche() == true)
		{
			cout << "Bouton [GAUCHE] enfoncé" << endl;
		}
		if (monRobot.recupererEtatBoutonCentral() == true)
		{
			cout << "Bouton [CENTRAL] enfoncé" << endl;
		}
		if (monRobot.recupererEtatBoutonRetour() == true)
		{
			cout << "Bouton [RETOUR] enfoncé" << endl;
		}

        // Attente de 100ms
		monRobot.attendre(100);
	}


	// Fin du programme
	return 0;
}
