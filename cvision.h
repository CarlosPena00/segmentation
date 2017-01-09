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
    Cvision(int index);
    Cvision(std::string);
    RGB* YUVtoRGB(YUV p);
    YUV* RGBtoYUV(RGB p);
    void BGRtoYUV(cv::Vec3b p, int *y, int *u, int *v);
    void RGBtoYUV(cv::Vec3b p, int *y, int *u, int *v);
    void setup();
    void getYUV();
    void getNormalFrame(cv::Mat &src, cv::Mat &dst);
    void getNormalFrameLut(cv::Mat &src, cv::Mat &dst);
    void getBrutalFrame(cv::Mat &src, cv::Mat &dst);
    void getBrutalFrameLut(cv::Mat &src, cv::Mat &dst);
    void getFrame(cv::Mat &frame);
    void getFrame();
    void setLimiar(int value);
    bool isInside(YUV p, Color q);
    int brutalForce(QColor p);
    int brutalForce(cv::Vec3b p);
    int brutalForce(YUV p);
    int normalForce(QColor p);
    int normalForce(YUV px);
    int vectorDist(YUV p);
    int debug(QColor p);
    double surfaceDistance(YUV p, Color q);
    double planDistance(int minPlano, int maxPlano);
    double absDistance(YUV p, YUV q);
    int* initLutNormal();
    int* initLutBrutal();
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
    int* lutNormal;
    int* lutBrutal;

};

#endif // CVISION_H

