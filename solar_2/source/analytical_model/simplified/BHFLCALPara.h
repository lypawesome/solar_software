#pragma once

#include <boost/describe.hpp>

#include <analytical_model/ModelPara.h>

namespace solar
{
    class BHFLCALPara : public ModelPara
    {
        public:
            BHFLCALPara() = default;
            void setPara(const std::string& property_type, const std::any& value) override;
            [[nodiscard]] auto getPara(const std::string& property_type) -> std::any override;
#include <utils/class_name.inc>
        private:
            // 椭圆高斯sigma_x
            double sigma_x_;
            double bias_x_;
            double bias_y_;

            // Auto Generated

            // 椭圆高斯sigma_y = sigma_x / (1 + log10(l'/w'))
            // l'和w'为l和w（定日镜的长和宽）在图像平面的投影的长度
            double sigma_y_;
            BOOST_DESCRIBE_CLASS(BHFLCALPara, (ModelPara), (), (), (sigma_x_, sigma_y_, bias_x_, bias_y_))
    };
}
