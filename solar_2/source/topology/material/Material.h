
#ifndef MATERIAL_H
#define MATERIAL_H

/*
    一个基类，然后派生出几种类型：


派生类中，除了absorb之外均需要设置slopeerror

slopeerror不需要写专门的类，这里只设置了一个枚举类----与TonatiuhPP中类似
*/

#include "utils/Vec3.h"
// #include "SlopeError.h"

#include <any>

#include <boost/describe.hpp>

namespace solar
{

    enum MaterialType
    {
        kMaterialAbsorb,
        kMaterialReflect,
        kMaterialRefract
    };
    enum SlopeErrorType
    {
        kGaussianSlopeError,
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
