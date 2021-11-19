/**
 * @file robot.h
 * @brief Définition de la classe Robot
 * @author David SALLE
 * @date 25/02/2019
 * @version 0.2
 *
 * Cette classe Robot formera une sur-couche à l'ensemble des classes ev3dev
 * et facilitera ainsi le développement des programmes pour  les "challenges"
 */
#ifndef ROBOT_H
#define ROBOT_H

// Librairies utilisées
#include <iostream>
#include <chrono>
#include <thread>
#include "ev3dev.h"

// Espaces de noms utilisés
using namespace std;
using namespace ev3dev;


// Définition de la classe
class Robot
{
public:
	/**
	 * Méthode constructeur pour initialiser l'objet Robot
	 * @param aucun
	 * @return rien
	 *
	 * La méthode vérifie la présence de tous les capteurs et actionneurs
	 * et signale d'éventuels problème par un message sur la console
	 */
	Robot();

	/**
	 * Méthode destructeur
	 * @param aucun
	 * @return rien
	 */
	~Robot();



	/**
	 * Méthode pour attendre pendant un certain temps exprimé en millisecondes
	 * @param delai_en_millisecondes
	 * @return rien
	 */
	void attendre(int delai_en_millisecondes);



	 /**
 	 * Méthode pour initialiser le capteur gyroscopique et remettre l'angle à 0
 	 * @param aucun
 	 * @return rien
 	 */
 	void initialiserGyroscope();

	/**
	 * Méthode pour récupérer l'angle issu du capteur gyroscopique
	 * @param aucun
	 * @return l'angle du robot
	 */
	int recupererGyroscopeAngle();

	/**
	 * Méthode pour récupérer la vitesse angulaire issue du capteur gyroscopique
	 * @param aucun
	 * @return la vitesse angulaire du robot
	 */
	int recupererGyroscopeVitesse();



	/**
	 * Méthode pour récupérer l'état du capteur de contact
	 * @param aucun
	 * @return true si le capteur est enfoncé, false sinon
	 */
	bool recupererEtatCapteurContact();



	/**
	 * Méthode pour récupérer la lumière réfléchie issue du capteur de couleur
	 * @param aucun
	 * @return la lumière réfléchie (0=noir à 100=blanc)
	 */
	int recupererLumiereReflechie();

	/**
	 * Méthode pour récupérer la lumière ambiante issue du capteur de couleur
	 * @param aucun
	 * @return la lumière ambiante (0=noir à 100=blanc)
	 */
	int recupererLumiereAmbiante();

	/**
	 * Méthode pour récupérer la couleur mesurée par le capteur de couleur
	 * @param aucun
	 * @return la couleur (0=inconnue, 1=black, 2=blue, 3=green, 4=yellow, 5=red 6=white, 7=brown)
	 */
	int recupererCouleurCode();

	/**
	 * Méthode pour récupérer la composante rouge mesurée par le capteur de couleur
	 * @param aucun
	 * @return la composante rouge mesurée par le capteur (0 à 1020)
	 */
	int recupererCouleurRouge();

	/**
	 * Méthode pour récupérer la composante verte mesurée par le capteur de couleur
	 * @param aucun
	 * @return la composante verte mesurée par le capteur (0 à 1020)
	 */
	int recupererCouleurVerte();

	/**
	 * Méthode pour récupérer la composante bleue mesurée par le capteur de couleur
	 * @param aucun
	 * @return la composante bleue mesurée par le capteur (0 à 1020)
	 */
	int recupererCouleurBleue();



	/**
	 * Méthode pour récupérer la distance mesurée en centimètres
	 * @param aucun
	 * @return la distance en centimètres
	 */
	float recupererDistance();



	/**
	 * Méthode pour récupérer la tension dans la batterie
	 * @param aucun
	 * @return la tension en Volts
	 */
	float recupererBatterieTension();

	/**
	 * Méthode pour récupérer l'intensité dans la batterie
	 * @param aucun
	 * @return l'intensité en Ampères
	 */
	float recupererBatterieIntensite();



	/**
	 * Méthode pour allumer un pixel de l'écran en x,y
	 * @param x
	 * @param y
	 * @return rien
	 */
	void allumerPixel(int x, int y);

	/**
	 * Méthode pour éteindre un pixel de l'écran en x,y
	 * @param x
	 * @param y
	 * @return rien
	 */
	void eteindrePixel(int x, int y);



	/**
	 * Méthode pour récupérer l'état du bouton du haut
	 * @param aucun
	 * @return true si le bouton est enfoncé, false sinon
	 */
	bool recupererEtatBoutonHaut();

	/**
	 * Méthode pour récupérer l'état du bouton du bas
	 * @param aucun
	 * @return true si le bouton est enfoncé, false sinon
	 */
	bool recupererEtatBoutonBas();

	/**
	 * Méthode pour récupérer l'état du bouton de droite
	 * @param aucun
	 * @return true si le bouton est enfoncé, false sinon
	 */
	bool recupererEtatBoutonDroite();

	/**
	 * Méthode pour récupérer l'état du bouton de gauche
	 * @param aucun
	 * @return true si le bouton est enfoncé, false sinon
	 */
	bool recupererEtatBoutonGauche();

	/**
	 * Méthode pour récupérer l'état du bouton central
	 * @param aucun
	 * @return true si le bouton est enfoncé, false sinon
	 */
	bool recupererEtatBoutonCentral();

	/**
	 * Méthode pour récupérer l'état du bouton retour
	 * @param aucun
	 * @return true si le bouton est enfoncé, false sinon
	 */
	bool recupererEtatBoutonRetour();



	/**
	 * Enumération pour représenter l'emplacement d'une led/moteur du robot
	 *   GAUCHE=0
	 *   CENTRE=1
	 *   DROITE=2
	 */
	enum Emplacement { GAUCHE, CENTRE, DROITE };

	/**
	 * Enumération pour représenter la couleur d'une led du robot
	 *   ROUGE=0
	 *   VERTE=1
	 */
	enum Couleur { ROUGE, VERTE };

	/**
	 * Méthode pour allumer une led
	 * @param e emplacement de la led (GAUCHE ou DROITE)
	 * @param c couleur de la led (ROUGE ou VERTE)
	 * @return rien
	 */
	void allumerLed(Emplacement e, Couleur c);

	/**
	 * Méthode pour éteindre une led
	 * @param e emplacement de la led (GAUCHE ou DROITE)
	 * @param c couleur de la led (ROUGE ou VERTE)
	 * @return rien
	 */
	void eteindreLed(Emplacement e, Couleur c);



	/**
	 * Méthode pour émettre un son
	 * @param frequence du son en Hertz
	 * @param durée du son en millisecondes
	 * @param synchrone : true=robot bloqué pendant son, false=robot peut faire autre chose pendant son
	 * @return rien
	 */
	void emettreSon(float frequence, float duree, bool synchrone);

	/**
	 * Méthode pour faire parler le robot (avec une accent anglophone)
	 * @param phrase à prononcer
	 * @param synchrone : true=robot bloqué pendant son, false=robot peut faire autre chose pendant son
	 * @return rien
	 */
	void parler(string phrase, bool synchrone);

	/**
	 * Méthode pour émettre un son
	 * @param nomFichier à lire. Format MP3 accepté. Il faut téléverser le fichier MP3 dans le robot
	 * @param synchrone : true=robot bloqué pendant son, false=robot peut faire autre chose pendant son
	 * @return rien
	 *
	 * Pour téléverser un fichier MP3 dans le robot on pourra utiliser la commande scp :
	 * $ scp meuh.mp3 robot@192.168.0.167:/home/robot/snir1/
	 */
	void lireFichierSon(string nomFichier, bool synchrone);



	/**
	 * Méthode pour initialiser les moteurs
	 * @param aucun
	 * @return rien
	 */
	void initialiserMoteurs();

	/**
     * Méthode pour changer la puissance des 3 moteurs
	 * @param gauche puissance du moteur gauche (-100 à 100)
	 * @param centrale puissance du moteur central (-100 à 100)
	 * @param droite puissance du moteur droit (-100 à 100)
	 * @return rien
	 *
	 * L'utilisation des moteurs ce cette manière permet de faire autre chose
	 * en même temps (lire capteurs, faire calculs...) car le changement est très bref.
	 * Les valeurs des puissances en pourcentage sont seuillées entre -100 et 100
	 *
	 * Les emplacements des moteurs gauche et droit s'entendent avec le robot
	 * positionné face à vous, boule directionnelle de votre côté et écran
	 * lisible facilement (à l'endroit)
	 */
	void changerPuissanceMoteurs(int gauche, int centrale, int droite);

	/**
	 * Méthode pour récupérer la position d'un moteur
	 * @param moteur (GAUCHE, CENTRE ou DROITE)
	 * @return la position en degrés
	 */
	int recupererPositionDuMoteur(Emplacement e);

	/**
	 * Méthode pour récupérer les positions des 3 moteurs
	 * @param positionGauche (passée par référence pour pouvoir récupérer la valeur)
	 * @param positionCentre (passée par référence pour pouvoir récupérer la valeur)
	 * @param positionDroite (passée par référence pour pouvoir récupérer la valeur)
	 * @return rien
	 */
	void recupererPositionsDesMoteurs(int &positionGauche, int &positionCentre, int &positionDroite);



private:
	// Attributs capteurs
	gyro_sensor capteurAngle;			// sur port 4
	touch_sensor capteurContact;		// sur port 1
	color_sensor capteurCouleur;		// sur port 3
	ultrasonic_sensor capteurDistance;	// sur port 2

	// Attributs écran
	lcd ecran;

	// Attributs moteurs (voir constructeur)
	large_motor *pMoteurGauche;		// sur port A
	large_motor *pMoteurDroit;		// sur port C
	medium_motor *pMoteurCentral;	// sur port B
};


#endif
