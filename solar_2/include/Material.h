
#ifndef MATERIAL_H
#define MATERIAL_H

/*
    一个基类，然后派生出几种类型：
        1、diffuse
        2、metal----高光反射
        3、不加折射的
        4、加折射的....
*/

#include "Vec3.h"
#include "Ray.h"
#include "Geometry.h"
#include "SlopeError.h"
#include <any>


namespace solar{

class Material{
public:
    //计算得到下一根光线
    virtual bool getNextRay(Ray in_ray,IntersectInfo& intersection) const ;

};


//玻璃层---有折射
class Glass : public Material
{
public:
    Glass();
    bool getNextRay(Ray in_ray,IntersectInfo& intersection) const;

private:
    //吸收率是设定好的，反射率通过Fresnel计算得到，透射率用1-吸收率-反射率得到
    double reflectivity;    //反射率---可以通过Fresnel计算得到
    double transmissivity;  //透射率---进入到玻璃内的概率
    double absorptivity;    //吸收率----反射率+吸收率+透射率=1

    double refractive_index;    //玻璃的折射率
    double thickness;   //玻璃的厚度



};

//银层--相当于metal
class Sliver : public Material
{
public:
    Sliver();
    bool getNextRay(Ray in_ray,IntersectInfo& intersection) const;

private:
    double reflectivity;    //反射率
    double absorptivity;    //吸收率

    SlopeError slope_error;     //法向扰动的类型
    Vec3 color;     //颜色设置
};

class Heliostat{
public:
    Heliostat();
    bool getNextRay(Ray in_ray,IntersectInfo& intersection) const;

private:
    Glass glass;
    Sliver sliver;
};

//class Material
//{
//public:
//    Material(const Vec3& _ambient_color = Vec3(0.3,0.4,0.5),
//             const Vec3& _diffuse_color = Vec3(0.3,0.3,0.3),
//             const Vec3& _specular_color = Vec3(0.1,0.1,0.1),
//             const Vec3& _emissive_color = Vec3(0.0,0.0,0.0),
//             double _shininess=0.1, double _transparency=0.0,
//             bool _reverse_normal=false){
//        //ambient_color =
//    }


//    void setPara(std::string name, std::any value){
//        //params[name] = value;
//    }
//    auto getPara(std::string name)const ->std::any
//    {
//        //return params.at(name);
//    }


//private:

//    Vec3 ambientColor;
//    Vec3 diffuseColor;
//    Vec3 specularColor;
//    Vec3 emissiveColor;

//    double shininess;
//    double transparency;

//    bool reverseNormals;
//};

}

#endif // MATERIAL_H
