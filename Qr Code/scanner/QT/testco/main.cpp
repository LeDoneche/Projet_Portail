#include <QCoreApplication>
#include <iostream>
#include <QtCore>


#include <QtSql/QSqlDatabase>
#include <QtSql/QSql>
#include "/home/snir/Documents/QT project/Projet/PROJET/libs/sqlrequest.h"
#include <QtSql/QSqlQuery>

std::string test;

using namespace  std;

void connection()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setUserName("portail");
    db.setPassword("portail");
    db.setDatabaseName("Portail");

    if(db.open()) {
        //test = "06aa6cea";

        qDebug() << "Vous etes connecté à la bdd";

            QSqlDatabase::database().transaction();
            QSqlQuery query ;
            query.exec(QString::fromStdString("SELECT COUNT(QR) FROM Personnel WHERE QR = '06aa6ceaa';")); // "SELECT COUNT(QR) FROM Personnel WHERE QR = '" + test + "';"
                    qDebug() << query.first();
                    int key = 0;
            if( key != 0) {
                qDebug() << "QRCode bon";

                query.exec("SELECT NbPlace FROM Parking");
                if (query.next()) {
                    //- Verification qu le nb de place est sup a 0 -//
                    if ( query.value(0).toInt() > 0 ){
                    int nbPlace = query.value(0).toInt();
                    nbPlace = nbPlace - 1 ;
                    //- mise a jour de la bdd -//
                    query.exec("UPDATE `Parking` SET `NbPlace`=" + QString::number(nbPlace)+";");
                    } else {
                        qDebug() << "Attention plus de place dans le parking";
                    }
                }
                QSqlDatabase::database().commit();

            }  else  {
                qDebug() << "erreur QRCode ";
            }
    }else {
         qDebug() << "Vous n'etes pas connecté";
   }

}

int main()
{

    connection();
    return 0;
}
