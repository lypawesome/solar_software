#pragma once

#include <boost/describe.hpp>

#include <utils/Para.h>
#include <utils/HasValue.h>

#include <memory>

namespace solar
{
    class SunPosition;

    class ScenePara : public Para
    {
        public:
            ScenePara() = default;
            void setPara(const std::string& property_type, const QVariant& value) override;
            [[nodiscard]] auto getPara(const std::string& property_type) -> QVariant override;
            void testPrint() const override;
#include <utils/class_name.inc>

        private:
            double DNI_ = kUndefined;                                // 太阳直接辐射强度
            double CSR_ = kUndefined;                                // 太阳光分布参数
            std::shared_ptr<SunPosition> sun_position_; // 太阳位置
            BOOST_DESCRIBE_CLASS(ScenePara, (Para), (), (), (DNI_, CSR_, sun_position_))
    };
} // namespace solar
