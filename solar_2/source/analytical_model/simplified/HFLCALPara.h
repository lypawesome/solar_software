#pragma once

#include <boost/describe.hpp>

#include <analytical_model/ModelPara.h>

namespace solar
{
    class HFLCALPara : public ModelPara
    {
        public:
            HFLCALPara() = default;
            void setPara(const std::string& property_type, const std::any& value) override;
            [[nodiscard]] auto getPara(const std::string& property_type) -> std::any override;
#include <utils/class_name.inc>
        private:
            double sigma_; // 圆形高斯sigma
            BOOST_DESCRIBE_CLASS(HFLCALPara, (ModelPara), (), (), (sigma_))
    };
} // namespace solar
