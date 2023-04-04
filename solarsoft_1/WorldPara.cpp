#include "WorldPara.h"

/*
==================================Location====================================
*/
void Location::setPara(QString name, QVariant value)
{
    switch(_hash.at(name))
    {
    case 0: site_name = value.toString();   break;
    case 1: longitude = value.toDouble();   break;
    case 2: latitude = value.toDouble();    break;
    }
}
QVariant Location::getPara(QString name) const
{
    QVariant ret;
    switch(_hash.at(name))
    {
    case 0: ret = site_name;    break;
    case 1: ret = longitude;    break;
    case 2: ret = latitude;     break;
    }
    return ret;
}
void Location::testPrint() const
{
    qDebug()<<"WorldPara::Location: site_name="
           <<site_name<<" longitude="<<longitude<<" latitude="<<latitude;
}


/*
==========================================Sun===============================================

*/
Sun::Sun(double _azimuth, double _elevation, double _irradiance, bool _trackable, int _sunshape_type)
    :azimuth(_azimuth), elevation(_elevation),irradiance(_irradiance),trackable(_trackable)
{
    reallocateSunshape(_sunshape_type);
}
Sun::~Sun()
{
    delete sunshape;        //这里，把父类的析构函数虚化，就可以删除子类的指针
    sunshape = nullptr;
}
void Sun::setPara(QString name, QVariant value)
{
    switch(_hash.at(name))
    {
    case 0: azimuth = value.toDouble();     break;
    case 1: elevation = value.toDouble();   break;
    case 2: irradiance = value.toDouble();  break;
    case 3: trackable = value.toBool();     break;
    case 4:                                             //重新设置sunshape的类型
    {
        reallocateSunshape(value.toInt());
        break;
    }
    case 5: sunshape->setPara(value.toDouble());    break;
    }
}
QVariant Sun::getPara(QString name) const
{
    QVariant ret;
    switch(_hash.at(name))
    {
    case 0: ret = azimuth;     break;
    case 1: ret = elevation;   break;
    case 2: ret = irradiance;  break;
    case 3: ret = trackable;     break;
    case 4: ret = sunshape_type;   break;
    case 5: ret = sunshape->getPara();    break;
    }
    return ret;
}
void Sun::testPrint() const
{
    qDebug()<<"WorldPara::Sun: azimuth="<<azimuth<<" elevation="<<elevation<<" irradiance="<<irradiance<<" trackable="<<trackable
           <<"\n \t\t"<<" sunshape_type="<<sunshape_type<<" sunshape.para="<<sunshape->getPara();

}
void Sun::reallocateSunshape(int _sunshape_type)
{
    this->sunshape_type = _sunshape_type;
    delete sunshape;
    sunshape = nullptr;
    switch(_sunshape_type)
    {
    case PILLBOX:   sunshape = new PillboxSunShape(); break;
    case BUIE:      sunshape = new BuieSunShape();      break;
    case GAUSSION:  sunshape = new GaussionSunShape();  break;
    default:{
        qDebug()<<"SUN construction error::sunshapeType is not found";
        break;
    }
    }
}


/*
============================================Air============================================
*/

void Air::setPara(QString name, QVariant value)
{
    switch(_hash.at(name))
    {
    case 0: air_model_type = value.toInt(); break;
    }
}
QVariant Air::getPara(QString name) const
{
    QVariant ret;
    switch(_hash.at(name)){
    case 0: ret = air_model_type; break;
    }
    return ret;
}
void Air::testPrint() const
{
    qDebug()<<"WorldPara::Air: air_model_type = "<<air_model_type;
}

/*
 * ==========================================Camera================================================
*/

Camera::Camera(const Vec3& _position,const Vec3& _rotation_axis, double _rotation_angle, bool _perspective)
    : position(_position), rotation_angle(_rotation_angle),rotation_axis(_rotation_axis),perspective(_perspective)
{
    lookat = Vec3(0,0,0);
    up = Vec3(0,1,0);       //y轴指向上方

    calculateUVW();
}
/*
这个函数仍需完善：
        当position改变时，uvw也需要改变
        当rotation改变时，lookat、uvw均需要改变【这里是否需要矩阵计算？？】
        ！！！！！！！！！！还需要参考一下learnopengl中camera视角移动的部分
*/
void Camera::setPara(QString name, QVariant value)
{
    switch(_hash.at(name))
    {
    case 0: position = value.value<Vec3>();     calculateUVW();    break;
    case 1: rotation_axis = value.value<Vec3>();    break;
    case 2: rotation_angle = value.toDouble();  break;
    case 3: perspective = value.toBool();       break;
    }
}
QVariant Camera::getPara(QString name) const
{
    QVariant ret;
    switch(_hash.at(name))
    {
    case 0: ret.setValue(position);         break;
    case 1: ret.setValue(rotation_angle);   break;
    case 2: ret = rotation_angle;           break;
    case 3: ret = perspective;              break;
    }
    return ret;
}
void Camera::testPrint() const
{
    qDebug()<<"WorldPara::Camera: position = ("<<position.x()<<","<<position.y()<<","<<position.z()
           <<")  rotation_axis = ("<<rotation_axis.x()<<","<<rotation_axis.y()<<","<<rotation_axis.z()
          <<")  rotation_angle = "<<rotation_angle<<"  perspective = "<<perspective;
}
void Camera::calculateUVW()
{
    w = unit_vector(position - lookat);						//注意，屏幕中心在w轴的负半轴上
    u = unit_vector(cross(up, w));						//对应屏幕上的x轴
    v = cross(w, u);
}


/*
 * ==============================================Terrain========================================================

*/
void Terrain::setPara(QString name, QVariant value)
{
    switch(_hash.at(name))
    {
    case 0: grid = value.toBool();  break;
    case 1: fill = value.toBool();  break;
    case 2: steps = value.value<Vec3>();     break;
    case 3: division = value.value<Vec3>();  break;
    case 4: min = value.value<Vec3>();  break;
    case 5: max = value.value<Vec3>();  break;
    case 6: file = value.toString();    break;
    }
}
QVariant Terrain::getPara(QString name) const
{
    QVariant ret;
    switch(_hash.at(name))
    {
    case 0: ret = grid; break;
    case 1: ret = fill; break;
    case 2: ret.setValue(steps);    break;
    case 3: ret.setValue(division);    break;
    case 4: ret.setValue(min);    break;
    case 5: ret.setValue(max);    break;
    case 6: ret = file; break;
    }
    return ret;
}
void Terrain::testPrint() const
{

}


/*
======================================================Cloud===============================================================
*/
void Cloud::setPara(QString name, QVariant value)
{
    switch(_hash.at(name))
    {
    case 0: coordinate = value.value<Vec3>();   break;
    case 1: length = value.toDouble();  break;
    case 2: width = value.toDouble();   break;
    case 3: file = value.toString();    break;
    }
}
QVariant Cloud::getPara(QString name) const
{
    QVariant ret;
    switch(_hash.at(name))
    {
    case 0: ret.setValue(coordinate);   break;
    case 1: ret = length;   break;
    case 2: ret = width;    break;
    case 3: ret = file;     break;
    }
    return ret;
}
void Cloud::testPrint() const
{

}


