#ifndef USE_CVSNAKEIMAGE_H
#define USE_CVSNAKEIMAGE_H
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "opencv/cv.h"
#include "opencv/highgui.h"
#include "zbar.h"
#include "zbar/Image.h"
#include "zbar/ImageScanner.h"
#include "QFileDialog"
#include "zbar/Video.h"
#include "QMessageBox"
#include "QWidget"
#include "QTimer"
#include <zint.h>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/legacy/legacy.hpp>
using namespace zbar;
using namespace cv;

typedef struct parameter Parameter;

struct parameter {
  float alpha;
  float beta;
  float gamma;
};
class use_cvSnakeImage
{
public:
    use_cvSnakeImage(IplImage *src);
};

#endif // USE_CVSNAKEIMAGE_H
