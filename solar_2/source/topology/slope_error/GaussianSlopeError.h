#include "topology/slope_error/SlopeError.h"

namespace solar
{

class GaussianSlopeError : public SlopeError
{
public:
    GaussianSlopeError();

private:
    double sigma;   //高斯分布的标准差
};

} 