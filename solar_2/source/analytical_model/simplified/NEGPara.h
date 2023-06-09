#pragma once

#include <boost/describe.hpp>

#include <analytical_model/ModelPara.h>

namespace solar
{
    class NEGPara : public ModelPara
    {
        public:
            NEGPara() = default;
            void setPara(const std::string& property_type, const std::any& value) override;
            [[nodiscard]] auto getPara(const std::string& property_type) -> std::any override;
#include <utils/class_name.inc>
        private:
            double flux_param_; // 定日镜反射光斑总能量
            double sigma_x_;
            double sigma_y_;
            double bias_x_;
            double bias_y_;
            BOOST_DESCRIBE_CLASS(NEGPara, (ModelPara), (), (),
                                 (flux_param_, sigma_x_, sigma_y_, bias_x_, bias_y_))
    };
} // namespace solar
