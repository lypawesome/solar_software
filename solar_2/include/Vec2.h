
#ifndef VEC2_H
#define VEC2_H


namespace solar
{

class Vec2
{
public:
    Vec2();
    Vec2(double x,double y):e{x,y} {};

    double X(){return e[0];}
    double Y(){return e[1];}
    void setX(double x){e[0]=x;}
    void setY(double y){e[1]=y;}

    double& operator[] (int index){return e[index];}

private:
    double e[2];
};

}

#endif // VEC2_H
