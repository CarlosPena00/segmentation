#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QTimer *updateTimer;

    updateTimer = new QTimer();
    connect(updateTimer, SIGNAL(timeout()), this, SLOT(updateAndDraw()));
    updateTimer->start(30);
    cvision = new Cvision(carlos);
    cvision->getFrame(dst);
    int width = ui->labelDisplay->width();
    int height = ui->labelDisplay->height();
    this->maxPosition = QPoint(width,height);
    colorDist = new ColorDist [MAXCOLOR];

       this->cor[0] = QColor(255,255,255);
       this->cor[1] = QColor(255,165,0);
       this->cor[2] = QColor(0,0,255);
       this->cor[3] = QColor(255,255,0);
       this->cor[4] = QColor(255,0,0);
       this->cor[5] = QColor(0,255,0);
       this->cor[6] = QColor(255,0,255);
       this->cor[7] = QColor(100,100,250);
       this->cor[8] = QColor(138,043,226);
       this->cor[9] = QColor(107,66,38);
       this->cor[10] = QColor(255,255,255);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QColor MainWindow::displayShow(cv::Mat &frame, QPoint p)
{
    cv::Size newSize(this->ui->labelDisplay->width(), this->ui->labelDisplay->height());
    cv::resize(frame, frame, newSize);
    cv::cvtColor(frame, frame, CV_BGR2RGB);
    QImage qimg((uchar*)frame.data, frame.cols, frame.rows, frame.step, QImage::Format_RGB888);
    this->ui->labelDisplay->setPixmap(QPixmap::fromImage(qimg));

    QColor myrgb(qimg.pixel(p));
    //std::cout<<myrgb.red()<<" "<<myrgb.green()<<" "<<myrgb.blue()<<std::endl;
    paletteTag[10].setColor( backgroundRole(), myrgb  );
    ui->framePixel->setPalette( paletteTag[10] );
    ui->framePixel->setAutoFillBackground( true );

    ui->label_RGB->setText(QString("( ") + QString::number(myrgb.red()) + QString(" ; ")+
                           QString::number(myrgb.green()) + QString(" ; ")
                           + QString::number(myrgb.blue()) + QString(" )"));


    return myrgb;

}

void MainWindow::displayShowNormal(cv::Mat &frame)
{
    cv::Size newSize(this->ui->labelDisplayNormal->width(), this->ui->labelDisplayNormal->height());
    cv::resize(frame, frame, newSize);
    //cv::cvtColor(frame, frame, CV_BGR2RGB);
    QImage qimg((uchar*)frame.data, frame.cols, frame.rows, frame.step, QImage::Format_RGB888);
    this->ui->labelDisplayNormal->setPixmap(QPixmap::fromImage(qimg));

}

void MainWindow::displayShowBrutal(cv::Mat &frame)
{
    cv::Size newSize(this->ui->labelDisplayBrutal->width(), this->ui->labelDisplayBrutal->height());
    cv::resize(frame, frame, newSize);
    //cv::cvtColor(frame, frame, CV_BGR2RGB);
    QImage qimg((uchar*)frame.data, frame.cols, frame.rows, frame.step, QImage::Format_RGB888);
    this->ui->labelDisplayBrutal->setPixmap(QPixmap::fromImage(qimg));
}

void MainWindow::displayCte()
{
    paletteTag[0].setColor( backgroundRole(), cor[0]  );
    ui->framecolor->setPalette( paletteTag[0] );
    ui->framecolor->setAutoFillBackground( true );
    paletteTag[1].setColor( backgroundRole(), cor[1]  );
    ui->framecolor_2->setPalette( paletteTag[1] );
    ui->framecolor_2->setAutoFillBackground( true );
    paletteTag[2].setColor( backgroundRole(), cor[2]  );
    ui->framecolor_3->setPalette( paletteTag[2] );
    ui->framecolor_3->setAutoFillBackground( true );
    paletteTag[3].setColor( backgroundRole(), cor[3]  );
    ui->framecolor_4->setPalette( paletteTag[3] );
    ui->framecolor_4->setAutoFillBackground( true );
    paletteTag[4].setColor( backgroundRole(), cor[4]  );
    ui->framecolor_5->setPalette( paletteTag[4] );
    ui->framecolor_5->setAutoFillBackground( true );
    paletteTag[5].setColor( backgroundRole(), cor[5]  );
    ui->framecolor_6->setPalette( paletteTag[5] );
    ui->framecolor_6->setAutoFillBackground( true );
    paletteTag[6].setColor( backgroundRole(), cor[6]  );
    ui->framecolor_7->setPalette( paletteTag[6] );
    ui->framecolor_7->setAutoFillBackground( true );
    paletteTag[7].setColor( backgroundRole(), cor[7]  );
    ui->framecolor_8->setPalette( paletteTag[7] );
    ui->framecolor_8->setAutoFillBackground( true );
    paletteTag[8].setColor( backgroundRole(), cor[8]  );
    ui->framecolor_9->setPalette( paletteTag[8] );
    ui->framecolor_9->setAutoFillBackground( true );
    paletteTag[9].setColor( backgroundRole(), cor[9]  );
    ui->framecolor_10->setPalette( paletteTag[9] );
    ui->framecolor_10->setAutoFillBackground( true );



}

void MainWindow::displayChooseOneAbs(int color)
{
    paletteChoose[0].setColor(backgroundRole(),cor[color]);
    ui->framecolorPredict->setPalette(paletteChoose[0]);
    ui->framecolorPredict->setAutoFillBackground(true);
    ui->label_PredictRGBAbs->setText(QString("( ") + QString::number(cor[color].red()) + QString(" ; ")+
                                     QString::number(cor[color].green()) + QString(" ; ")
                                     + QString::number(cor[color].blue()) + QString(" )"));
}

void MainWindow::displayChooseOneBrutalF(int color)
{
    paletteChoose[2].setColor(backgroundRole(),cor[color]);
    ui->framecolorPredict_3->setPalette(paletteChoose[2]);
    ui->framecolorPredict_3->setAutoFillBackground(true);
    ui->label_PredictRGBBrutalF->setText(QString("( ") + QString::number(cor[color].red()) + QString(" ; ")+
                                     QString::number(cor[color].green()) + QString(" ; ")
                                     + QString::number(cor[color].blue()) + QString(" )"));

}

void MainWindow::displayChooseOneNormalF(int color)
{
    paletteChoose[3].setColor(backgroundRole(),cor[color]);
    ui->framecolorPredict_4->setPalette(paletteChoose[3]);
    ui->framecolorPredict_4->setAutoFillBackground(true);
    ui->label_PredictRGBNormalF->setText(QString("( ") + QString::number(cor[color].red()) + QString(" ; ")+
                                         QString::number(cor[color].green()) + QString(" ; ")
                                         + QString::number(cor[color].blue()) + QString(" )"));

}

void MainWindow::displayChooseOneEuclidean(int color)
{
    paletteChoose[1].setColor(backgroundRole(),cor[color]);
    ui->framecolorPredict_2->setPalette(paletteChoose[1]);
    ui->framecolorPredict_2->setAutoFillBackground(true);
    ui->label_PredictRGBEuclidean->setText(QString("( ") + QString::number(cor[color].red()) + QString(" ; ")+
                                     QString::number(cor[color].green()) + QString(" ; ")
                                     + QString::number(cor[color].blue()) + QString(" )"));
}

QPoint MainWindow::getPosition()
{
    if(ui->labelDisplay->underMouse()){
        this->position = ui->labelDisplay->mapFromGlobal(QCursor::pos());

        if(this->position.x() >= maxPosition.x()){
            this->position.setX(maxPosition.x()-1);

        }
        if(this->position.y() >= maxPosition.y()){
            this->position.setY(maxPosition.y()-1);

        }
        if(this->position.x() < 0){
            this->position.setX(0);

        }
        if(this->position.y() < 0){
            this->position.setY(0);

        }
    }

    this->ui->Xpos->setText(QString::number(this->position.x()));
    this->ui->Ypos->setText(QString::number(this->position.y()));

    return this->position;
}


void MainWindow::vectorDistance(QColor p, ColorDist vector[])
{
    ColorDist chooseOne;
    chooseOne.dist = 1000;
    chooseOne.color = -1;
    for(int i = 0 ; i < MAXCOLOR ; i ++){
        vector[i].dist = distanceAbs(p,this->cor[i]);
        vector[i].color = i;

        if(chooseOne.dist > vector[i].dist){
            chooseOne.dist = vector[i].dist;
            chooseOne.color = i;
        }
    }
    displayChooseOneAbs(chooseOne.color);

    chooseOne.dist = 9999000;
    chooseOne.color = -1;
    for(int i = 0 ; i < MAXCOLOR ; i ++){
        vector[i].dist = distanceEucledian(p,this->cor[i]);
        vector[i].color = i;

        if(chooseOne.dist > vector[i].dist){
            chooseOne.dist = vector[i].dist;
            chooseOne.color = i;
        }
    }
    displayChooseOneEuclidean(chooseOne.color);




}

double MainWindow::distanceAbs(QColor p, QColor q)
{
    return std::abs(p.red() - q.red()) + std::abs(p.blue() - q.blue()) + std::abs(p.green() - q.green()) ;
}

double MainWindow::distanceEucledian(QColor p, QColor q)
{
    return std::pow(p.red() - q.red(),2) + std::pow(p.blue() - q.blue(),2) + std::pow(p.green() - q.green(),2) ;
}





void MainWindow::updateAndDraw(){
    cvision->getFrame(src);
    cvision->getFrame(dst);

    cvision->getNormalFrame(src,dst);
    dst.copyTo(brutalForce);
    this->pos = getPosition();
    rgb = displayShow(src,this->pos);
    displayCte();
    vectorDistance(rgb, colorDist);
    int brutalF = cvision->brutalForce(rgb);
    displayChooseOneBrutalF(brutalF);
    int normalF = cvision->normalForce(rgb);
    displayChooseOneNormalF(normalF);
    displayShowNormal(dst);

    cvision->getBrutalFrame(brutalForce,brutalForce);
    displayShowBrutal(brutalForce);

}
