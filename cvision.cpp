#include "cvision.h"

RGB *Cvision::YUVtoRGB(YUV p)
{
    RGB* var = new RGB;
    var->B = 1.164*(p.y - 16) + 2.018*(p.u - 128);
    var->G = 1.164*(p.y - 16) - 0.813*(p.v - 128) - 0.391*(p.u - 128);
    var->R = 1.164*(p.y - 16) + 1.596*(p.v - 128);
    return var;
}

YUV *Cvision::RGBtoYUV(RGB p)
{
    YUV* var = new YUV;

    var->y = (299*p.R + 587*p.G + 114*p.B + 500)/1000;
    var->u = (492 * (p.B-var->y) + 128000)/1000;
    var->v = (877 * (p.R-var->y) + 128000)/1000;

    return var;
}

void Cvision::BGRtoYUV(cv::Vec3b p, int *y, int *u, int *v)
{


    *y = (299*p.val[2] + 587*p.val[1] + 114*p.val[0] + 500)/1000;
    *u = (492 * (p.val[0] - *y) + 128000)/1000;
    *v = (877 * (p.val[2] - *y) + 128000)/1000;


}


void Cvision::RGBtoYUV(cv::Vec3b p, int *y, int *u, int *v)
{
    *y = (299*p.val[0] + 587*p.val[1] + 114*p.val[2] + 500)/1000;
    *u = (492 * (p.val[2] - *y) + 128000)/1000;
    *v = (877 * (p.val[0] - *y) + 128000)/1000;
}

Cvision::Cvision(int index)
{
    cam.open(index);
    setup();
}

Cvision::Cvision(std::string url)
{
    cam.open(url);
    setup();

}

void Cvision::setup()
{
    getFrame(this->src);
    colorName[0] = "NoCol";
    colorName[1] = "Laranja";
    colorName[2] = "Azul";
    colorName[3] = "Amarelo";
    colorName[4] = "Vermelho";
    colorName[5] = "Verde";
    colorName[6] = "Rosa";
    colorName[7] = "AzulClaro";
    colorName[8] = "Roxo";
    colorName[9] = "Marrom";
    this->cor[0] = cv::Vec3b(255,255,255);
    this->cor[1] = cv::Vec3b(255,165,0);
    this->cor[2] = cv::Vec3b(0,0,255);
    this->cor[3] = cv::Vec3b(255,255,0);
    this->cor[4] = cv::Vec3b(255,0,0);
    this->cor[5] = cv::Vec3b(0,255,0);
    this->cor[6] = cv::Vec3b(255,0,255);
    this->cor[7] = cv::Vec3b(100,100,250);
    this->cor[8] = cv::Vec3b(138,043,226);
    this->cor[9] = cv::Vec3b(107,66,38);
    this->cor[10] = cv::Vec3b(255,255,255);

    getYUV();

}

void Cvision::getFrame(cv::Mat &frame){

    cam>>frame;

    if(frame.empty() || frame.rows < 1 || frame.cols < 1){
        cam.set(CV_CAP_PROP_POS_FRAMES, 0);
        cam >> frame;
    }


}

void Cvision::getFrame()
{

    cam>>src2;


}

bool Cvision::isInside(YUV p, Color q)
{

    if( p.y >= q.min.y && p.u >= q.min.u && p.v >= q.min.v)
            if(p.y <= q.max.y && p.u <= q.max.u && p.v <= q.max.v)return true;

    return false;

}

int Cvision::brutalForce(QColor p)
{
    RGB var;
    var.R = p.red();
    var.G = p.green();
    var.B = p.blue();
    YUV *px;
    px = RGBtoYUV(var);
    return vectorDist(px[0]);
}

int Cvision::brutalForce(cv::Vec3b p)
{
    YUV px[1];
    RGBtoYUV(p,&px[0].y,&px[0].u,&px[0].v);
    return vectorDist(px[0]);
}

int Cvision::normalForce(QColor p)
{
    RGB var;
    var.R = p.red();
    var.G = p.green();
    var.B = p.blue();
    int finalIndex = 0;
    YUV *px;
    px = RGBtoYUV(var);

    for(int i = 0 ; i < MAXCOLOR ; i++){
        if(isInside(px[0],color[i])){
            finalIndex = i;
            px[0].dist[i] = 0;
        }
    }
    return finalIndex;
}

int Cvision::normalForce(YUV px)
{
    int finalIndex = 0;
    for(int i = 0 ; i < MAXCOLOR ; i++){
        if(isInside(px,color[i])){
            finalIndex = i;
            px.dist[i] = 0;
        }
    }

    return finalIndex;

}
int Cvision::vectorDist(YUV p)
{
   int finalIndex=-1;
   double minDist = 999999999;

    for(int i = 0 ; i < MAXCOLOR ; i++){

        if(isInside(p,color[i])){
            minDist = 0;
            finalIndex = i;
            p.dist[i] = 0;
        }else{
            p.dist[i] = surfaceDistance(p, color[i]);
            if(minDist > p.dist[i]){
                minDist = p.dist[i];
                finalIndex = i;
            }
        }

    }



    return finalIndex;
}

int Cvision::debug(QColor p)
{
    RGB var;
    var.R = p.red();
    var.G = p.green();
    var.B = p.blue();
    YUV *px;
    px = RGBtoYUV(var);
    return vectorDist(px[0]);

}
double Cvision::surfaceDistance(YUV p, Color q)
{
    double minDist = 999999;
    double localDist = 0;
//Y Plan
    for(int i = q.min.u ; i <= q.max.u ; i+=10)
    {
        for(int j = q.min.v ; j <= q.max.v ; j+=10)
        {
            var.y = q.min.y;
            var.u = i;
            var.v = j;
            localDist = absDistance(p,var);
            if(minDist > localDist){
                minDist = localDist;
            }
            var.y = q.max.y;
            localDist = absDistance(p,var);
            if(minDist > localDist)
            {
                minDist = localDist;
            }

        }
    }
//U Plan
    for(int i = q.min.y ; i <= q.max.y ; i+=10)
    {
        for(int j = q.min.v ; j <= q.max.v ; j+=10)
        {
            var.y = i;
            var.u = q.min.u;
            var.v = j;
            localDist = absDistance(p,var);
            if(minDist > localDist){
                minDist = localDist;
            }
            var.u = q.max.u;
            localDist = absDistance(p,var);
            if(minDist > localDist)
            {
                minDist = localDist;
            }

        }
    }
//V Plan
    for(int i = q.min.y ; i <= q.max.y ; i+=10)
    {
        for(int j = q.min.u ; j <= q.max.u ; j+=10)
        {
            var.y = i;
            var.u = j;
            var.v = q.min.v;
            localDist = absDistance(p,var);
            if(minDist > localDist){
                minDist = localDist;
            }
            var.v = q.max.v;
            localDist = absDistance(p,var);
            if(minDist > localDist)
            {
                minDist = localDist;
            }

        }
    }

    return minDist;
}



double Cvision::absDistance(YUV p, YUV q)
{
    return std::abs(p.y - q.y ) + std::abs(p.u - q.u) + std::abs(p.v - q.v);
}



void Cvision::getYUV()
{

    cv::FileStorage fs( xml , cv::FileStorage::READ);
    cv::FileNode n;

    for(int i=0;i<MAXCOLOR;i++){

        n = fs[colorName[i]];
        color[i].min.y=(int) n["ymin"];
        color[i].min.u=(int) n["umin"];
        color[i].min.v=(int) n["vmin"];
        color[i].max.y=(int) n["ymax"];
        color[i].max.u=(int) n["umax"];
        color[i].max.v=(int) n["vmax"];

    }

    fs.release();

}

void Cvision::getNormalFrame(cv::Mat &src, cv::Mat &dst)
{
    int cols = src.cols;
    int rows = src.rows;
    cv::Vec3b tempvar;YUV var;
    for(int j = 0 ; j < rows ; ++j)
    {
        for(int i = 0 ; i < cols ; ++i)
        {
            tempvar = src.at<cv::Vec3b>(j,i);
            BGRtoYUV(tempvar,&var.y,&var.u,&var.v);
            //std::cout<<"( "<<var.y<<" "<<var.u<<" "<<var.v<<" )"<<std::endl;
            dst.at<cv::Vec3b>(j,i) = this->cor[normalForce(var)];

        }
    }

}

void Cvision::getBrutalFrame(cv::Mat &src, cv::Mat &dst)
{
    int cols = src.cols;
    int rows = src.rows;
    cv::Vec3b tempvar;YUV var;
    for(int j = 0 ; j < rows ; ++j)
    {
        for(int i = 0 ; i < cols ; ++i)
        {
            tempvar = src.at<cv::Vec3b>(j,i);
            if(tempvar != cv::Vec3b(0,0,0)){
                dst.at<cv::Vec3b>(j,i) = this->cor[brutalForce(tempvar)];
            }
        }
    }
}
