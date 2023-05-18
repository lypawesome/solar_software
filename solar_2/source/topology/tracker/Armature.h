
#ifndef ARMATURE_H
#define ARMATURE_H

#include <QVariant>

#include "utils/Utils.h"
#include "utils/Vec2.h"
#include "utils/Vec3.h"


namespace solar
{

    enum ArmatureType
    {
        kOneAxis,
        kTwoAxis,
        kTwoAxisWithDrives
    };

    class Armature
    {
        public:
            Armature();
            virtual void setPara(const std::string& property_type, const QVariant& value) = 0;
            virtual auto getPara(const std::string& property_type) -> QVariant = 0;
            [[nodiscard]] virtual auto getType() const -> ArmatureType = 0;
    };

} // namespace solar
#endif // ARMATURE_H
