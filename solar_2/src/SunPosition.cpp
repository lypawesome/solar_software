
#include "SunPosition.h"
//include <format>

namespace solar
{
/*
 *     kAzimuth,
    kElevation,
    kIrradiance,
    kTrackable,
*/
void SunPosition::setPara(const int property_type, const QVariant& value)
{
    switch (property_type) {
    case kAzimuth:
        azimuth_ = value.toDouble();
        break;
    case kElevation:
        elevation_ = value.toDouble();
        break;
    case kIrradiance:
        irradiance_ = value.toDouble();
        break;
    case kTrackable:
        trackable_ = value.toBool();
        break;
    default:
        throw "ERROR::NO SUCH PARA_PROPERTY IN SUNPOSITION:"+std::to_string(property_type);
        break;
    }
}
auto SunPosition::getPara(const int property_type) const -> QVariant
{
    QVariant ret;
    switch (property_type) {
    case kAzimuth:
        ret = azimuth_;
        break;
    case kElevation:
        ret = elevation_;
        break;
    case kIrradiance:
        ret = irradiance_;
        break;
    case kTrackable:
        ret = trackable_;
        break;
    default:
        throw "ERROR::NO SUCH PARA_PROPERTY IN SUNPOSITION:"+std::to_string(property_type);
        break;
    }

    return ret;
}
void SunPosition::testPrint() const
{
//    qDebug() << std::format("\t SunPosition:: azimuth={}, elevation={}, irradiance={}, trackable={}",
//                                azimuth_, elevation_, irradiance_, trackable_);
}


} // namespace solar

