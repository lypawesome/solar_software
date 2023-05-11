
#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <vector>

#include <QVariant>
#include<QDebug>

#include "Vec3.h"
#include <any>
#include "Utils.h"

namespace solar{

    enum GeometryType{
        kGeometryPlanar,
        kGeometryParabolic,
        kGeometryHyperbolic,
        kGeometryElliptic,
        kGeometryBSpline,
        kGeometryMap
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

    //平面，不需要额外设置参数
    class Planar : public Geometry
    {
    public:
        Planar() : type_(kGeometryPlanar){};

        GeometryType getType()override { return type_;   }

    private:
        GeometryType type_;
    };

    //抛物面:z=x^2/a^2 + y^2/b^2
    class Parabolic : public Geometry
    {
    public:
        Parabolic(double a=1, double b=1)
            :a_(a), b_(b),type_(kGeometryParabolic) { }

        void setPara(const int property_type, const QVariant& value) override;
        auto getPara(const int property_type) const -> QVariant override ;
        GeometryType getType()override { return type_;   }

    private:
        double a_;
        double b_;
        GeometryType type_;
    };

    //双曲面:z^2/c^2-x^2/a^2-y^2/b^2=1
    class Hyperbolic :public Geometry
    {
    public:
        Hyperbolic(double a=1, double b=1, double c=1 )
            :a_(a), b_(b),c_(c),type_(kGeometryHyperbolic)  { }

        void setPara(const int property_type, const QVariant& value) override;
        auto getPara(const int property_type) const -> QVariant override ;
        GeometryType getType()override { return type_;   }

    private:
        double a_;
        double b_;
        double c_;
        GeometryType type_;
    };

    //椭球面面:x^2/a^2 + y^2/b^2 + z^2/c^2 = 1
    class Elliptic : public Geometry
    {
    public:
        Elliptic(double a=1, double b=1, double c=1 )
            :a_(a), b_(b),c_(c),type_(kGeometryElliptic)  { }

        void setPara(const int property_type, const QVariant& value) override;
        auto getPara(const int property_type) const -> QVariant override ;
        GeometryType getType()override { return type_;   }

    private:
        double a_;
        double b_;
        double c_;
        GeometryType type_;
    };

    /*
     * B样条曲面--无理B样条
     * 第一种方法：进行插值计算，计算得出B样条曲面
     *      给出插值点，两个方向上插值点的个数，两个方向上的阶数，以及节点向量生成方法、参数生成方法
     *      插值得出控制顶点，即得到了B样条曲面的表达式
     * 第二种方法：插值过程另外计算，直接给出B样条曲面的表达式
     *      给出：控制顶点、两个方向上控制顶点的个数、两个方向上的节点向量、两个方向上的阶数
     *      每次给定(u,v)值，计算出两个方向上的基函数，通过B样条曲面的公式计算得到一个值w
     *      取若干个这样的(u,v)点，则（u，v，w）组成的面就是B样条曲面
     * 选择第二种方法
     * 【参考-应用几何造型GM09章节ppt、教材-非均匀有理B样条】
     * 问题：是否需要使用NURBS进行表示？？？
    */
    class BSpline : public Geometry
    {
    public:
        BSpline() : file_(""),type_(kGeometryBSpline) { }

        void setPara(const int property_type, const QVariant& value) override;
        auto getPara(const int property_type) const -> QVariant override ;
        GeometryType getType()override { return type_;   }
        void readFile();    //读取文件

    private:
        std::string file_;   // 文件，从该文件中读入B样条曲面的各种信息
        GeometryType type_;

        int cnt_u_, cnt_v_;       //两个方向的控制点个数分别为：cnt_u + 1,  cnt_v+1
        int order_u_, order_v_;   //两个方向的阶数分别为：order_u、order_v
        std::vector<std::vector<Vec3>> control_points_;   //控制顶点
        std::vector<double> knot_u_, knot_v_;     //两个方向的节点向量


    };

    /*
     * 自定义
     * 读入mesh(.obj)文件，这个文件记录了定日镜上各个点的位置、法向信息
    */
    class Map : public Geometry
    {
    public:
        Map() : file_(""), type_(kGeometryMap) { }

        void setPara(const int property_type, const QVariant& value) override;
        auto getPara(const int property_type) const -> QVariant override ;
        GeometryType getType() override { return type_;   }
        void readFile();    //读取文件

    private:
        std::string file_;
        GeometryType type_;

        std::vector<std::vector<Vec3>> points_;
        std::vector<std::vector<Vec3>> normals_;
    };

    //柱面
    class Cylinder : public Geometry
    {
    public:
        void setPara(const int property_type, const QVariant& value) override;
        auto getPara(const int property_type) const -> QVariant override ;
        GeometryType getType() override { return type_;   }
    private:
        double height_;
        double radius_;

        GeometryType type_;
    };

    //圆锥面
    class Cone : public Geometry
    {
    public:
        void setPara(const int property_type, const QVariant& value) override;
        auto getPara(const int property_type) const -> QVariant override ;
        GeometryType getType() override { return type_;   }
    private:
        double height_;
        double up_radius_;
        double down_radius_;

        GeometryType type_;
    };


    /*
     * ===================================================================
     * 下面这些先放一放,
     * 等前面的写好，再做下面的
        */

    //立方体
    class Cube : public Geometry
    {
    public:

    private:
        Vec3 size;  //三个维度上的长度
    };

    //球面
    class Sphere : public Geometry
    {
    public:

    private:
        double radius;   //半径

    };



    class FunctionZ : public Geometry
    {
    public:

    private:
        std::string function;   // 显式方程

    };
    class FunctionXYZ : public Geometry
    {
    public:

    private:
        std::string function;   // 隐式方程

    };

}

#endif // SHAPERT_H
