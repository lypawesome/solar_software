#include "topology/geometry/Mesh.h"

namespace solar
{
    
/*
 * ===========================Mesh==========================
*/
void Mesh::setPara(const int property_type, const QVariant& value)
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
auto Mesh::getPara(const int property_type) const -> QVariant
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

}