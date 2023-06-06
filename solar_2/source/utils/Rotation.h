
#ifndef ROTATION_H
#define ROTATION_H

/*
旋转：包括旋转轴、旋转角度
*/

#include "utils/Utils.h"
#include "utils/Vec3.h"

#include <any>
#include <unordered_map>

#include <QVariant>

#include <boost/describe.hpp>

namespace solar
{
    class Rotation
    {
        public:
            Rotation(const Vec3& axis = Vec3(1, 0, 0), double angle = 0)
                : axis_(axis), angle_(angle)
            {
                qDebug()<<"====================use rotation default construct==========";
            }
            Rotation(double a, double b, double c, double d)
            {
                Rotation(Vec3(a,b,c),d);
            }

            void setPara(const std::string& property_type, const QVariant& value);
            auto getPara(const std::string& property_type) -> QVariant;
            void testPrint() const;

            // 转化为string，前三个表示axis，最后一个数表示angle
            auto rotation2String() ->std::string
            {
                return axis_.vec32String() +","+ double2String(angle_);
            }

#include <utils/class_name.inc>

        private:
            Vec3 axis_;    // 旋转轴
            double angle_; // 旋转角度
            BOOST_DESCRIBE_CLASS(solar::Rotation, (), (), (), (axis_, angle_))
    };
} // namespace solar

Q_DECLARE_METATYPE(solar::Rotation)

#endif // ROTATION_H
