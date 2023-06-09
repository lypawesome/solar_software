#pragma once

#include <boost/describe.hpp>

#include <analytical_model/ModelPara.h>

namespace solar
{
    class ICauchyPara : public ModelPara
    {
        public:
            ICauchyPara() = default;
            void setPara(const std::string& property_type, const std::any& value) override;
            [[nodiscard]] auto getPara(const std::string& property_type) -> std::any override;
#include <utils/class_name.inc>
        private:
            double diffusion_coeff_{}; // 扩散系数（公式中的s）
            BOOST_DESCRIBE_CLASS(ICauchyPara, (ModelPara), (), (), ())
    };
} // namespace solar
