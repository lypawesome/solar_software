#include "topology/geometry/Geometry.h"

namespace solar
{
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

}