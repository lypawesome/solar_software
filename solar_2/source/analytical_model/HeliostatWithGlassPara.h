#pragma once

#include <boost/describe.hpp>

#include "utils/Para.h"

namespace solar
{
    /// \brief 场景参数-各定日镜单独设置的部分（镜面为玻璃的定日镜）
    class HeliostatWithGlassPara : public Para
    {
        public:
            HeliostatWithGlassPara() = default;
            void setPara(const std::string& property_type, const QVariant& value) override;
            [[nodiscard]] auto getPara(const std::string& property_type) -> QVariant override;
            void testPrint() const override;
#include <utils/class_name.inc>

        private:
            // Huang-model specific

            double refractivity_{}; // 折射率
            double sigma_glass_refract_x_1_{}; // 玻璃表面x方向上第一次折射的光学误差（mrad）
            double sigma_glass_refract_y_1_{}; // 玻璃表面y方向上第一次折射的光学误差（mrad）
            double sigma_glass_reflect_x_{}; // 玻璃底面x方向上反射的光学误差（mrad）
            double sigma_glass_reflect_y_{}; // 玻璃底面y方向上反射的光学误差（mrad）
            double sigma_glass_refract_x_2_{}; // 玻璃表面x方向上第二次折射的光学误差（mrad）
            double sigma_glass_refract_y_2_{}; // 玻璃表面y方向上第二次折射的光学误差（mrad）
            double sigma_glass_down_slope_error_{}; // 玻璃底面上的微表面法向扰动（mrad）
            BOOST_DESCRIBE_CLASS(HeliostatWithGlassPara, (Para), (), (),
                                 (refractivity_, sigma_glass_refract_x_1_, sigma_glass_refract_y_1_,
                                  sigma_glass_reflect_x_, sigma_glass_reflect_y_,
                                  sigma_glass_refract_x_2_, sigma_glass_refract_y_2_))
    };
} // namespace solar
