#ifndef CYLINDER_H
#define CYLINDER_H

#include "topology/geometry/Geometry.h"

#include <boost/describe.hpp>

namespace solar
{
    // 柱面
    class Cylinder : public Geometry
    {
        public:
            Cylinder(double height=1,double radius=1) : height_(height),radius_(radius) {}
                                                    
            void setPara(const std::string& property_type, const QVariant& value) override;
            auto getPara(const std::string& property_type) -> QVariant override;
            [[nodiscard]] auto getType() const -> GeometryType override { return type_; }
#include <utils/class_name.inc>

        private:
            double height_;
            double radius_;

            GeometryType type_ = kGeometryCylinder;
            BOOST_DESCRIBE_CLASS(Cylinder, (Geometry), (), (), (height_, radius_))
    };

} // namespace solar

#endif