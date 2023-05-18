
#ifndef TARGET_H
#define TARGET_H

#include "utils/Utils.h"
#include "utils/Vec2.h"
#include "utils/Vec3.h"

#include <QVariant>

#include <string>

#include <boost/describe.hpp>

namespace solar
{
    class Target
    {
        public:
            Target();
            void setPara(const std::string& property_type, const QVariant& value);
            auto getPara(const std::string& property_type) -> QVariant;
#include <utils/class_name.inc>

        private:
            std::string aiming_type_; // 类型
            Vec3 aiming_point_;       // 目标点
            Vec2 angles_;             // 角度
            BOOST_DESCRIBE_CLASS(solar::Target, (), (), (), (aiming_type_, aiming_point_, angles_))
    };

} // namespace solar

#endif // TARGET_H
