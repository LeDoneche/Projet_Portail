
#include <iostream>
#include <algorithm>
#include <vector>
#include "/usr/include/zbar.h"

#include <opencv2/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <QtCore/QCoreApplication>

#include <QtSql/QSqlDatabase>
#include <QtSql/QSql>
#include "/home/snir/Documents/QT project/Projet/PROJET/libs/sqlrequest.h"


using namespace std;
using namespace cv;
using namespace zbar;


typedef struct
{
  string type;
  string data;
  vector <Point> location;
}decodedObject;

// Find and decode barcodes and QR codes
void decode(Mat &im, vector<decodedObject>&decodedObjects)
{

  // Create zbar scanner
  ImageScanner scanner;

  // Configure scanner
  scanner.set_config(ZBAR_QRCODE, ZBAR_CFG_ENABLE, 1);

  // Convert image to grayscale
  Mat imGray;
  cvtColor(im, imGray,COLOR_BGR2GRAY);

  // Wrap image data in a zbar image
  Image image(im.cols, im.rows, "Y800", (uchar *)imGray.data, im.cols * im.rows);

  // Scan the image for QRCodes
  int scann = scanner.scan(image);

  // Print results
  for(Image::SymbolIterator symbol = image.symbol_begin(); symbol != image.symbol_end(); ++symbol)
  {
    decodedObject obj;

    obj.data = symbol->get_data();

    // Print data
    cout << "Data : " << obj.data << endl << endl;
    decodedObjects.push_back(obj);
  }
}

int main(int argc, char *argv[])
{
/*
    // Read image
    Mat im;
    if(argc>1)
      im = imread(argv[1]);
    else
      im = imread("/home/snir/Documents/QT project/Projet/capture.jpg");

   // Variable for decoded objects
   vector<decodedObject> decodedObjects;

   // Find and decode barcodes and QR codes
   decode(im, decodedObjects);


   return 0;
*/
   QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
   db.setHostName("localhost");
   db.setUserName("portail");
   db.setPassword("portail");
   db.setDatabaseName("Portail");
   if(db.open()) {

      cout << "Base de donnée connecté" << endl;


   }else {

       cout << "Base de donnée non-connecté" << endl;

  }
   return 0;
 }
