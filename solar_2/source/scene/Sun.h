#ifndef SUN_H
#define SUN_H

#include "utils/Para.h"
#include "utils/Utils.h"

#include <boost/describe.hpp>

namespace solar
{
    class SunShape;
    class SunPosition;

    class Sun : public Para
    {
        public:
            Sun();
            // {
            //     sunshape_ = std::make_shared<PillboxSunShape>(); // 先放高斯
            //     sun_position_ = std::make_shared<SunPosition>();
            // }

            void setPara(const std::string& property_type, const QVariant& value) override;
            [[nodiscard]] auto getPara(const std::string& property_type) -> QVariant override;
            void testPrint() const override;
#include <utils/class_name.inc>

        private:
            std::shared_ptr<SunShape> sunshape_;
            std::shared_ptr<SunPosition> sun_position_;

            BOOST_DESCRIBE_CLASS(Sun, (Para), (), (), (sunshape_, sun_position_))
    };

} // namespace solar

#endif