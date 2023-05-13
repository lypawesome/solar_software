#include "world/sun/sunshape/BuieSunShape.h"

namespace solar
{
    void BuieSunShape::setPara(double para) { csr_ = para; }
    auto BuieSunShape::getPara() const -> double { return csr_; }
    auto BuieSunShape::getType() const -> SunShapeType{return type_;}
    void BuieSunShape::testPrint() const
    {
        //qDebug() << std::format("\t Buie SunShape::csr={}", csr_);
    }
}