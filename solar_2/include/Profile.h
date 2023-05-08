
#ifndef PROFILE_H
#define PROFILE_H

/*
    Geometry的轮廓
    相当于Geometry在二维的平面上的投影
*/

#include "Vec2.h"
#include <string>
#include <QVariant>
#include "Utils.h"

namespace solar
{
    enum ProfileType{
        kProfileRectangular,
        kProfileCircular,
        kProfileRegular,
        kProfileTriangle,
        kProfilePolygon
    };

    class Profile
    {
    public:
        Profile();

        virtual void setPara(const int property_type, const QVariant& value) = 0 ;
        virtual auto getPara(const int property_type) const -> QVariant = 0 ;
        virtual auto getType() const ->ProfileType = 0 ;
        virtual void testPrint() const = 0 ;
    };

    //这个类，貌似会导致闪退的bug
//    class Box : public ProfileRT
//    {

//    };

    //矩形轮廓
    class Rectangular : public Profile
    {
    public:
        Rectangular(const Vec2& rect_u, const Vec2& rect_v)
            : rect_u_(rect_u), rect_v_(rect_v), type_(kProfileRectangular) {}

        void setPara(const int property_type, const QVariant& value) override ;
        auto getPara(const int property_type) const -> QVariant override ;
        void testPrint() const override ;
        auto getType() const ->ProfileType override
        {return type_;}

    private:
        Vec2 rect_u_;     //Vec2两个分量，分表表示uMin,uMax
        Vec2 rect_v_;

        ProfileType type_;
    };

    //圆形、扇形、环形轮廓
    class Circular : public Profile
    {
    public:
        Circular(const Vec2& circle_radius, const Vec2& circle_phi)
            : circle_radius_(circle_radius), circle_phi_(circle_phi), type_(kProfileCircular) {}

        void setPara(const int property_type, const QVariant& value) override ;
        auto getPara(const int property_type) const -> QVariant override ;
        void testPrint() const override ;
        auto getType() const ->ProfileType override
        {return type_;}

    private:
        Vec2 circle_radius_;     //半径，两个分量：rMin,rMax
        Vec2 circle_phi_;   //角度，两个分量：phiMin,phiMax

        ProfileType type_;
    };

    //规则多边形
    class Regular : public Profile
    {
    public:
        Regular(int regular_edge_length, int regular_edge_cnt)
            : regular_edge_length_(regular_edge_length), regular_edge_cnt_(regular_edge_cnt),
              type_(kProfileRegular)      {}

        void setPara(const int property_type, const QVariant& value) override ;
        auto getPara(const int property_type) const -> QVariant override ;
        void testPrint() const override ;
        auto getType() const ->ProfileType override
        {return type_;}

    private:
        int regular_edge_length_;      //边的长度
        int regular_edge_cnt_;      //边的个数

        ProfileType type_;
    };

    //三角形轮廓
    class Triangle : public Profile
    {
    public:
        Triangle(const Vec2& tri_a, const Vec2& tri_b, const Vec2& tri_c)
            : tri_a_(tri_a), tri_b_(tri_b), tri_c_(tri_c), type_(kProfileTriangle) {}

        void setPara(const int property_type, const QVariant& value) override ;
        auto getPara(const int property_type) const -> QVariant override ;
        void testPrint() const override ;
        auto getType() const ->ProfileType override
        {return type_;}

    private:
        Vec2 tri_a_;     //三个顶点的位置
        Vec2 tri_b_;
        Vec2 tri_c_;

        ProfileType type_;
    };

    //多边形
    class Polygon : public Profile
    {
    public:
        Polygon():poly_points_(""), type_(kProfileTriangle) {}

        void setPara(const int property_type, const QVariant& value) override ;
        auto getPara(const int property_type) const -> QVariant override ;
        void testPrint() const override ;
        auto getType() const ->ProfileType override
        {return type_;}

    private:
        std::string poly_points_;     //输入一系列点的坐标

        ProfileType type_;
    };
}

#endif // PROFILERT_H
