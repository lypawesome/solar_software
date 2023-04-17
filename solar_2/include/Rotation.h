
#ifndef ROTATION_H
#define ROTATION_H

/*
旋转：包括旋转轴、旋转角度
*/

#include "Vec3.h"
#include <unordered_map>
#include <any>

namespace solar{
    class Rotation
    {
        public:
            Rotation() : axis(Vec3(1,0,0)), angle(0.0) {};
            Rotation(const Vec3& _axis, double _angle) : axis(_axis), angle(_angle){};

            void setAxis(Vec3 _axis) { axis = _axis; }
            auto getAxis() const -> std::any { return axis; }
            void setAngle(double _angle) { angle = _angle; }
            auto getAngle() const ->std::any {return angle; }

            void setPara(std::string name, std::any value){
                if(name == "axis")
                    setAxis( std::any_cast<Vec3>(value) );
                if(name == "angle")
                    setAngle( std::any_cast<double>(value) );
            }
            auto getPara(std::string name)const -> std::any
            {
                if(name == "axis")
                    return getAxis();
                if(name == "angle")
                    return getAngle();
                return -1;
            }

        private:
            Vec3 axis;          //旋转轴
            double angle;       //旋转角度
    };
}



#endif // ROTATION_H
