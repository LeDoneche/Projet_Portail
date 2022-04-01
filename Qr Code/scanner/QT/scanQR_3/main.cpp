#include <iostream>
#include <algorithm>
#include <vector>
#include <zbar.h>

#include <opencv2/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>

#include <QCoreApplication>
#include <QtCore>

#include <QtSql>
#include <QSqlDatabase>
#include "/home/pi/LibMysql/libs/sqlrequest.h"
#include <QtSql/QSqlQuery>



using namespace std;
using namespace cv;
using namespace zbar;

std::string test;

void image(){

    Mat fichier = imread("/home/pi/ftp/capture.jpg", IMREAD_GRAYSCALE);
    imshow("Image", fichier);

    int largeur = fichier.cols;
    int hauteur = fichier.rows;
    ImageScanner decodage;
    decodage.set_config(ZBAR_NONE, ZBAR_CFG_ENABLE, 1);
    Image image(largeur, hauteur, "Y800", fichier.data, largeur*hauteur);
    cout << decodage.scan(image) << endl;
    for (auto symbole = image.symbol_begin(); symbole != image.symbol_end(); ++symbole)
    {
        cout << "Data : " << symbole->get_data() << endl;
        test = symbole->get_data();
    }
}


void connection()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setUserName("portail");
    db.setPassword("portail");
    db.setDatabaseName("Portail");

    if(db.open()) {

        qDebug() << "Vous etes connecté à la bdd";

            QSqlDatabase::database().transaction();
            QSqlQuery query ;
            query.exec(QString::fromStdString("SELECT QR FROM Personnel WHERE QR = '" + test + "';")); // "SELECT COUNT(QR) FROM Personnel WHERE QR = '" + test + "';"
                    int key = query.numRowsAffected(); // verif si le champ existe
            if( key > 0) {
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
   image();
   connection();

    return  0;
}
