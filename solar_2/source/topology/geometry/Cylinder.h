#include "topology/geometry/Geometry.h"

#include <boost/describe.hpp>

namespace solar
{
    // 柱面
    class Cylinder : public Geometry
    {
        public:
            void setPara(const std::string& property_type, const QVariant& value) override;
            auto getPara(const std::string& property_type) -> QVariant override;
            [[nodiscard]] auto getType() const -> GeometryType override { return type_; }
#include <utils/class_name.inc>

        private:
            double height_;
            double radius_;

            GeometryType type_;
            BOOST_DESCRIBE_CLASS(Cylinder, (Geometry), (), (), (height_, radius_, type_))
    };

} // namespace solar