#include "scene/Location.h"
#include <utils/ParaUtils.h>
#include <utils/Format.h>

#include <QDebug>

using namespace solar;

void solar::Location::setPara(const std::string& property_type, const QVariant& value)
{
    ::solar::setPara(property_type, value, this);
}

auto solar::Location::getPara(const std::string& property_type) -> QVariant
{
    return ::solar::getPara(property_type, this);
}

void solar::Location::testPrint() const
{
    qDebug() << ::solar::format("Location: site_name={}, "
                       "longitude={},  latitude={}",
                       site_name_, longitude_, latitude_);
}
