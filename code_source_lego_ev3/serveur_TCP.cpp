// Librairies nécessaires
#include <iostream>
#include <sstream>
#include <unistd.h>
#include <cerrno>
#include <sys/un.h>
#include <arpa/inet.h>
#include "robot.hpp"
#include <string> 

// Espace de nom utilisé
using namespace std;

// Point d'entrée du programme
int main()
{
    // Instanciation de l'objet robot
	Robot monRobot;

    // Initialisation des moteurs et des tachymètres à 0
	monRobot.initialiserMoteurs();

    // Création de la socket serveur
    int sd_serveur = socket(AF_INET, SOCK_STREAM, 0);

    // Configuration de la socket, notamment le port d'écoute
    struct sockaddr_in cfg_serveur;
    cfg_serveur.sin_family = AF_INET;
    cfg_serveur.sin_addr.s_addr = htonl(INADDR_ANY);
    cfg_serveur.sin_port = htons(1665);

    // Attachement de la socket au port défini
    int resultat = bind(sd_serveur, (struct sockaddr *)&cfg_serveur, sizeof(cfg_serveur));
    if( resultat <0)
    {
        cout << "Erreur de port" << endl;
        return -1;
    }
    

    // Création une file d'attente de connexion
    listen(sd_serveur, 5);
    while(1)
    {
        // Dès qu’un nouveau client se connecte à notre serveur,
        // une nouvelle socket est créée pour gérer le client
        int sd_client = accept(sd_serveur, NULL, NULL);

        monRobot.initialiserGyroscope();


        while(1)
        {
            // Réception de la requête du client
            char buffer[1024];
            memset(buffer, 0x00, 1024);
            int nbOctets = recv(sd_client, buffer, sizeof(buffer), 0);
            string reponse(buffer);
            cout << reponse << endl;

            // Envoi de la réponse au client
            string requete = "ok";

            if(reponse[0] == 'A')
            {
                monRobot.changerPuissanceMoteurs(0, 0, 0);
                monRobot.changerPuissanceMoteurs(75, 0, 75);
                send(sd_client, requete.c_str(), requete.size(), 0);
            }else if(reponse[0] == 'R')
            {
                monRobot.changerPuissanceMoteurs(0, 0, 0);
                monRobot.changerPuissanceMoteurs(-75, 0, -75);
                send(sd_client, requete.c_str(), requete.size(), 0);
            }else if(reponse[0] == 'G')
            {
                monRobot.changerPuissanceMoteurs(0, 0, 0);
                monRobot.changerPuissanceMoteurs(-25, 0, 25);  
                send(sd_client, requete.c_str(), requete.size(), 0);
            }else if(reponse[0] == 'D')
            {
                monRobot.changerPuissanceMoteurs(0, 0, 0);
                monRobot.changerPuissanceMoteurs(25, 0, -25); 
                send(sd_client, requete.c_str(), requete.size(), 0); 
            }else if(reponse[0] == 'S')
            {
                monRobot.changerPuissanceMoteurs(0, 0, 0);
                send(sd_client, requete.c_str(), requete.size(), 0);
            }else if(reponse[0] == 'L')
            {
                monRobot.changerPuissanceMoteurs(0, 0, 0);
                monRobot.changerPuissanceMoteurs(0, 30, 0);
                monRobot.attendre(1200);
                monRobot.changerPuissanceMoteurs(0, 0, 0);
                send(sd_client, requete.c_str(), requete.size(), 0);
            }else if(reponse[0] == 'B')
            {
                monRobot.changerPuissanceMoteurs(0, 0, 0);
                monRobot.changerPuissanceMoteurs(0, -30, 0);
                monRobot.attendre(1200);
                monRobot.changerPuissanceMoteurs(0, 0, 0);
                send(sd_client, requete.c_str(), requete.size(), 0);
            }else if(reponse[0] == 'P')
            {
                monRobot.parler("Fuck you", true);
                send(sd_client, requete.c_str(), requete.size(), 0);
            }else if(reponse[0] == 'T')
            {   ostringstream chaine ;
                chaine << monRobot.recupererLumiereReflechie() << ";" << monRobot.recupererGyroscopeAngle() << ";" << monRobot.recupererBatterieTension() << ";" << monRobot.recupererDistance() << ";" << monRobot.recupererPositionDuMoteur(Robot::GAUCHE) << "," << monRobot.recupererPositionDuMoteur(Robot::CENTRE) << "," << monRobot.recupererPositionDuMoteur(Robot::DROITE) << endl;
                string trame = chaine.str();
                cout << trame << endl;
                send(sd_client, trame.c_str(), trame.size(), 0);
            }
            
        }
        // Fermeture de la socket client
        close(sd_client);
    }
    // Fermeture de la socket serveur
    close(sd_serveur);

    // Fin du programme
    return 0;
}  