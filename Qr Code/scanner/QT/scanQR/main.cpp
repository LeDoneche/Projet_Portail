#include <iostream>
#include <zbar.h>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;
using namespace zbar;

int main()
{
    /*
    Mat couleur = imread("/home/snir/Documents/QT project/Projet/capture.jpg"); // chemin d'acces complet de l'image à decoder
    imshow("Image", couleur);
    waitKey();

    Mat gris;
    cvtColor(couleur, gris, COLOR_BGR2GRAY);
    imshow("Image", gris);
    waitKey();

    Mat gradx, grady, result;
    Sobel(gris, gradx, CV_8U, 1, 0, 3, 0.4, 128);
    Sobel(gris, grady, CV_8U, 0, 1, 3, 0.4, 128);
    subtract(gradx, grady, result);
    imshow("Result", result);
    waitKey();

    Mat flou;
    blur(result, flou, Size(9, 30)); // 30: réglage flou pour avoir la bonne zone blanche
    //imshow("Result", flou);
    waitKey();

    threshold(flou, flou, 50, 255, THRESH_BINARY);
    imshow("Result", flou);
    waitKey();

    Mat localisation = getStructuringElement(MORPH_RECT, Size(53, 17));
    morphologyEx(flou, flou, MORPH_CLOSE, localisation);
    imshow("Result", flou);
    waitKey();

    erode(flou, flou, Mat(), Point(-1, -1), 3);
    dilate(flou, flou, Mat(), Point(-1, -1), 3);
    imshow("Result", flou);
    waitKey();

    vector<vector<Point>> contours;
    findContours(flou, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
    RotatedRect rect = minAreaRect(contours[0]);
    Rect zone = rect.boundingRect() - Point(30, 10) + Size(60, 15);
    rectangle(couleur, zone, Scalar(0, 255, 0), 2);
    imshow("Image", couleur);
    waitKey();

    Mat zoneRect = gris(zone);
    imshow("Zone", zoneRect);
    waitKey();

    int largeur = zoneRect.cols;
    int hauteur = zoneRect.rows;
    ImageScanner decodage;
    decodage.set_config(ZBAR_NONE, ZBAR_CFG_ENABLE, 1);
    Image image(largeur, hauteur, "Y800", zoneRect.data, largeur*hauteur);
    cout << decodage.scan(image) << endl;
    for (auto code = image.symbol_begin(); code != image.symbol_end(); ++code) {
        cout << "Data : " << code->get_data() << endl;
    }
    return 0;
*/


    Mat fichier = imread("/home/snir/Documents/QT project/Projet/capture.jpg", IMREAD_GRAYSCALE);
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
    }


}


