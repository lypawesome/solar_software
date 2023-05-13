#include "topology/geometry/Geometry.h"

namespace solar
{
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
        Vec2 size_;     //在投影面的长和宽
        GeometryType type_;
    };
}