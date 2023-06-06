#ifndef ABSORB_H
#define ABSORB_H

/**
 * ！！！！看一下师姐的算法：是用Fresnel计算的反射率还是自己设置的反射率
 *          -是用Fresnel的空气、玻璃折射率计算出来的反射率
 * 先写着，反正还能改
 * ！！！！注意：这里的thickness与Heliostat的thickness重复了...保留否？
*/

#include "topology/material/Material.h"

namespace solar
{
     // 玻璃层---吸收、反射、折射
    // 注意这里的反射是用fresnel计算得到的
    class Refract : public Material
    {
        public:
            Refract()
            {
                reflectivity_ = 0.88;       
                transmissivity_ = 0.1;
                air_refractive_index_ = 1.0;
                glass_refractive_index_ = 1.5 ;
                glass_thickness_ = 0.5;       //！！！！单位cm，暂时这样设定
                slope_error_type_ = kGaussianSlopeError;
                slope_ = 0.02;
                type_ = kMaterialRefract;
                
            };

            void setPara(const std::string& property_type, const QVariant& value) override;
            auto getPara(const std::string& property_type) -> QVariant override;
            [[nodiscard]] auto getType() const -> MaterialType override;
            void testPrint() const override;
#include <utils/class_name.inc>

        private:
            // 反射率通过Fresnel计算得到，
            double reflectivity_; // 反射率---可以通过Fresnel计算得到----不可以自己设置，不放到UI层
            double transmissivity_; // 透射率---进入到玻璃内的概率,可以自己设置
            // double absorptivity_;       //吸收率 = 1-反射率-透射率 ----- 不用自己设置

            double air_refractive_index_;   // 空气的折射率
            double glass_refractive_index_; // 玻璃的折射率  通过这两个参数可以计算反射率
            double glass_thickness_;              // 玻璃层的厚度

            SlopeErrorType slope_error_type_;
            double slope_;

            MaterialType type_;
            BOOST_DESCRIBE_CLASS(solar::Refract, (solar::Material), (), (),
                                 (reflectivity_, transmissivity_, air_refractive_index_,
                                  glass_refractive_index_, glass_thickness_, slope_error_type_, slope_ ))
    };
    

}

#endif