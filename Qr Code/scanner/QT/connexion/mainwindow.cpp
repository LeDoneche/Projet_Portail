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

            QSqlQuery query ;
            if(query.exec("INSERT INTO Personnel (nom,prenom,KeyPswd,adresse_mail) VALUE ('jackie', 'Roger', 'idergeef','popg rg  eg eg ');"))    {

                QMessageBox::information(this, "Requette", "envoyer");

            }  else  {

                QMessageBox::information(this, "Requette", "non-envoyer");
            }


    }else {

        QMessageBox::information(this, "Non-connecté", "Vous ête maintenant non-connecté");


   }
}
