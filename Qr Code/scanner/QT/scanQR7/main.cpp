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
    QString message = "Places: " +  QString::number(co1->nbPlace) + "/50";
    pl->afficher(message);


    return 0;
}
