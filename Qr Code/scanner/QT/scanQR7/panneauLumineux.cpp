#include "PanneauLumineux.h"

using namespace std;

PanneauLumineux::PanneauLumineux() {

}

int PanneauLumineux::envoyerTrame(char trame[MAX_TRAME]) {
    QUdpSocket *socket;
    // connexion au panneau lumineux
    socket = new QUdpSocket();
    socket-> bind(QHostAddress("172.20.233.19"), 9520);
    socket->writeDatagram(trame, QHostAddress("172.20.233.19"), 9520 );
    socket->close();
    return 0;
}

int PanneauLumineux::fabriquerTrame(char *trame, QString message) {
    couleur = ArcEnCiel3;

    char tramePrefixe[MAX_TRAME] = {0x01,'Z','0','0',0x02};

    char trameOPt[MAX_TRAME] = {'A','A',0x06,0x0E,'0','0','0',0x0F,'0',0x0A,'I','0',0x0A,'O','0',0x1C,couleur,0x1A,'1',0x1E,'1'};

    // on concatène les trames
    sprintf(trame, "%s%s", tramePrefixe,trameOPt);

    // on concatène le texte dans la trame
    strcat(trame, message.toLatin1());

    // on termine la trame
    i = strlen(trame);

    trame[i] = 0x04;

    //Pour le Debug
    char code[16];
    QString trameHexa = "";
    for(i = 0; i < (int)strlen(trame)-1; i++)
    {
        sprintf(code, "0x%02X ", trame[i]);
        trameHexa += code;

    }
    sprintf(code, "0x%02X", trame[i]);
    trameHexa += code;
    //qDebug() << Q_FUNC_INFO << "-> trame : " << trameHexa;
    //Fin Debug

    return 0;

}

int PanneauLumineux::afficher(QString message) {
    char trame[MAX_TRAME] = {0x04};

    //qDebug() << Q_FUNC_INFO << "-> message : " ;

    // on fabrique la trame
    fabriquerTrame(&trame[0], message);
    // on envoie la trame
    envoyerTrame(trame);

    return 0;
}


