#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace std;

#define q2c(string) string.toStdString()

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setUserName("portail");
    db.setPassword("portail");
    db.setDatabaseName("Portail");

    if(db.open()) {

        QMessageBox::information(this, "Connection", "Vous ête maintenant connecté");

            QSqlDatabase::database().transaction();
            QSqlQuery query ;
            //- Verification du qr code dans la bdd -//
            if(query.exec("SELECT QR FROM Personnel WHERE QR = '2de4ff49d';")) {
                QMessageBox::information(this, "Requette", "code bon");

                //- Verification du nb de place -//
                query.exec("SELECT NbPlace FROM Parking");
                if (query.next()) {
                    //- Verification qu le nb de place est sup a 0 -//
                    if ( query.value(0).toInt() > 0 ){
                    int nbPlace = query.value(0).toInt();
                    nbPlace = nbPlace - 1 ;
                    //- mise a jour de la bdd -//
                    query.exec("UPDATE `Parking` SET `NbPlace`=" + QString::number(nbPlace)+";");
                    } else {
                        QMessageBox::information(this, "Attention", "plus de place dans le parking");
                    }
                }
                QSqlDatabase::database().commit();
            }  else  {
                 QMessageBox::information(this, "Requette", "code non-correct");
            }
    }else {
       QMessageBox::information(this, "Non-connecté", "Vous ête  non-connecté");
   }
}
