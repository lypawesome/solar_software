#include "topology/geometry/Geometry.h"

namespace solar
{
    //平面，不需要额外设置参数
    class Rectangle : public Geometry
    {
    public:
        Rectangle() : type_(kGeometryRectangle){};

        GeometryType getType()override { return type_;   }

    private:
        Vec2 size_;                 //size_.x--长，size_.y--宽
        GeometryType type_;
    };
}