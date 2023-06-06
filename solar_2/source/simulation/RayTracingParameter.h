
#ifndef RAYTRACING_PARAMETER_H
#define RAYTRACING_PARAMETER_H

/**
 * 仍然是UI界面部分，是光追仿真参数的设置，用于RayTracingWindow中的参数设置
 * 通过qml与C++中的数据绑定来实现
 * 
 * 其中scene_grid_size_有三个维度，这里不需要分成三个成员变量来保存，只需要写三个Q_PROPERTY及其函数即可
*/

#include <QDebug>
#include <QString>
#include <QObject>
#include "utils/Vec2.h"
#include "utils/Vec3.h"

namespace solar
{
    class RayTracingParameter : public QObject
    {
        Q_OBJECT
        Q_PROPERTY(QString ray_cnt READ readRayCnt WRITE writeRayCnt NOTIFY rayCntChanged)
        Q_PROPERTY(QString pixel_length READ readPixelLength WRITE writePixelLength NOTIFY pixelLengthChanged)
        Q_PROPERTY(QString subheliostat_length READ readSubheliostatLength WRITE writeSubheliostatLength NOTIFY subheliostatLengthChanged)
        Q_PROPERTY(QString scene_grid_x READ readSceneGridX WRITE writeSceneGridX NOTIFY sceneGridXChanged)
        Q_PROPERTY(QString scene_grid_y READ readSceneGridY WRITE writeSceneGridY NOTIFY sceneGridYChanged)
        Q_PROPERTY(QString scene_grid_z READ readSceneGridZ WRITE writeSceneGridZ NOTIFY sceneGridZChanged)

    public:
        RayTracingParameter(){      //设置初始数据
            ray_cnt_ = 100;
            pixel_length_ = 0.01;
            subheliostat_length_ = 0.01;
            scene_grid_size_ = Vec3(0,0,0); 
        }

        QString readRayCnt();   // 把ray_cnt_转换为QString用于ui读取
        void writeRayCnt(const QString& str);   // 用从ui传来的QString更新ray_cnt_

        QString readPixelLength();   // 把pixel_size_转换为QString用于ui读取
        void writePixelLength(const QString& str);   // 用从ui传来的QString更新pixel_size_

        QString readSubheliostatLength();   // 把subheliostat_size_转换为QString用于ui读取
        void writeSubheliostatLength(const QString& str);   // 用从ui传来的QString更新subheliostat_size_

        QString readSceneGridX();   
        void writeSceneGridX(const QString& str); 
        QString readSceneGridY();   
        void writeSceneGridY(const QString& str);
        QString readSceneGridZ();   
        void writeSceneGridZ(const QString& str);  

    signals:
        QString rayCntChanged();        // 信号，不需要实现，在qml里绑定即可
        QString pixelLengthChanged(); 
        QString subheliostatLengthChanged(); 
        QString sceneGridXChanged(); 
        QString sceneGridYChanged(); 
        QString sceneGridZChanged(); 

    private:
        int ray_cnt_;   // 进行仿真的光线数目
        double pixel_length_;   // 接收器像素尺寸
        double subheliostat_length_;    //微定日镜尺寸
        Vec3 scene_grid_size_;     //对整个场景进行划分，---三维的,每个维度都可能不一样大
        //Vec3 scene_size_;           // 整个场景的包围盒的大小


    };
}


#endif