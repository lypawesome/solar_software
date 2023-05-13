#include "scene/Location.h"

namespace solar
{
    /*
    ==================================Location====================================
    kSiteName,
    kLongitude,
    kLatitude,
    */
    void Location::setPara(const int property_type, const QVariant& value)
    {
        switch(property_type)
        {
        case kSiteName:
        {
            site_name_ = value.toString().toStdString();
            break;
        }
        case kLongitude:
        {
            longitude_ = value.toDouble();
            break;
        }
        case kLatitude:
        {
            latitude_ = value.toDouble();
            break;
        }
        default:
        {
            throw "ERROR::Location::setPara()::NO SUCH PARA_PROPERTY:" + std::to_string(property_type);
        }
        }
    }
    auto Location::getPara(const int property_type) const -> QVariant
    {
        QVariant ret ;
        switch (property_type)
        {
        case kSiteName:
        {
            ret = QString::fromStdString(site_name_);
            break;
        }
        case kLongitude:
        {
            ret = longitude_;
            break;
        }
        case kLatitude:
        {
            ret = latitude_;
            break;
        }
        default:
        {
            throw "ERROR::Location::getPara()::NO SUCH PARA_PROPERTY:" + std::to_string(property_type);
            break;
        }
        }

        return ret;
    }

    void Location::testPrint() const
    {
//        qDebug() << std::format("Location: site_name={}, "
//                            "longitude={},  latitude={}",
//                            site_name_, longitude_, latitude_);
    }
}