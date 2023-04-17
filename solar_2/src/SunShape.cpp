#include "SunShape.h"

#include <QDebug>

#include <format>

namespace solar
{
    void GaussianSunShape::setPara(double para) { sigma = para; }
    auto GaussianSunShape::getPara() const -> double { return sigma; }
    auto GaussianSunShape::getType() const -> SunShapeType{return type;}
    void GaussianSunShape::testPrint() const
    {
        qDebug() << std::format("Gaussion SunShape::sigma={}", sigma);
    }

    void PillboxSunShape::setPara(double para) { theta_max = para; }
    auto PillboxSunShape::getPara() const -> double { return theta_max; }
    auto PillboxSunShape::getType() const -> SunShapeType{return type;}
    void PillboxSunShape::testPrint() const
    {
        qDebug() << std::format("Pillbox SunShape::theta_Max={}", theta_max);
    }

    void BuieSunShape::setPara(double para) { csr = para; }
    auto BuieSunShape::getPara() const -> double { return csr; }
    auto BuieSunShape::getType() const -> SunShapeType{return type;}
    void BuieSunShape::testPrint() const
    {
        qDebug() << std::format("Buie SunShape::csr={}", csr);
    }
} // namespace solar

