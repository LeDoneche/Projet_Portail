#include "bdd.h"

using namespace std;

// constructeur
BDD::BDD(QString AddData , QString Host , QString User , QString Password , QString Name){

    db = QSqlDatabase::addDatabase(AddData);
    db.setHostName(Host);
    db.setUserName(User);
    db.setPassword(Password);
    db.setDatabaseName(Name);
}

int BDD::VerifQR(string qr) {

    if(db.open()){
        QSqlDatabase::database().transaction();
        query.exec(QString::fromStdString("SELECT QR FROM Personnel WHERE QR = '" + qr + "';"));
        verifChampBdd = query.numRowsAffected(); // verif si le champ existe
        if( verifChampBdd > 0) {
            // qr existe dans la bdd;
            return 1;
        } else {
            // qr n'existe pas
            return 0;
        }
    } else {
        qDebug() << "probleme ouverture bdd";
    }
}

int BDD::VerifNbPlace(string qr) {
    if (VerifQR(qr) == 1){
        if (db.open()){
            query.exec("SELECT NbPlace FROM Parking");
            if (query.next()) {
                //- Verification qu le nb de place est sup a 0 -//
                if ( query.value(0).toInt() > 0 ){
                    // place dispo dans le parking
                    return 1;
                } else {
                    // Attention plus de place dans le parking
                    return 0;
                }
            }
        } else {
            qDebug() << "probleme ouverture bdd";
        }
    }
}

void BDD::MajPlace(string qr) {
    if (db.open()){
        if (VerifNbPlace(qr) == 1){
            calculPlace = query.value(0).toInt();
            calculPlace = calculPlace - 1 ;
            query.exec("UPDATE `Parking` SET `NbPlace`=" + QString::number(calculPlace)+";");
        }
    } else {
        qDebug() << "probleme ouverture bdd";
    }
    QSqlDatabase::database().commit();
}

int BDD::NbPlaces() {
    QSqlQuery requete ;
    requete.exec ("SELECT * FROM Parking");
    while (requete.next ()){
        nbPlace = requete.value(0).toInt();
    }
    int result = nbPlace;
    return result;
}
