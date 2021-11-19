/**
 * @file robot.cpp
 * @brief Implémentation de la classe Robot
 * @author David SALLE
 * @date 25/02/2010
 * @version 0.2
 *
 * Cette classe Robot formera une sur-couche à l'ensemble des classes ev3dev
 * et facilitera ainsi le développement des programmes pour les "challenges"
 */

// Librairies utilisées
#include "robot.hpp"


//==============================================================================
// Méthodes constructeur et desctructeur
//==============================================================================
Robot::Robot()
{
	
	// Instanciations dynamiques des objets "moteurs" selon leurs ports de sortie respectifs
	pMoteurGauche = new large_motor("ev3-ports:outA");			// "outA"
	pMoteurCentral = new medium_motor("ev3-ports:outB");	// "outB"
	pMoteurDroit = new large_motor("ev3-ports:outC");			// "outC"

	// Vérifications de la présence des moteurs
	if (pMoteurGauche->connected() == false)
	{
		cout << "ERREUR => Le moteur gauche ne semble pas présent (port A)" << endl;
	}
	if (pMoteurCentral->connected() == false)
	{
		cout << "ERREUR => Le moteur central ne semble pas présent (port B)" << endl;
	}
	if (pMoteurDroit->connected() == false)
	{
		cout << "ERREUR => Le moteur droit ne semble pas présent (port C)" << endl;
	}

	// Initialisations des moteurs
	initialiserMoteurs();
	
	// Vérification de la présence des capteurs
	if (capteurAngle.connected() == false)
	{
		cout << "ERREUR => Le capteur d'angle ne semble pas présent" << endl;
	}
	else
	{
		initialiserGyroscope();
	}

	if (capteurContact.connected() == false)
	{
		cout << "ERREUR => Le capteur de contact ne semble pas présent" << endl;
	}
	if (capteurCouleur.connected() == false)
	{
		cout << "ERREUR => Le capteur de couleur ne semble pas présent" << endl;
	}
	if (capteurDistance.connected() == false)
	{
		cout << "ERREUR => Le capteur de distance ne semble pas présent" << endl;
	}
}


Robot::~Robot()
{
	// Destruction des objets "moteurs"
	delete pMoteurGauche;
	delete pMoteurCentral;
	delete pMoteurDroit;
}


//==============================================================================
// Méthodes utilitaires
//==============================================================================
void Robot::attendre(int delai_en_millisecondes)
{
	this_thread::sleep_for(chrono::milliseconds(delai_en_millisecondes));
}


//==============================================================================
// Méthodes pour gérer le gyroscope
//==============================================================================
int Robot::recupererGyroscopeAngle()
{
	return capteurAngle.angle();
}


int Robot::recupererGyroscopeVitesse()
{
	return capteurAngle.rate();
}


void Robot::initialiserGyroscope()
{
	capteurAngle.set_mode(capteurAngle.mode_gyro_cal);
	capteurAngle.set_mode(capteurAngle.mode_gyro_ang);
}


//==============================================================================
// Méthodes pour gérer le capteur de contact
//==============================================================================
bool Robot::recupererEtatCapteurContact()
{
	return capteurContact.is_pressed();
}


//==============================================================================
// Méthodes pour gérer le capteur de couleur
//==============================================================================
int Robot::recupererLumiereReflechie()
{
	return capteurCouleur.reflected_light_intensity();
}

int Robot::recupererLumiereAmbiante()
{
	return capteurCouleur.ambient_light_intensity();
}

int Robot::recupererCouleurCode()
{
	return capteurCouleur.color();
}

int Robot::recupererCouleurRouge()
{
	return capteurCouleur.red();
}

int Robot::recupererCouleurVerte()
{
	return capteurCouleur.green();
}

int Robot::recupererCouleurBleue()
{
	return capteurCouleur.blue();
}


//==============================================================================
// Méthodes pour gérer le capteur de distance (ultrason)
//==============================================================================
float Robot::recupererDistance()
{
	return capteurDistance.distance_centimeters();
}


//==============================================================================
// Méthodes pour gérer la batterie
//==============================================================================
float Robot::recupererBatterieTension()
{
	return power_supply::battery.measured_volts();
}

float Robot::recupererBatterieIntensite()
{
	return power_supply::battery.measured_amps();
}


//==============================================================================
// Méthodes pour gérer l'écran LCD
//==============================================================================
void Robot::allumerPixel(int x, int y)
{
	if ( (x >= 0) && (x < 178) && (y >= 0) && (y < 128) )
	{
		unsigned char *pFB = ecran.frame_buffer();
		pFB[(x / 8) + (y * 24)] = 1 << (x % 8);
	}
}

void Robot::eteindrePixel(int x, int y)
{
	if ( (x >= 0) && (x < 178) && (y >= 0) && (y < 128) )
	{
		unsigned char *pFB = ecran.frame_buffer();
		pFB[(x / 8) + (y * 24)] = 0 << (x % 8);
	}
}


//==============================================================================
// Méthodes pour gérer les boutons
//==============================================================================
bool Robot::recupererEtatBoutonHaut()
{
	return button::up.pressed();
}

bool Robot::recupererEtatBoutonBas()
{
	return button::down.pressed();
}

bool Robot::recupererEtatBoutonDroite()
{
	return button::right.pressed();
}

bool Robot::recupererEtatBoutonGauche()
{
	return button::left.pressed();
}

bool Robot::recupererEtatBoutonCentral()
{
	return button::enter.pressed();
}

bool Robot::recupererEtatBoutonRetour()
{
	return button::back.pressed();
}


//==============================================================================
// Méthodes pour gérer les leds
//==============================================================================
void Robot::allumerLed(Emplacement e, Couleur c)
{
	if ( (e == GAUCHE) && (c == ROUGE) )
	{
		led::red_left.on();
	}
	if ( (e == GAUCHE) && (c == VERTE) )
	{
		led::green_left.on();
	}
	if ( (e == DROITE) && (c == ROUGE) )
	{
		led::red_right.on();
	}
	if ( (e == DROITE) && (c == VERTE) )
	{
		led::green_right.on();
	}
}

void Robot::eteindreLed(Emplacement e, Couleur c)
{
	if ( (e == GAUCHE) && (c == ROUGE) )
	{
		led::red_left.off();
	}
	if ( (e == GAUCHE) && (c == VERTE) )
	{
		led::green_left.off();
	}
	if ( (e == DROITE) && (c == ROUGE) )
	{
		led::red_right.off();
	}
	if ( (e == DROITE) && (c == VERTE) )
	{
		led::green_right.off();
	}
}


//==============================================================================
// Méthodes pour gérer le son
//==============================================================================
void Robot::emettreSon(float frequence, float duree, bool synchrone)
{
	sound::tone(frequence, duree, synchrone);
}

void Robot::parler(string phrase, bool synchrone)
{
	sound::speak(phrase, synchrone);
}

void Robot::lireFichierSon(string nomFichier, bool synchrone)
{
	sound::play(nomFichier, synchrone);
}


//==============================================================================
// Méthodes pour gérer les moteurs
//==============================================================================
void Robot::initialiserMoteurs()
{
	// Ré-initialisation des 3 moteurs
	pMoteurGauche->reset();
	pMoteurCentral->reset();
	pMoteurDroit->reset();
}

void Robot::changerPuissanceMoteurs(int puissanceGauche, int puissanceCentrale, int puissanceDroite)
{
	// Seuillage des puissances (au cas où)
	if (puissanceGauche < -100)
	{
		puissanceGauche = -100;
	}
	if (puissanceCentrale < -100)
	{
		puissanceCentrale = -100;
	}
	if (puissanceDroite < -100)
	{
		puissanceDroite = -100;
	}
	if (puissanceGauche > 100)
	{
		puissanceGauche = 100;
	}
	if (puissanceCentrale > 100)
	{
		puissanceCentrale = 100;
	}
	if (puissanceDroite > 100)
	{
		puissanceDroite = 100;
	}

	// Modification de la puissance des moteurs...
	pMoteurGauche->set_duty_cycle_sp(puissanceGauche);
	pMoteurCentral->set_duty_cycle_sp(puissanceCentrale);
	pMoteurDroit->set_duty_cycle_sp(puissanceDroite);

	// ...et application
	pMoteurGauche->run_direct();
	pMoteurDroit->run_direct();
	pMoteurCentral->run_direct();
}

int Robot::recupererPositionDuMoteur(Emplacement e)
{
	if (e == GAUCHE)
	{
		return pMoteurGauche->position();
	}
	if (e == CENTRE)
	{
		return pMoteurCentral->position();
	}
	if (e == DROITE)
	{
		return pMoteurDroit->position();
	}
}

void Robot::recupererPositionsDesMoteurs(int &positionGauche, int &positionCentre, int &positionDroite)
{
	positionGauche = pMoteurGauche->position();
	positionCentre = pMoteurCentral->position();
	positionDroite = pMoteurDroit->position();
}
