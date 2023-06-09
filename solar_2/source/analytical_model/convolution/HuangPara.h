#pragma once

#include <boost/describe.hpp>

#include <analytical_model/ModelPara.h>

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
            double sigma_x_{};
            double sigma_y_{};
            BOOST_DESCRIBE_CLASS(HuangPara, (ModelPara), (), (), (sigma_x_, sigma_y_))
    };
} // namespace solar
