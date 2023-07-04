#pragma once

#include <boost/describe.hpp>

#include <utils/HasValue.h>
#include <utils/Para.h>
#include <utils/Vec2.h>


namespace solar
{
    /// \brief 场景参数-各定日镜单独设置的部分（镜面为玻璃的定日镜）
    /// 若无特殊说明，Vec类型的分量顺序为(x, y, z)
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

            double refractivity_ = kUndefined;    // 折射率
            Vec2 sigma_glass_down_slope_error_{}; // 玻璃底面上的微表面法向扰动（mrad）

            // Auto-generated Part

            Vec2 sigma_glass_refract_1_{}; // 玻璃表面上第一次折射的光学误差（mrad）
            Vec2 sigma_glass_reflect_{};   // 玻璃底面上反射的光学误差（mrad）
            Vec2 sigma_glass_refract_2_{}; // 玻璃表面上第二次折射的光学误差（mrad）

            BOOST_DESCRIBE_CLASS(HeliostatWithGlassPara, (Para), (), (),
                                 (refractivity_, sigma_glass_down_slope_error_,
                                  sigma_glass_refract_1_, sigma_glass_reflect_,
                                  sigma_glass_refract_2_))
    };
} // namespace solar
