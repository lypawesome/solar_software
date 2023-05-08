
#include "Profile.h"

namespace solar
{

/*########################Rectangular###############################
 * kRectU, kRectV,
*/
void Rectangular::setPara(const int property_type, const QVariant& value)
{
    switch (property_type)
    {
    case kRectU:    rect_u_ = value.value<Vec2>();  break;
    case kRectV:    rect_v_ = value.value<Vec2>();  break;
    default:
        throw "ERROR::Rectangular::setPara()::no such property_type"
            + std::to_string(property_type);
        break;
    }
}
auto Rectangular::getPara(const int property_type) const -> QVariant
{
    QVariant ret ;
    switch (property_type)
    {
    case kRectU:    ret = QVariant::fromValue(rect_u_);  break;
    case kRectV:    ret = QVariant::fromValue(rect_v_);  break;
    default:
        throw "ERROR::Rectangular::getPara()::no such property_type"
            + std::to_string(property_type);
        break;
    }
    return ret;
}
void Rectangular::testPrint() const
{

}




}   // namespace solar

