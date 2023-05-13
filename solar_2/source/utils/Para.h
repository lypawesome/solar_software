
#ifndef PARA_H
#define PARA_H


/*
所有需要设置参数的类，在这里定义，包括右上方world和topo的参数
一个虚基类：Para
其他为派生类：Location、Sun、Air、Camera、Terrain、Cloud、Node、Shape、Tracker、Array

para中的每个类的params中，存的都是在UI中可以更改的属性

注意，这个类文件里，采用C++的数据类型
#include "SunShape.h"
#include "SunPosition.h"
#include "Attenuation.h"
#include"utils/Vec3.h"
#include "Rotation.h"
#include "Grid.h"
#include "Geometry.h"
#include "Profile.h"
#include "Material.h"
#include "topology/tracker/Armature.h"
#include "Target.h"
！！！！除了要与UI交互的函数用QVariant，其他的都用std::any
*/

#include <QList>
#include <QString>
#include <QDebug>
#include <QVariant>

#include <memory>
#include <unordered_map>
#include <utility>
#include <variant>
#include <any>
#include <vector>



namespace solar{




    class Para
    {
    public:
        virtual void setPara(
            const int property_type,
            const QVariant&
                value) = 0; // 纯虚函数,用来设置一个参数的值[不要加const，因为要对值进行修改]
        [[nodiscard]] virtual auto getPara(const int property_type) const
            -> QVariant = 0;
        virtual void testPrint() const = 0; // 纯虚函数，输出参数的内容进行测试

    protected:
        Para() = default;
    };

   
} //namespace std

#endif // PARA_H
