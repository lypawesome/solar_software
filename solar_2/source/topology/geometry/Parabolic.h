#ifndef PARABOLIC_H
#define PARABOLIC_H

#include "topology/geometry/Geometry.h"
#include <utils/Vec2.h>

#include <boost/describe.hpp>

namespace solar
{
    // 抛物面:z=x^2/a^2 + y^2/b^2
    class Parabolic : public Geometry
    {
        public:
            Parabolic(double a = 1, double b = 1) : a_(a), b_(b) {}

            void setPara(const std::string& property_type, const QVariant& value) override;
            auto getPara(const std::string& property_type) -> QVariant override;
            [[nodiscard]] auto getType() const -> GeometryType override { return type_; }
#include <utils/class_name.inc>

        private:
            double a_;
            double b_;
            Vec2 size_; // 在投影面的长和宽
            GeometryType type_ = kGeometryParabolic;
            BOOST_DESCRIBE_CLASS(Parabolic, (Geometry), (), (), (a_, b_, size_, type_))
    };
} // namespace solar

#endif