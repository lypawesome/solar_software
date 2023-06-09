#pragma once

#include <boost/describe.hpp>

#include "utils/Para.h"
#include <utils/Vec2.h>

namespace solar
{
    class SimulationPara : public Para
    {
        public:
            SimulationPara() = default;
            void setPara(const std::string& property_type, const QVariant& value) override;
            [[nodiscard]] auto getPara(const std::string& property_type) -> QVariant override;
            void testPrint() const override;
#include <utils/class_name.inc>
        private:
            Vec2 receiver_pixel_size_;
            Vec2 micro_heliostat_pixel_size_;
            BOOST_DESCRIBE_CLASS(SimulationPara, (Para), (), (),
                                 (receiver_pixel_size_, micro_heliostat_pixel_size_))
    };
} // namespace solar
