
#ifndef PROFILE_H
#define PROFILE_H

/*

    Geometry的轮廓
    相当于Geometry在二维的平面上的投影
*/

#include "Vec2.h"
#include <string>

namespace solar
{

    class Profile
    {
    public:
        Profile();
    };

    //这个类，貌似会导致闪退的bug
//    class Box : public ProfileRT
//    {

//    };

    //矩形轮廓
    class Rectangular : public Profile
    {
    private:
        Vec2 u;     //Vec2两个分量，分表表示uMin,uMax
        Vec2 v;
    };

    //圆形、扇形、环形轮廓
    class Circular : public Profile
    {
    private:
        Vec2 r;     //半径，两个分量：rMin,rMax
        Vec2 phi;   //角度，两个分量：phiMin,phiMax
    };

    //规则多边形
    class Regular : public Profile
    {
        int r;      //边的长度
        int n;      //边的个数
    };

    //三角形轮廓
    class Triangle : public Profile
    {
    private:
        Vec2 a;     //三个顶点的位置
        Vec2 b;
        Vec2 c;
    };

    //多边形
    class Polygon : public Profile
    {
    private:
        std::string points;     //输入一系列点的坐标
    };
}

#endif // PROFILERT_H