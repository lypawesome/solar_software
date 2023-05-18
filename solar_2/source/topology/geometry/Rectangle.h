#include "topology/geometry/Geometry.h"
#include <utils/Vec2.h>

#include <boost/describe.hpp>

namespace solar
{
    // 平面，不需要额外设置参数
    class Rectangle : public Geometry
    {
        public:
            Rectangle() = default;

            void setPara(const std::string& property_type, const QVariant& value) override;
            auto getPara(const std::string& property_type) -> QVariant override;
            [[nodiscard]] auto getType() const -> GeometryType override { return type_; }
#include <utils/class_name.inc>

        private:
            Vec2 size_; // size_.x--长，size_.y--宽
            GeometryType type_ = kGeometryRectangle;
            BOOST_DESCRIBE_CLASS(Rectangle, (Geometry), (), (), (size_, type_))
    };
} // namespace solar