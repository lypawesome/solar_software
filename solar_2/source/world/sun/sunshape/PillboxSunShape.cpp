#include "world/sun/sunshape/PillboxSunShape.h"
#include <utils/Format.h>

#include <QDebug>

namespace solar
{
    void PillboxSunShape::setPara(double para) { theta_max_ = para; }
    auto PillboxSunShape::getPara() const -> double { return theta_max_; }
    auto PillboxSunShape::getType() const -> SunShapeType { return type_; }
    void PillboxSunShape::testPrint() const
    {
        qDebug() << ::solar::format("\t Pillbox SunShape::theta_Max={}", theta_max_);
    }
} // namespace solar
