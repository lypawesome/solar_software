
#include "world/sun/sun_position/SunPosition.h"
#include <utils/ParaUtils.h>

using namespace solar;

void solar::SunPosition::setPara(const std::string& property_type, const QVariant& value)
{
    ::solar::setPara(property_type, value, this);
}

auto solar::SunPosition::getPara(const std::string& property_type) -> QVariant
{
    return ::solar::getPara(property_type, this);
}

void solar::SunPosition::testPrint() const
{
   qDebug() << ::solar::format("\t SunPosition:: azimuth={}, elevation={}, irradiance={}, trackable={}",
                               azimuth_, elevation_, irradiance_, trackable_);
}

// namespace solar
// {
// /*
//  *     kAzimuth,
//     kElevation,
//     kIrradiance,
//     kTrackable,
// */

// void SunPosition::testPrint() const
// {
// //    qDebug() << std::format("\t SunPosition:: azimuth={}, elevation={}, irradiance={}, trackable={}",
// //                                azimuth_, elevation_, irradiance_, trackable_);
// }


// } // namespace solar

