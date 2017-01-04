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
    cv::imshow("Ola",src2);

}

bool Cvision::isInside(YUV p, Color q)
{

    if( p.y >= q.min.y && p.u >= q.min.u && p.v >= q.min.v)
            if(p.y <= q.max.y && p.u <= q.max.u && p.v <= q.max.v)return true;

    return false;

}
int Cvision::vectorDist(YUV p)
{
   int finalIndex=-1;
   double minDist = 999999999;

    for(int i = 0 ; i < MAXCOLOR ; i++){
        p.dist[i] = surfaceDistance(p, color[i]);

        if(minDist > p.dist[i]){
            minDist = p.dist[i];
            finalIndex = i;
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
