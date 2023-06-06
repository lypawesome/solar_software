
#include "simulation/RayTracingParameter.h"

using namespace solar;

QString solar::RayTracingParameter::readRayCnt()
{
    return QString::number(ray_cnt_);
}
void solar::RayTracingParameter::writeRayCnt(const QString& str)
{
    // 注意这里要判断是否类中存的数据与ui传回来的数据是否相等
    // 只有当数据真正改变时才发出信号，否则会有无线递归的风险
    int data = str.toInt();
    if(data != ray_cnt_)
    {
        ray_cnt_ = data;
        emit rayCntChanged();
    }
    qDebug() <<"********** changed ray_cnt_ to: " << ray_cnt_;
}   


QString solar::RayTracingParameter::readPixelLength()
{
    return QString::number(pixel_length_);
}
void solar::RayTracingParameter::writePixelLength(const QString& str)
{
    double data = str.toDouble();
    
    if(fabs(data - pixel_length_) > 1e-8)
    {
        pixel_length_ = data;
        emit pixelLengthChanged();
    }
    qDebug() <<"********** changed pixel_length_ to: " << pixel_length_;
}

QString solar::RayTracingParameter::readSubheliostatLength()
{
    return QString::number(subheliostat_length_);
}
void solar::RayTracingParameter::writeSubheliostatLength(const QString& str)
{
    double data = str.toDouble();
    
    if(fabs(data - subheliostat_length_) > 1e-8)
    {
        subheliostat_length_ = data;
        emit subheliostatLengthChanged();
    }
    qDebug() <<"********** changed subheliostat_length_ to: " << subheliostat_length_;
}



QString solar::RayTracingParameter::readSceneGridX()
{
    return QString::number(scene_grid_size_.x());
}  
void solar::RayTracingParameter::writeSceneGridX(const QString& str)
{
    double data = str.toDouble();
    
    if(fabs(data - scene_grid_size_.x()) > 1e-8)
    {
        scene_grid_size_.set_x(data);
        emit sceneGridXChanged();
    }
    qDebug() <<"********** changed scene_grid_size_.x to: " << scene_grid_size_.x();
} 
QString solar::RayTracingParameter::readSceneGridY()
{
    return QString::number(scene_grid_size_.y());
}   
void solar::RayTracingParameter::writeSceneGridY(const QString& str)
{
    double data = str.toDouble();
    
    if(fabs(data - scene_grid_size_.y()) > 1e-8)
    {
        scene_grid_size_.set_y(data);
        emit sceneGridYChanged();
    }
    qDebug() <<"********** changed scene_grid_size_.y to: " << scene_grid_size_.y();
}
QString solar::RayTracingParameter::readSceneGridZ()
{
    return QString::number(scene_grid_size_.z());
}   
void solar::RayTracingParameter::writeSceneGridZ(const QString& str)
{
    double data = str.toDouble();
    
    if(fabs(data - scene_grid_size_.z()) > 1e-8)
    {
        scene_grid_size_.set_z(data);
        emit sceneGridZChanged();
    }
    qDebug() <<"********** changed scene_grid_size_.z to: " << scene_grid_size_.z();
}  