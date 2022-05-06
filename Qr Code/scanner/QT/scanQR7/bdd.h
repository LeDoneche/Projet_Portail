#ifndef BDD_H
#define BDD_H

#include "header.h"

using namespace std;

class BDD {

    QSqlDatabase db;
    QSqlQuery query ;
    int verifChampBdd;
    int calculPlace;

public:

    BDD(QString AddData , QString Host , QString User , QString Password , QString Name);
    int VerifQR(string qr);
    int VerifNbPlace(string qr);
    void MajPlace(string qr);
    int NbPlaces();

    int nbPlace;

};

#endif // BDD_H
