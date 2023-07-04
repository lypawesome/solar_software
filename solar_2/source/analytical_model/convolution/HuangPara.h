#pragma once

#include <boost/describe.hpp>

#include <analytical_model/ModelPara.h>
#include <utils/HasValue.h>
#include <utils/Vec2.h>

namespace solar
{
    class HuangPara : public ModelPara
    {
        public:
            HuangPara() = default;
            void setPara(const std::string& property_type, const std::any& value) override;
            [[nodiscard]] auto getPara(const std::string& property_type) -> std::any override;
#include <utils/class_name.inc>
        private:
            double sigma_x_ = kUndefined;
            double sigma_y_ = kUndefined;
            BOOST_DESCRIBE_CLASS(HuangPara, (ModelPara), (), (), (sigma_x_, sigma_y_))
    };
} // namespace solar
