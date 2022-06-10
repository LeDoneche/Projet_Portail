#include "header.h"

using namespace std;
using namespace cv;

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

int nb;
std::string qr;
int key;
QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
int pas_QRCode;

int envoyerTrame(char trame[MAX_TRAME])
{

    QUdpSocket *socket;
    // connexion au panneau lumineux
    socket = new QUdpSocket();
    socket-> bind(QHostAddress("172.20.233.19"), 9520);
    socket->writeDatagram(trame, QHostAddress("172.20.233.19"), 9520 );
    socket->close();
    return 0;
}

int fabriquerTrame(char *trame, QString message)
{
    int i = 0;
    char couleur;
    QString str;

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

int afficher(QString message)
{
    char trame[MAX_TRAME] = {0x04};

    //qDebug() << Q_FUNC_INFO << "-> message : " ;

    // on fabrique la trame
    fabriquerTrame(&trame[0], message);
    // on envoie la trame
    envoyerTrame(trame);

    return 0;
}




void display(Mat &im, Mat &bbox)
{
    int n = bbox.rows;
    for(int i = 0 ; i < n ; i++)
    {
        line(im, Point2i(bbox.at<float>(i,0),bbox.at<float>(i,1)), Point2i(bbox.at<float>((i+1) % n,0), bbox.at<float>((i+1) % n,1)), Scalar(255,0,0), 3);
    }
}

void analyse_qr(){

    // lecture de l'image
    Mat inputImage;
    inputImage = imread("/home/pi/ftp/cap.jpg");
    QRCodeDetector qrDecoder = QRCodeDetector();

    Mat bbox, rectifiedImage;

    string data = qrDecoder.detectAndDecode(inputImage, bbox, rectifiedImage);
    if(data.length()>0)
    {
        cout << "Data : " << data << endl;
        qr = data ;

        display(inputImage, bbox);
        rectifiedImage.convertTo(rectifiedImage, CV_8UC3);
    }
    else
        cout << "QR Code non detecte" << endl;
    pas_QRCode = 12;
}

void connection() {
    db.setHostName("localhost");
    db.setUserName("portail");
    db.setPassword("portail");
    db.setDatabaseName("Portail");
}
void bdd()
{

    if(db.open()) { //db.open()

        qDebug() << "Vous etes connecté à la bdd";

        QSqlDatabase::database().transaction();
        QSqlQuery query ;
        query.exec(QString::fromStdString("SELECT QR FROM Personnel WHERE QR = '" + qr + "';"));
        key = query.numRowsAffected(); // verif si le champ existe
        if( key > 0) {
            qDebug() << "QRCode bon";

            query.exec("SELECT NbPlace FROM Parking");
            if (query.next()) {
                //- Verification qu le nb de place est sup a 0 -//
                if ( query.value(0).toInt() > 0 ){
                    int nbPlace = query.value(0).toInt();
                    nbPlace = nbPlace - 1 ;
                    nb = nbPlace;
                    cout << "nombre de place restante :" << nb << endl;
                    //- mise a jour de la bdd -//
                    query.exec("UPDATE `Parking` SET `NbPlace`=" + QString::number(nbPlace)+";");

                } else {
                    qDebug() << "Attention plus de place dans le parking";


                }
            }
            QSqlDatabase::database().commit();

        }  else  {
            qDebug() << "erreur QRCode ";

            QSqlQuery requete ;
            //je récupère le nombre de place disponible dans la BDD
            requete.exec ("SELECT * FROM Parking");

            while (requete.next ()){
                nb = requete.value(0).toInt();

            }
        }
    }else {
        qDebug() << "Vous n'etes pas connecté";

    }

}

int main()
{   
    connection();

    analyse_qr();
    bdd();

 /*
     //Message pour non-présence du qrcode (si code tourne en boucle)
    if (pas_QRCode == 12){
        QString message5 = "Places: " + QString::number(nb)+"/50";
        afficher(message5);

    }
    else {
*/
    {
        //Message pour la limite de place
        if (nb <= 0)
        {
            QString message4 = "Parking Plein";
            afficher(message4);

        }
        else  {

            /*
            je récupère la variable "nb" et je l'insère dans le message
            pour afficher nombres de places dispo
           */
            QString message = "Places: " + QString::number(nb)+"/50";
            afficher(message);

            //temporisation de 3s
            QThread::sleep(3);

            //si qrcode non présent dans la bdd
            if( key == 0)
            {
                QString message2 = "QRCode Faux";
                afficher(message2);
                QThread::sleep(3);
                 afficher(message); //je réaffiche le nombres de places restantes
            }

            //si qrcode présent dans la bdd
            else
            {
                QString message3 = "QRCode Bon";
                afficher(message3);
                QThread::sleep(3);
                 afficher(message); //je réaffiche le nombres de places restantes

            }


        }

     }

      return 0;
  }








