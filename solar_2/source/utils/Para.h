
#ifndef PARA_H
#define PARA_H

/*
所有需要设置参数的类，在这里定义，包括右上方world和topo的参数
一个虚基类：Para
其他为派生类：Location、Sun、Air、Camera、Terrain、Cloud、Node、Shape、Tracker、Array

para中的每个类的params中，存的都是在UI中可以更改的属性

注意，这个类文件里，采用C++的数据类型
#include "Attenuation.h"
#include "Geometry.h"
#include "Grid.h"
#include "Material.h"
#include "Profile.h"
#include "Rotation.h"
#include "SunPosition.h"
#include "SunShape.h"
#include "Target.h"
#include "topology/tracker/Armature.h"
#include"utils/Vec3.h"

！！！！除了要与UI交互的函数用QVariant，其他的都用std::any
*/

#include <QVariant>

#include <string>

namespace solar
{

    class Para
    {
        public:
            virtual ~Para() = default;

            /// \brief 用来设置一个参数的值
            /// \param property_type 参数名称
            /// \param value 参数的值
            virtual void setPara(const std::string& property_type, const QVariant& value) = 0;

            /// \brief 用来获得一个参数的值
            /// \param property_type 参数名称
            [[nodiscard]] virtual auto getPara(const std::string& property_type)
                -> QVariant = 0;
        //     virtual void setPara(
        //     const int property_type,
        //     const QVariant&
        //         value) = 0; // 纯虚函数,用来设置一个参数的值[不要加const，因为要对值进行修改]
        // [[nodiscard]] virtual auto getPara(const int property_type) const
        //     -> QVariant = 0;

            /// \brief 输出参数的内容进行测试
            virtual void testPrint() const = 0;


        protected:
            Para() = default; 
    };

} // namespace solar

#endif // PARA_H
