
#ifndef VEC2_H
#define VEC2_H

#include <QMetaType>
#include "utils/Utils.h"

namespace solar
{

class Vec2
{
public:
    Vec2(){};
    Vec2(double x,double y):e{x,y} {};

    double x(){return e[0];}
    double y(){return e[1];}
    void setX(double x){e[0]=x;}
    void setY(double y){e[1]=y;}

    double& operator[] (int index){return e[index];}

    auto vec2ToString() -> std::string;
    

private:
    double e[2];
};

}
Q_DECLARE_METATYPE(solar::Vec2)

#endif // VEC2_H
