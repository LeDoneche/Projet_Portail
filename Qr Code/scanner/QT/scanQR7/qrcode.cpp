#include "QRCode.h"

using namespace std;

string QRCode::getQr() const {
    return qr;
}

// constructeur
QRCode::QRCode(QString ImgPath) {
    inputImage = imread(ImgPath.toStdString());
}

void QRCode::display(Mat &im, Mat &bbox) {
    for(int i = 0 ; i < n ; i++) {
        line(im, Point2i(bbox.at<float>(i,0),bbox.at<float>(i,1)), Point2i(bbox.at<float>((i+1) % n,0), bbox.at<float>((i+1) % n,1)), Scalar(255,0,0), 3);
    }
}

bool QRCode::Detection() {
    QRCodeDetector qrDecoder = QRCodeDetector();
    string data = qrDecoder.detectAndDecode(inputImage, bbox, rectifiedImage);
    if(data.length()>0) {
        return true;
    } else {
        return false;
    }

}

string QRCode::RecupData(){
    QRCodeDetector qrDecoder = QRCodeDetector();
    string data = qrDecoder.detectAndDecode(inputImage, bbox, rectifiedImage);
    if(data.length()>0) {
        qr = data ;
        return qr;
    }
    else return nullptr;
}
