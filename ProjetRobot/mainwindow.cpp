#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Instanciation de la socket
    tcpSocket = new QTcpSocket(this);

    // Attachement d'un slot qui sera appelé à chaque fois que des données arrivent (mode asynchrone)
    connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(gerer_donnees()));

    // Idem pour les erreurs
    connect(tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(afficher_erreur(QAbstractSocket::SocketError)));

    ui->Av->setFocus();

    //Fond du plan pour le dessin
    fondPlan = new QImage;
    fondPlan->load("/Users/etiennemeganck/Desktop/c++/Année 2/QtCreator/Robot_SNIRIUM/ProjetRobot/image-blanche.png");
    ui->Carte->setPixmap(QPixmap::fromImage(*fondPlan));

    //création d'un timer pour récupérer la trame
    pTimer = new QTimer;

    // Association du "tick" du timer à l'appel d'une méthode SLOT faire_qqchose()
    connect(pTimer, SIGNAL(timeout()), this, SLOT(demander_Trame()));
}

MainWindow::~MainWindow()
{
    // Arrêt du timer
    pTimer->stop();

    //Destruction du timer
    delete pTimer;

    //Desctruction de l'interface graphique
    delete fondPlan;

    // Destruction de la socket
    tcpSocket->abort();
    delete tcpSocket;

    // Destruction de l'interface graphique
    delete ui;
}

void MainWindow::on_SeConnecter_clicked()
{
    //Récupération des paramètres
    QString adresseIp = ui->RepIP->text();
    unsigned short port = ui->RepPort->text().toInt();

    //Connection
    tcpSocket->connectToHost(adresseIp, port);

    //test
    tcpSocket->write("OK");

    //Lancement du timer
    pTimer->start(2000);
}

void MainWindow::on_SeDeconnecter_clicked()
{
    //Deconnection
    tcpSocket->close();
}

QString MainWindow::Xor(QString trame)
{
    QString decoder;
    int key[9] = {2, 9, 8, 7, 1, 4, 6, 5, 3};

    for (int i = 0; i < trame.size(); i++)
    {
        QChar caractere(trame[i].toLatin1() ^ (key[i%9] + i) % 20);
        decoder += caractere;
    }

    return decoder;
}

void MainWindow::gerer_donnees()
{
    //Récupération des données
    QByteArray reponse = tcpSocket->readAll();
    QString trame = Xor(reponse);


    qDebug() << trame << "\n";
    qDebug() << trame.size() << "\n";

    //Découpage de la trame
    QStringList trameDecoupee = trame.split(";");

    qDebug() << trameDecoupee;

    if (trameDecoupee.size() >= 6)
    {
        //taux SNIRIUM
        unsigned short tauxSNIRIUM = trameDecoupee[0].toShort();
        ui->RepTauxSnirium->setText(QString("%1").arg(tauxSNIRIUM));
        //Angle
        short angle = trameDecoupee[1].toShort();
        if (angle > 360 || angle < -360)
        {
            angle = angle % 360;
        }
        ui->RepAngle->setText(QString("%1").arg(angle));

        //Batterie
        //trameDecoupee[2]

        //Distance
        float distance = trameDecoupee[3].toFloat();
        ui->RepPosition->setText(QString("%1").arg(distance));
        if (distance <= 10)
        {
            tcpSocket->write("S");
        }

        //Angle roue
        sauvegardeRoueG.push_back(trameDecoupee[4].toFloat());
        sauvegardeRoueD.push_back(trameDecoupee[5].toFloat());

        dessiner_Robot();
     }
}

void MainWindow::on_Av_clicked()
{
    qDebug()<<"a";
    tcpSocket->write("A");
}


void MainWindow::on_Ar_clicked()
{
    tcpSocket->write("R");
}


void MainWindow::on_Dr_clicked()
{
    tcpSocket->write("D");
}


void MainWindow::on_Ga_clicked()
{
    tcpSocket->write("G");
}


void MainWindow::on_St_clicked()
{
    tcpSocket->write("S");
}


void MainWindow::on_MonterBras_clicked()
{
    tcpSocket->write("L");
}


void MainWindow::on_BaisserBras_clicked()
{
    tcpSocket->write("B");
}

void MainWindow::dessiner_Robot()
{
    if (sauvegardeRoueG.size() >= 2)
    {
        //Roue
        int taille = sauvegardeRoueD.size();
        float roueG = sauvegardeRoueG[taille-1];
        float roueD = sauvegardeRoueD[taille-1];
        const unsigned short diametre_roue = 56;
        int angle = (ui->RepAngle->text()).toInt();

        double perimetre_roue = (2 * 3.14 * ( diametre_roue / 2 ) );

        double aMgMd = ( ( sauvegardeRoueG[taille-2] - roueG ) + ( sauvegardeRoueD[taille-2] - roueD ) ) / 2;
        double d = ( aMgMd * perimetre_roue ) / 360;
        double dx = d * cos( angle );
        double dy = d * sin( angle );

        int x2 = x1 + dx;
        int y2 = y1 + dy;

        x1 = x2;
        y1 = y2;

        //Préparation du fond du dessin
        QPainter p(fondPlan);

        if (taille >= 3)
        {
            //Efface le robot
            p.setBrush(QBrush(Qt::white));
            p.drawEllipse(x1, y1, 26, 26);
        }

        //Choix de la couleur
        p.setBrush(QBrush(Qt::black));

        //Dessin du robot
        p.drawEllipse(x2, y2, 25, 25);

        p.end();

        ui->Carte->setPixmap(QPixmap::fromImage(*fondPlan));

    }
}

void MainWindow::afficher_erreur(QAbstractSocket::SocketError socketError)
{
    switch (socketError)
    {
        case QAbstractSocket::RemoteHostClosedError:
            break;
        case QAbstractSocket::HostNotFoundError:
            QMessageBox::information(this, tr("Client TCP"),
                                     tr("Hôte introuvable"));
            break;
        case QAbstractSocket::ConnectionRefusedError:
            QMessageBox::information(this, tr("Client TCP"),
                                     tr("Connexion refusée"));
            break;
        default:
            QMessageBox::information(this, tr("Client TCP"),
                                     tr("Erreur : %1.")
                                     .arg(tcpSocket->errorString()));
    }
}

void MainWindow::demander_Trame()
{
    tcpSocket->write("T");
}

