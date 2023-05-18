
#ifndef SUNPOSITION_H
#define SUNPOSITION_H

/*

*/

#include <QVariant>

#include "utils/Utils.h"

#include <boost/describe.hpp>

namespace solar
{

    class SunPosition
    {
        public:
            SunPosition(double azimuth = 0, double elevation = 90, double irradiance = 1000,
                        bool trackable = true)
                : azimuth_(azimuth), elevation_(elevation), irradiance_(irradiance),
                  trackable_(trackable)
            {
            }

            void setPara(const std::string& property_type, const QVariant& value);
            [[nodiscard]] auto getPara(const std::string& property_type) -> QVariant;
            void testPrint() const;
#include <utils/class_name.inc>

        private:
            double azimuth_;    // 方位角
            double elevation_;  // 高度角
            double irradiance_; // 辐射强度
            bool trackable_;    // 是否可追踪
            BOOST_DESCRIBE_CLASS(SunPosition, (), (), (), (azimuth_, elevation_, irradiance_, trackable_))
    };

} // namespace solar

#endif // SUNPOSITION_H
