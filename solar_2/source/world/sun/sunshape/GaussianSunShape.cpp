#include "world/sun/sunshape/GaussianSunShape.h"

namespace solar
{
    void GaussianSunShape::setPara(double para) { sigma_ = para; }
    auto GaussianSunShape::getPara() const -> double { return sigma_; }
    auto GaussianSunShape::getType() const -> SunShapeType{return type_;}
    void GaussianSunShape::testPrint() const
    {
        //qDebug() << std::format("\t Gaussion SunShape::sigma={}", sigma_);
    }
}