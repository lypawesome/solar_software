
#ifndef RAY_H
#define RAY_H

#include "Vec3.h"

namespace solar{

/*
    光线，光线上任一点表示为：origin + t * direction
*/
class Ray
{
public:
    Ray(){};
    Ray(const Vec3& _origin, const Vec3& _direction)
        :orig(_origin), dir(_direction) {};

    Vec3 origin() const {return orig;}
    Vec3 direction() const {return dir;}
    void setOrigin(const Vec3& _origin) {orig = _origin;}
    void setDirection(const Vec3& _direction) {dir = _direction;}

    Vec3 at(double t) const{ return orig + t * dir; }


private:
    Vec3 orig;        //光线的起点
    Vec3 dir;     //光线的方向
};

}   //namespace solar

#endif // RAY_H
