#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <iostream>
#include <QMainWindow>
#include <QTimer>
#include "cvision.h"
#include <cstdlib>
#include <cstring>

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
    void displayCte();

    QPoint getPosition();
    void vectorDistance(QColor p, ColorDist vector[]);
    void displayChooseOneAbs(int color);
    void displayChooseOneBrutalF(int color);
    void displayChooseOneNormalF(int color);
    double distanceAbs(QColor p, QColor q);
    double distanceEucledian(QColor p, QColor q);


    void displayChooseOneEuclidean(int color);
private:
    std::string carlos  ="/home/kaka/Desktop/RC/video4.avi";

    Ui::MainWindow *ui;
    cv::Mat src;
    cv::Mat dst;
    Cvision *cvision;
    QPoint position;
    QPoint pos;
    QPoint maxPosition;
    QPalette paletteTag[20];
    QPalette paletteChoose[5];
    QColor cor[11];
    QColor rgb;
    ColorDist* colorDist;

};

#endif // MAINWINDOW_H
