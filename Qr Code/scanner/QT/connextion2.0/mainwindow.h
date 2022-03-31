#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <iostream>
#include <QCoreApplication>

#include <QtCore>
#include <QtGui>

#include "/home/snir/Documents/QT project/Projet/PROJET/libs/sqlrequest.h"
#include <QSql>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

#define q2c(string) string.toStdString()

namespace Ui { class MainWindow; }

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

