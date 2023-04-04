#include "SunShape.h"


void GaussionSunShape::setPara(double para)
{
    sigma = para;
}
double GaussionSunShape::getPara() const
{
    return sigma;
}
void GaussionSunShape::testPrint()const
{
    qDebug()<<"Gaussion SunShape:: sigma = "<<sigma;
}



void PillboxSunShape::setPara(double para)
{
    theta_max = para;
}
double PillboxSunShape::getPara() const
{
    return theta_max;
}
void PillboxSunShape::testPrint()const
{
    qDebug()<<"Pillbox SunShape:: theta_Max = "<<theta_max;
}



void BuieSunShape::setPara(double para)
{
    csr = para;
}
double BuieSunShape::getPara() const
{
    return csr;
}
void BuieSunShape::testPrint()const
{
    qDebug()<<"Buie SunShape:: csr = "<<csr;
}
