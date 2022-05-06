#ifndef PANNEAULUMINEUX_H
#define PANNEAULUMINEUX_H

#include "header.h"

using namespace std;

#define MAX_TRAME       64

#define EOTsansRetour 0x04
#define EOTavecRetour 0x03 //OK sera envoyé par l'afficheur
#define NOIR '0'
#define ROUGE '1'
#define VERT '2'
#define ORANGE '3'
#define ArcEnCiel1 '4'
#define ArcEnCiel2 '5'
#define ArcEnCiel3 '6'
#define ArcEnCiel4 '7'

class PanneauLumineux {

public :

    PanneauLumineux();
    int afficher(QString message);
    int fabriquerTrame(char *trame, QString message);
    int envoyerTrame(char trame[MAX_TRAME]);


private :

    int i = 0;
    char couleur;
    QString str;
    char code[16];

};

#endif // PANNEAULUMINEUX_H
