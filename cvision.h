#ifndef CVISION_H
#define CVISION_H

#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/opencv.hpp"
#include <QMainWindow>
#include <QTimer>
#ifndef MAXCOLOR
#define MAXCOLOR 10
#endif

typedef struct YUV{

    int y;
    int u;
    int v;
    int index;
    double dist[MAXCOLOR];
}YUV;

typedef struct RGB{
    int R;
    int G;
    int B;
}RGB;

typedef struct Color{
    YUV max;
    YUV min;
}Color;

class Cvision
{
public:
    RGB* YUVtoRGB(YUV p);
    YUV* RGBtoYUV(RGB p);
    void BGRtoYUV(cv::Vec3b p, int *y, int *u, int *v);
    void RGBtoYUV(cv::Vec3b p, int *y, int *u, int *v);
    Cvision(int index);
    Cvision(std::string);
    void setup();
    void getYUV();
    void getNormalFrame(cv::Mat &src, cv::Mat &dst);
    void getBrutalFrame(cv::Mat &src, cv::Mat &dst);
    void getFrame(cv::Mat &frame);
    void getFrame();
    void setLimiar(int value);
    bool isInside(YUV p, Color q);
    int brutalForce(QColor p);
    int brutalForce(cv::Vec3b p);
    int normalForce(QColor p);
    int normalForce(YUV px);
    double surfaceDistance(YUV p, Color q);
    double planDistance(int minPlano, int maxPlano);
    double absDistance(YUV p, YUV q);
    int vectorDist(YUV p);
    int debug(QColor p);
private:
    std::string url;
    std::string carlos="/home/kaka/Desktop/RC/video4.avi";
    std::string xml   ="/home/kaka/Desktop/Knn/SegKnn.xml";
    std::string colorName[20];
    cv::Vec3b cor[20];
    cv::VideoCapture cam;
    cv::Mat src;
    cv::Mat src2;
    Color color[MAXCOLOR];
    YUV var;
    YUV myColor[1];//Mudar
    int limiar = 500;

};

#endif // CVISION_H

