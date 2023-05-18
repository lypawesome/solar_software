#ifndef NODE_H
#define NODE_H

#include "utils/Para.h"
#include "utils/Rotation.h"
#include "utils/Utils.h"

#include <boost/describe.hpp>

namespace solar
{
    class Node : public Para
    {
        public:
            virtual ~Node() = default;
            Node(const Vec3& translation = Vec3(0, 0, 0), const Vec3& rotation_axis = Vec3(0, 0, 1),
                 double rotation_angle = 0.0, const Vec3& scale = Vec3(1, 1, 1))
                : translation_(translation), rotation_(Rotation(rotation_axis, rotation_angle)),
                  scale_(scale)
            {
            }

            void setPara(const std::string& property_type, const QVariant& value) override;
            [[nodiscard]] auto getPara(const std::string& property_type) -> QVariant override;
            void testPrint() const override;
#include <utils/class_name.inc>

        private:
            Vec3 translation_;  // 位移
            Rotation rotation_; // 旋转
            Vec3 scale_;        // 放缩
            BOOST_DESCRIBE_CLASS(Node, (Para), (), (), (translation_, rotation_, scale_))
    };

} // namespace solar

#endif