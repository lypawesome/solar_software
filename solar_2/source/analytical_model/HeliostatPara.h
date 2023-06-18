#pragma once

#include <boost/describe.hpp>

#include "utils/Para.h"
#include "utils/Vec2.h"

#include <cstdint>
#include <memory>

namespace solar
{
    class Heliostat;
    class HeliostatWithGlassPara;

    /// \brief 场景参数-各定日镜单独设置的部分
    /// 若无特殊说明，Vec类型的分量顺序为(x, y, z)
    class HeliostatPara : public Para
    {
        public:
            HeliostatPara() = default;

            void setPara(const std::string& property_type, const QVariant& value) override;
            [[nodiscard]] auto getPara(const std::string& property_type) -> QVariant override;
            void testPrint() const override;
#include <utils/class_name.inc>

        private:
            std::uint64_t heliostat_id_{}; // 定日镜编号
            std::uint64_t receiver_id_{};  // 接收器编号
            double mirror_area_{};         // 镜面面积（m^2）
            double total_area_{};          // 定日镜总面积（m^2）
            double reflectivity_{};        // 反射率
            double sigma_tracking_{};      // 跟踪误差（mrad）
            Vec2 sigma_slope_error_{};   // 定日镜表面上的微表面法向扰动（mrad）
            // 镜面为玻璃的定日镜的额外参数
            std::shared_ptr<HeliostatWithGlassPara> heliostat_glass_para_;

            // Auto-generated Part

            double air_attenuation_efficiency_{}; // 大气透射效率
            double distance_to_focus_center_{};   // 定日镜中心与聚焦点距离（m）
            double sigma_astigmatism_{};          // 散光误差（mrad）
            double sigma_beam_quality_{};         // 光束质量误差（mard）

            BOOST_DESCRIBE_CLASS(HeliostatPara, (Para), (), (),
                                 (heliostat_id_, receiver_id_, mirror_area_, total_area_,
                                  reflectivity_, sigma_tracking_, sigma_slope_error_,
                                  heliostat_glass_para_, air_attenuation_efficiency_,
                                  distance_to_focus_center_, sigma_astigmatism_,
                                  sigma_beam_quality_))
    };
} // namespace solar
