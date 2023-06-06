#ifndef HYPERBOLIC_H
#define HYPERBOLIC_H

#include "topology/geometry/Geometry.h"
#include <utils/Vec2.h>

#include <boost/describe.hpp>

namespace solar
{
    // 双叶双曲面:z^2/c^2-x^2/a^2-y^2/b^2=1
    class Hyperbolic : public Geometry
    {
        public:
            Hyperbolic(double a = 1, double b = 1, double c = 1) : a_(a), b_(b), c_(c) {}

            void setPara(const std::string& property_type, const QVariant& value) override;
            auto getPara(const std::string& property_type) -> QVariant override;
            [[nodiscard]] auto getType() const -> GeometryType override { return type_; }
#include <utils/class_name.inc>

        private:
            double a_;
            double b_;
            double c_;
            Vec2 size_; // 在投影面的长和宽
            GeometryType type_ = kGeometryHyperbolic;
            BOOST_DESCRIBE_CLASS(Hyperbolic, (Geometry), (), (), (a_, b_, c_, size_, type_))
    };
} // namespace solar

#endif