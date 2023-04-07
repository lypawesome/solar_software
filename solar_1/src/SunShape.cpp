#include "SunShape.h"

#include <QDebug>

#include <format>

namespace solar
{
    void GaussionSunShape::setPara(double para) { sigma = para; }
    auto GaussionSunShape::getPara() const -> double { return sigma; }
    void GaussionSunShape::testPrint() const
    {
        qDebug() << std::format("Gaussion SunShape::sigma={}", sigma);
    }

    void PillboxSunShape::setPara(double para) { theta_max = para; }
    auto PillboxSunShape::getPara() const -> double { return theta_max; }
    void PillboxSunShape::testPrint() const
    {
        qDebug() << std::format("Pillbox SunShape::theta_Max={}", theta_max);
    }

    void BuieSunShape::setPara(double para) { csr = para; }
    auto BuieSunShape::getPara() const -> double { return csr; }
    void BuieSunShape::testPrint() const
    {
        qDebug() << std::format("Buie SunShape::csr={}", csr);
    }
} // namespace solar
