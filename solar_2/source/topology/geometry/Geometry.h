
#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <QVariant>

#include <string>

namespace solar
{

    enum GeometryType
    {
        kGeometryRectangle,
        kGeometryParabolic,
        kGeometryHyperbolic,
        kGeometryElliptic,
        kGeometryBSpline,
        kGeometryMesh,

        kGeometryCylinder,
        kGeometryMultiPanelComprisedOfHeatTube,
        kGeometryRectangle3D,
    };

    class Geometry
    {
        public:
            virtual ~Geometry() = default;
            //这里不必写抽象类的构造函数，会报错...不明原因

            virtual void setPara(const std::string& property_type, const QVariant& value) = 0;
            virtual auto getPara(const std::string& property_type) -> QVariant = 0;
            [[nodiscard]] virtual auto getType() const -> GeometryType = 0;

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

} // namespace solar

#endif // SHAPERT_H
