#ifndef QRCode_H
#define QRCode_H

#include "header.h"

using namespace cv;
using namespace std;

class QRCode {

    Mat bbox, rectifiedImage;
    int n = bbox.rows;
    Mat inputImage;
    string data;

    void display(cv::Mat &im, cv::Mat &bbox);

public:

    QRCode(QString ImgPath);
    bool Detection();
    string RecupData();
    string getQr() const;

    string qr;
};

#endif // QRCode_H
