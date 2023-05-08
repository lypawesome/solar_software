
#ifndef SLOPEERROR_H
#define SLOPEERROR_H

#include "Vec3.h"

namespace solar{

class SlopeError
{
public:
    SlopeError();

};


class GaussianSlopeError : public SlopeError
{
public:
    GaussianSlopeError();

private:
    double sigma;   //高斯分布的标准差
};


class PillboxSlopeError :public SlopeError
{
public:
    PillboxSlopeError();

};


}   // namespace solar

#endif // SLOPEERROR_H
