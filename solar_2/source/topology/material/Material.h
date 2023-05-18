
#ifndef MATERIAL_H
#define MATERIAL_H

/*
 * =====还没想好怎么写，看一下Tonatiuh的源码，跟师姐交流一下
 *
    一个基类，然后派生出几种类型：


派生类中，除了absorb之外均需要设置slopeerror
【先不用SlopeError类，用枚举值+slope，具体如何使用要跟师姐交流一下】
*/

#include "utils/Vec3.h"
// #include "SlopeError.h"

#include <any>

#include <boost/describe.hpp>

namespace solar
{

    enum MaterialType
    {
        kAbsorb,
    };
    enum SlopeErrorType
    {
        kGaussionSlopeError,
        kPillboxSlopeError
    };

    class Material
    {
        public:
            virtual void setPara(const std::string& property_type, const QVariant& value) = 0;
            virtual auto getPara(const std::string& property_type) -> QVariant = 0;
            [[nodiscard]] virtual auto getType() const -> MaterialType = 0;
            virtual void testPrint() const = 0;
    };

    // Absorb：仅吸收
    class Absorb : public Material
    {
        public:
            virtual ~Absorb() = default;
            Absorb() : type_(kAbsorb) {}

            void setPara(const std::string& property_type, const QVariant& value) override;
            auto getPara(const std::string& property_type) -> QVariant override;
            [[nodiscard]] auto getType() const -> MaterialType override;
            void testPrint() const override;
#include <utils/class_name.inc>

        private:
            MaterialType type_;
            BOOST_DESCRIBE_CLASS(solar::Absorb, (solar::Material), (), (), (type_))
    };

    // Reflect：吸收+反射
    class Reflect : public Material
    {
        public:
            Reflect();

            void setPara(const std::string& property_type, const QVariant& value) override;
            auto getPara(const std::string& property_type) -> QVariant override;
            [[nodiscard]] auto getType() const -> MaterialType override;
            void testPrint() const override;
#include <utils/class_name.inc>

        private:
            double reflectivity_;             // 反射率  【默认吸收率=1-反射率】
            SlopeErrorType slope_error_type_; // 法向扰动的类型_枚举值
            double slope_;

            MaterialType type_;
            BOOST_DESCRIBE_CLASS(solar::Reflect, (solar::Material), (), (),
                                 (reflectivity_, slope_error_type_, slope_))
    };

    // 玻璃层---吸收、反射、折射
    // 注意这里的反射是用fresnel计算得到的
    class Refract : public Material
    {
        public:
            Refract();

            void setPara(const std::string& property_type, const QVariant& value) override;
            auto getPara(const std::string& property_type) -> QVariant override;
            [[nodiscard]] auto getType() const -> MaterialType override;
            void testPrint() const override;
#include <utils/class_name.inc>

        private:
            // 反射率通过Fresnel计算得到，
            double reflectivity_; // 反射率---可以通过Fresnel计算得到----不可以自己更改
            double transmissivity_; // 透射率---进入到玻璃内的概率,可以自己设置
            // double absorptivity_;       //吸收率 = 1-反射率-透射率 ----- 不用自己设置

            double air_refractive_index_;   // 空气的折射率
            double glass_refractive_index_; // 玻璃的折射率
            double thickness_;              // 玻璃层的厚度

            SlopeErrorType slope_error_type_;
            double slope_;

            MaterialType type_;
            BOOST_DESCRIBE_CLASS(solar::Refract, (solar::Material), (), (),
                                 (reflectivity_, transmissivity_, air_refractive_index_,
                                  glass_refractive_index_, thickness_, slope_error_type_, slope_,
                                  type_))
    };

    // class Heliostat : public Material
    //{
    // public:
    //     Heliostat();

    //    void setPara(const int property_type, const QVariant& value) override ;
    //    auto getPara(const int property_type) const -> QVariant override;
    //    void testPrint() const override ;

    // private:
    //     Glass glass;
    //     Sliver sliver;
    // };

    // class Material
    //{
    // public:
    //     Material(const Vec3& _ambient_color = Vec3(0.3,0.4,0.5),
    //              const Vec3& _diffuse_color = Vec3(0.3,0.3,0.3),
    //              const Vec3& _specular_color = Vec3(0.1,0.1,0.1),
    //              const Vec3& _emissive_color = Vec3(0.0,0.0,0.0),
    //              double _shininess=0.1, double _transparency=0.0,
    //              bool _reverse_normal=false){
    //         //ambient_color =
    //     }

    //    void setPara(std::string name, std::any value){
    //        //params[name] = value;
    //    }
    //    auto getPara(std::string name)const ->std::any
    //    {
    //        //return params.at(name);
    //    }

    // private:

    //    Vec3 ambientColor;
    //    Vec3 diffuseColor;
    //    Vec3 specularColor;
    //    Vec3 emissiveColor;

    //    double shininess;
    //    double transparency;

    //    bool reverseNormals;
    //};

} // namespace solar

#endif // MATERIAL_H
