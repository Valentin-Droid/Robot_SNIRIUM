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
}

MainWindow::~MainWindow()
{
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
    //tcpSocket->write("Bonjour");
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
