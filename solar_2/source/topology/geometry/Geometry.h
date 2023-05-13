
#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <vector>

#include <QVariant>
#include<QDebug>

#include"utils/Vec3.h"
#include <any>
#include"utils/Utils.h"
#include "utils/Vec2.h"

namespace solar{

    enum GeometryType{
        kGeometryRectangle,
        kGeometryParabolic,
        kGeometryHyperbolic,
        kGeometryElliptic,
        kGeometryBSpline,
        kGeometryMesh
    };

    class Geometry
    {
    public:
        Geometry();

        virtual void setPara(const int property_type, const QVariant& value) = 0;
        virtual auto getPara(const int property_type) const -> QVariant = 0;
        virtual GeometryType getType()=0;

//    protected:
//        GeometryType type_;

        


    };

    

    

   

   

   
   

    
    // //圆锥面
    // class Cone : public Geometry
    // {
    // public:
    //     void setPara(const int property_type, const QVariant& value) override;
    //     auto getPara(const int property_type) const -> QVariant override ;
    //     GeometryType getType() override { return type_;   }
    // private:
    //     double height_;
    //     double up_radius_;
    //     double down_radius_;

    //     GeometryType type_;
    // };


    // /*
    //  * ===================================================================
    //  * 下面这些先放一放,
    //  * 等前面的写好，再做下面的
    //     */

    // //立方体
    // class Cube : public Geometry
    // {
    // public:

    // private:
    //     Vec3 size;  //三个维度上的长度
    // };

    // //球面
    // class Sphere : public Geometry
    // {
    // public:

    // private:
    //     double radius;   //半径

    // };



    // class FunctionZ : public Geometry
    // {
    // public:

    // private:
    //     std::string function;   // 显式方程

    // };
    // class FunctionXYZ : public Geometry
    // {
    // public:

    // private:
    //     std::string function;   // 隐式方程

    // };

}

#endif // SHAPERT_H
