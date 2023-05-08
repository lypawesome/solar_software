
#ifndef TARGET_H
#define TARGET_H

#include<QVariant>
#include <string>
#include "Vec3.h"
#include "Vec2.h"
#include "Utils.h"

namespace solar
{

class Target
{
public:
    Target();
    void setPara(const int property_type, const QVariant& value);
    auto getPara(const int property_type) const -> QVariant ;

private:
    std::string aiming_type_;   //类型
    Vec3 aiming_point_;         //目标点
    Vec2 angles_;               //角度
};

}   // namespace solar

#endif // TARGET_H
