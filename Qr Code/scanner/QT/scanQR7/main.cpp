#include <QCoreApplication>

#include "header.h"

#include "QRCode.h"
#include "BDD.h"
#include "PanneauLumineux.h"

using namespace std;
using namespace cv;

int main()
{
    /***********************************************************
             Annalyse du qr code
     ************************************************************/
    QRCode *qr1 = new QRCode("/home/pi/ftp/capture.jpg");

    while (qr1->Detection() == false ) {
        string rsltQR = qr1->RecupData();
    }

    /***********************************************************
         Connection à la base de donnée
    ************************************************************/
    BDD *co1 = new BDD("QMYSQL" , "localhost" , "portail" , "portail" , "Portail");




    /***********************************************************
             Vérification dans la base de donnée
     ************************************************************/
    if (qr1->Detection() == true){
        co1->VerifQR(qr1->qr);
        co1->VerifNbPlace(qr1->qr);
        co1->MajPlace(qr1->qr);
    }



    /***********************************************************
             Affichage nombre de places restante
     ************************************************************/
    PanneauLumineux *pl = new PanneauLumineux();
    
    //Message pour la limite de place
    if (co1->nbPlace >= 50) {
        QString message4 = "Parking Plein";
        pl->afficher(message4);
    } else {
        /*
           je récupère la variable "nb" et je l'insère dans le message
           pour afficher nombres de places dispo
          */
        QString message = "Places: " + QString::number(co1->nbPlace) +"/50";
        pl->afficher(message);
        
        //temporisation de 3s
        QThread::sleep(3);
        
        //si qrcode non présent dans la bdd
        if( co1->verifChampBdd == 0) {
            QString message2 = "QRCode Faux";
            pl->afficher(message2);
            QThread::sleep(3);
            pl->afficher(message); //je réaffiche le nombres de places restantes
        } else  {
            //si qrcode présent dans la bdd
            QString message3 = "QRCode Bon";
            pl->afficher(message3);
            QThread::sleep(3);
            pl->afficher(message); //je réaffiche le nombres de places restantes
        }
    }


    return 0;
}
