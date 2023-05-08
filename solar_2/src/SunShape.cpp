#include "SunShape.h"

#include <QDebug>

#include <format>

namespace solar
{
    void GaussianSunShape::setPara(double para) { sigma_ = para; }
    auto GaussianSunShape::getPara() const -> double { return sigma_; }
    auto GaussianSunShape::getType() const -> SunShapeType{return type_;}
    void GaussianSunShape::testPrint() const
    {
        qDebug() << std::format("\t Gaussion SunShape::sigma={}", sigma_);
    }

    void PillboxSunShape::setPara(double para) { theta_max_ = para; }
    auto PillboxSunShape::getPara() const -> double { return theta_max_; }
    auto PillboxSunShape::getType() const -> SunShapeType{return type_;}
    void PillboxSunShape::testPrint() const
    {
        qDebug() << std::format("\t Pillbox SunShape::theta_Max={}", theta_max_);
    }

    void BuieSunShape::setPara(double para) { csr_ = para; }
    auto BuieSunShape::getPara() const -> double { return csr_; }
    auto BuieSunShape::getType() const -> SunShapeType{return type_;}
    void BuieSunShape::testPrint() const
    {
        qDebug() << std::format("\t Buie SunShape::csr={}", csr_);
    }
} // namespace solar

