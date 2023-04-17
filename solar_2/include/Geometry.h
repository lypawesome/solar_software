
#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <vector>

#include "Profile.h"
#include "Vec3.h"
#include "Vec2.h"
#include "Ray.h"

namespace solar{

    //记录相交的交点信息
    struct IntersectInfo{
        Vec3 in_point;     //入射光与物体的交点坐标
        Vec3 out_point;     //入射点与出射点不一定是同一个
        Vec3 normal;        //交点所在的Geometry的法向，求出射光线时要计算法向扰动
        Ray in_ray;     //入射光线
        Ray out_ray;    //出射光线
    };

    class Geometry
    {
    public:
        Geometry();

        virtual Profile getProfile() const;

        //=================这些函数以后再加=====================
//        virtual Vec3 getPoint(double u, double v) const;    //根据平面投影点得到Geometry上的点
//        virtual Vec3 getNormal(double u, double v) const;
//        virtual Vec3 getDerivativeU(double u,double v) const;
//        virtual Vec3 getDerivativeV(double u, double v) const;
//        //double findArea(double u0, double v0, double u1, double v1)const;

//        virtual Vec2 getUV(const Vec3& p) const;        //根据Geometry上的点得到投影面上的点

        virtual bool intersect(Ray in_ray, IntersectInfo& intersection)const = 0;           // 最重要的函数!!!求交

    };

    //平面，不需要额外设置参数
    class Planar : public Geometry
    {
    public:
        Planar(std::shared_ptr<Profile> _profile=nullptr):profile(_profile){};

        bool intersect(Ray in_ray, IntersectInfo& intersection)const;
    private:
        std::shared_ptr<Profile> profile;
    };

    //抛物面:z=x^2/a^2 + y^2/b^2
    class Parabolic : public Geometry
    {
    public:
        bool intersect(Ray in_ray, IntersectInfo& intersection)const;

    private:
        double a;
        double b;
        std::shared_ptr<Profile> profile;
    };

    //双曲面:z^2/c^2-x^2/a^2-y^2/b^2=1
    class Hyperbolic :public Geometry
    {
    public:
        bool intersect(Ray in_ray, IntersectInfo& intersection)const;

    private:
        double a;
        double b;
        double c;
        std::shared_ptr<Profile> profile;
    };

    //椭球面面:x^2/a^2 + y^2/b^2 + z^2/c^2 = 1
    class Elliptic : public Geometry
    {
    public:
        bool intersect(Ray in_ray, IntersectInfo& intersection)const;

    private:
        double a;
        double b;
        double c;
        std::shared_ptr<Profile> profile;
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
        bool intersect(Ray in_ray, IntersectInfo& intersection)const;

    private:
        int cnt_u, cnt_v;    //两个方向的控制点个数分别为：cnt_u + 1,  cnt_v+1
        int order_u, order_v;   //两个方向的阶数分别为：k、l
        std::vector<std::vector<Vec3>> control_point;   //控制顶点
        std::vector<double> knot_u, knot_v;     //两个方向的节点向量

        std::shared_ptr<Profile> profile;
    };



    //立方体---不设置profile
    class Cube : public Geometry
    {
    public:
        bool intersect(Ray in_ray, IntersectInfo& intersection)const;

    private:
        Vec3 size;  //三个维度上的长度
    };

    //球面
    class Sphere : public Geometry
    {
    public:
        bool intersect(Ray in_ray, IntersectInfo& intersection)const;
    private:
        double radius;   //半径
        std::shared_ptr<Profile> profile;
    };

    //柱面
    class Cylinder : public Geometry
    {
    public:
        bool intersect(Ray in_ray, IntersectInfo& intersection)const;
    private:
        double height;
        double up_radius;
        double down_radius;
        std::shared_ptr<Profile> profile;
    };

    //圆锥面
    class Cone : public Geometry
    {
    public:
        bool intersect(Ray in_ray, IntersectInfo& intersection)const;
    private:
        double height;
        double radius;
        std::shared_ptr<Profile> profile;
    };

    class FunctionZ : public Geometry
    {
    public:
        bool intersect(Ray in_ray, IntersectInfo& intersection)const;
    private:
        std::string function;   // 显式方程
        std::shared_ptr<Profile> profile;
    };
    class FunctionXYZ : public Geometry
    {
    public:
        bool intersect(Ray in_ray, IntersectInfo& intersection)const;
    private:
        std::string function;   // 隐式方程
        std::shared_ptr<Profile> profile;
    };

}

#endif // SHAPERT_H
