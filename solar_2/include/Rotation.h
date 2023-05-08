
#ifndef ROTATION_H
#define ROTATION_H

/*
旋转：包括旋转轴、旋转角度
*/

#include "Utils.h"
#include "Vec3.h"
#include <unordered_map>
#include <any>
#include <QVariant>
#include <QDebug>

namespace solar{
    class Rotation
    {
        public:
            Rotation(const Vec3& axis=Vec3(1,0,0), double angle=0) : axis_(axis), angle_(angle){};


            void setPara(const int property_type, const QVariant& value) ;
            auto getPara(const int property_type) const -> QVariant ;
            void testPrint() const ;

        private:
            Vec3 axis_;          //旋转轴
            double angle_;       //旋转角度
    };
}



#endif // ROTATION_H
