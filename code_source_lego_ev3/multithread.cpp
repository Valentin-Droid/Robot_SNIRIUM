// Librairies nécessaires
#include <iostream>
#include <sstream>
#include <unistd.h>
#include <cerrno>
#include <sys/un.h>
#include <arpa/inet.h>
#include "robot.hpp"
#include <string> 
#include <pthread.h>    // pour pthread_create() et pthread_join()


// Espace de nom utilisé
using namespace std;

// variable globale

// Instanciation de l'objet robot
Robot monRobot;

//chiffrage xor de la trame
string Xor(string trame)
{
    string encoder;
    char key[9] = {2,9,8,7,1,4,6,5,3};
    for (int i = 0 ; i < trame.size(); i++)
    {
       encoder += trame[i] ^ (int(key[i%9])+ i) % 20;
    }

    return encoder;
}

// fonction du thread robot
void *robot(void *parametre)
{
    // Initialisation des moteurs et des tachymètres à 0
	monRobot.initialiserMoteurs();

    // Initialisation du gyroscope
    monRobot.initialiserGyroscope();

    if(reponse[0] == 'A')
        {
            monRobot.changerPuissanceMoteurs(0, 0, 0);
            monRobot.changerPuissanceMoteurs(75, 0, 75);
        }else if(reponse[0] == 'R')
        {
            monRobot.changerPuissanceMoteurs(0, 0, 0);
            monRobot.changerPuissanceMoteurs(-75, 0, -75);
        }else if(reponse[0] == 'G')
        {
            monRobot.changerPuissanceMoteurs(0, 0, 0);
            monRobot.changerPuissanceMoteurs(-25, 0, 25);  
        }else if(reponse[0] == 'D')
        {
            monRobot.changerPuissanceMoteurs(0, 0, 0);
            monRobot.changerPuissanceMoteurs(25, 0, -25); 
        }else if(reponse[0] == 'S')
        {
            monRobot.changerPuissanceMoteurs(0, 0, 0);
        }else if(reponse[0] == 'L')
        {
            monRobot.changerPuissanceMoteurs(0, 0, 0);
            monRobot.changerPuissanceMoteurs(0, 30, 0);
            monRobot.attendre(1200);
            monRobot.changerPuissanceMoteurs(0, 0, 0);
        }else if(reponse[0] == 'B')
        {
            monRobot.changerPuissanceMoteurs(0, 0, 0);
            monRobot.changerPuissanceMoteurs(0, -30, 0);
            monRobot.attendre(1200);
            monRobot.changerPuissanceMoteurs(0, 0, 0);
        }else if(reponse[0] == 'P')
        {
            monRobot.parler("Fuck you", true);
        }else if(reponse[0] == 'T')
        {   
            ostringstream chaine ;
            chaine << monRobot.recupererLumiereReflechie() << ";" << monRobot.recupererGyroscopeAngle() << ";" << monRobot.recupererBatterieTension() << ";" << monRobot.recupererDistance() << ";" << monRobot.recupererPositionDuMoteur(Robot::GAUCHE) << ";" << monRobot.recupererPositionDuMoteur(Robot::DROITE);
            string trame = Xor(chaine.str());
            cout << trame << endl;
        }

}

//fonction du thread réseau
void *reseau(void *parametre)
{
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
    }
    // Création une file d'attente de connexion
    listen(sd_serveur, 5);
    while(1)
    {
        // Dès qu’un nouveau client se connecte à notre serveur,
        // une nouvelle socket est créée pour gérer le client
        int sd_client = accept(sd_serveur, NULL, NULL);

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
                send(sd_client, requete.c_str(), requete.size(), 0);
            }else if(reponse[0] == 'R')
            {
                send(sd_client, requete.c_str(), requete.size(), 0);
            }else if(reponse[0] == 'G')
            {
                send(sd_client, requete.c_str(), requete.size(), 0);
            }else if(reponse[0] == 'D')
            {
                send(sd_client, requete.c_str(), requete.size(), 0); 
            }else if(reponse[0] == 'S')
            {
                send(sd_client, requete.c_str(), requete.size(), 0);
            }else if(reponse[0] == 'L')
            {
                send(sd_client, requete.c_str(), requete.size(), 0);
            }else if(reponse[0] == 'B')
            {
                send(sd_client, requete.c_str(), requete.size(), 0);
            }else if(reponse[0] == 'P')
            {
                send(sd_client, requete.c_str(), requete.size(), 0);
            }else if(reponse[0] == 'T')
            {
                send(sd_client, trame.c_str(), trame.size(), 0);
            }
        }
        // Fermeture de la socket client
        close(sd_client);
    }
    // Fermeture de la socket serveur
    close(sd_serveur);
}

// Point d'entrée du programme
int main()
{
    // le thread réseau
    pthread_t thread_reseau;

    // le thread robot
    pthread_t thread_robot;

    // Creation de la thread réseau
    pthread_create(&thread_reseau, NULL, reseau, NULL);

    // Creation de la thread robot
    pthread_create(&thread_robot, NULL, robot, NULL);

    // Attente de la fin du thread réseau
    pthread_join(thread_reseau, NULL);

    // Attente de la fin du thread robot
    pthread_join(thread_robot, NULL);

    // Fin du programme
    return 0;
}  