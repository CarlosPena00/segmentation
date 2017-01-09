#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <iostream>
#include <QMainWindow>
#include <QTimer>
#include "cvision.h"
#include <cstdlib>
#include <cstring>
#include <QTime>

#ifndef MAXCOLOR
#define MAXCOLOR 10
#endif

typedef struct ColorDist{
    int color;
    double dist;
}ColorDist;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public slots:
    void updateAndDraw();
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QColor displayShow(cv::Mat &frame, QPoint p);
    void displayShowNormal(cv::Mat &frame);
    void displayShowBrutal(cv::Mat &frame);
    void displayCte();

    QPoint getPosition();
    void vectorDistance(QColor p, ColorDist vector[]);
    void displayChooseOneAbs(int color);
    void displayChooseOneBrutalF(int color);
    void displayChooseOneNormalF(int color);
    double distanceAbs(QColor p, QColor q);
    double distanceEucledian(QColor p, QColor q);
    void getLimiar(int *value);


    void displayChooseOneEuclidean(int color);
private slots:
    void on_verticalSlider_valueChanged(int value);

    void on_pushButton_released();

private:
    std::string carlos  ="/home/kaka/Desktop/RC/video4.avi";

    Ui::MainWindow *ui;
    cv::Mat defaultDisplay,normalDisplay,brutalDisplay;
    cv::Mat src;
    cv::Mat dst;
    cv::Mat brutalForce;
    Cvision *cvision;
    QPoint position;
    QPoint pos;
    QPoint maxPosition;
    QPalette paletteTag[20];
    QPalette paletteChoose[5];
    QColor cor[11];
    QColor rgb;
    ColorDist* colorDist;
    QTime timer,timerLut;
    double tTimeCont=0.0,tTimeContLut =0.0;
    int tTimeInt=0, tTimeIntLut=0;
    int limiar = 500;

};

#endif // MAINWINDOW_H
