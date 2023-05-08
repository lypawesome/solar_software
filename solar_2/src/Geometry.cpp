
#include "Geometry.h"

namespace solar
{
/*
 * ==========================Parabolic================================
 * kA, kB
*/
void Parabolic::setPara(const int property_type, const QVariant& value)
{
    switch(property_type)
    {
    case kA:
    {
        a_ = value.toDouble();
        break;
    }
    case kB:
    {
        b_ = value.toDouble();
        break;
    }
    default:
    {
        throw "ERROR::Parabolic::setPara()::no such property_type: "
            + std::to_string(property_type);
        break;
    }
    }
}
auto Parabolic::getPara(const int property_type) const -> QVariant
{
    QVariant ret;
    switch(property_type)
    {
    case kA:
    {
        ret = a_;
        break;
    }
    case kB:
    {
        ret = b_;
        break;
    }
    default:
    {
        throw "ERROR::Parabolic::getPara()::no such property_type: "
            + std::to_string(property_type);
        break;
    }
    }
    return ret;
}

/*
 * ===========================Hyperbolic==========================
*/
void Hyperbolic::setPara(const int property_type, const QVariant& value)
{
    switch(property_type)
    {
    case kA:
    {
        a_ = value.toDouble();
        break;
    }
    case kB:
    {
        b_ = value.toDouble();
        break;
    }
    case kC:
    {
        c_ = value.toDouble();
        break;
    }
    default:
    {
        throw "ERROR::Hyperbolic::setPara()::no such property_type: "
            + std::to_string(property_type);
        break;
    }
    }
}
auto Hyperbolic::getPara(const int property_type) const -> QVariant
{
    QVariant ret;
    switch(property_type)
    {
    case kA:
    {
        ret = a_;
        break;
    }
    case kB:
    {
        ret = b_;
        break;
    }
    case kC:
    {
        ret = c_;
        break;
    }
    default:
    {
        throw "ERROR::Hyperbolic::getPara()::no such property_type: "
            + std::to_string(property_type);
        break;
    }
    }
    return ret;
}

/*
 * ===========================Elliptic==========================
*/
void Elliptic::setPara(const int property_type, const QVariant& value)
{
    switch(property_type)
    {
    case kA:
    {
        a_ = value.toDouble();
        break;
    }
    case kB:
    {
        b_ = value.toDouble();
        break;
    }
    case kC:
    {
        c_ = value.toDouble();
        break;
    }
    default:
    {
        throw "ERROR::Elliptic::setPara()::no such property_type: "
            + std::to_string(property_type);
        break;
    }
    }
}
auto Elliptic::getPara(const int property_type) const -> QVariant
{
    QVariant ret;
    switch(property_type)
    {
    case kA:
    {
        ret = a_;
        break;
    }
    case kB:
    {
        ret = b_;
        break;
    }
    case kC:
    {
        ret = c_;
        break;
    }
    default:
    {
        throw "ERROR::Elliptic::getPara()::no such property_type: "
            + std::to_string(property_type);
        break;
    }
    }
    return ret;
}


/*
 * ===========================BSpline==========================
*/
void BSpline::setPara(const int property_type, const QVariant& value)
{
    switch(property_type)
    {
    case kFile:
    {
        file_ = value.toString().toStdString();
        break;
    }
    default:
    {
        throw "ERROR::BSpline::setPara()::no such property_type: "
            + std::to_string(property_type);
        break;
    }
    }
}
auto BSpline::getPara(const int property_type) const -> QVariant
{
    QVariant ret;
    switch(property_type)
    {
    case kFile:
    {
        ret = QString::fromStdString(file_);
        break;
    }
    default:
    {
        throw "ERROR::BSpline::getPara()::no such property_type: "
            + std::to_string(property_type);
        break;
    }
    }
    return ret;
}

/*
 * ===========================Map==========================
*/
void Map::setPara(const int property_type, const QVariant& value)
{
    switch(property_type)
    {
    case kFile:
    {
        file_ = value.toString().toStdString();
        break;
    }
    default:
    {
        throw "ERROR::Custom::setPara()::no such property_type: "
            + std::to_string(property_type);
        break;
    }
    }
}
auto Map::getPara(const int property_type) const -> QVariant
{
    QVariant ret;
    switch(property_type)
    {
    case kFile:
    {
        ret = QString::fromStdString(file_);
        break;
    }
    default:
    {
        throw "ERROR::Custom::getPara()::no such property_type: "
            + std::to_string(property_type);
        break;
    }
    }
    return ret;
}



} // namespace solar
