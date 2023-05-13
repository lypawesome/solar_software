#include "topology/geometry/Geometry.h"

namespace solar
{
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
        Vec2 size_;     //在投影面的长和宽
        GeometryType type_;
    };
}