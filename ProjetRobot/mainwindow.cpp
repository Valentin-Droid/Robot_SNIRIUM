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

void MainWindow::gerer_donnees()
{
    //Récupération des données
    QByteArray reponse = tcpSocket->readAll();
    QString trame = reponse;

    //Découpage de la trame
    QStringList trameDecoupee = trame.split(";");

    if (trameDecoupee.size() >= 4)
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
        //Distance
        float distance = trameDecoupee[3].toFloat();
        ui->RepPosition->setText(QString("%1").arg(distance));
        if (distance <= 10)
        {
            tcpSocket->write("S");
        }
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

