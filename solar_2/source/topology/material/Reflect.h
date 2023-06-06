#ifndef ABSORB_H
#define ABSORB_H

#include "topology/material/Material.h"

namespace solar
{
    // Reflect：吸收+反射
    class Reflect : public Material
    {
        public:
            Reflect(){
                reflectivity_ = 0.88;
                slope_error_type_ = kGaussianSlopeError;
                slope_ = 0.02;
                type_ = kMaterialReflect;
            };

            void setPara(const std::string& property_type, const QVariant& value) override;
            auto getPara(const std::string& property_type) -> QVariant override;
            [[nodiscard]] auto getType() const -> MaterialType override;
            void testPrint() const override;
#include <utils/class_name.inc>

        private:
            double reflectivity_;             // 反射率  【默认吸收率=1-反射率】
            SlopeErrorType slope_error_type_; // 法向扰动的类型_枚举值--------！！！！是否直接存成string？？？
            double slope_;

            MaterialType type_;
            BOOST_DESCRIBE_CLASS(solar::Reflect, (solar::Material), (), (),
                                 (reflectivity_, slope_error_type_, slope_))
    };    

}

#endif