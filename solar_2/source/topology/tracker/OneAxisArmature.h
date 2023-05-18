
#include "topology/tracker/Armature.h"

#include <QVariant>

#include "utils/Utils.h"
#include "utils/Vec2.h"
#include "utils/Vec3.h"

#include <boost/describe.hpp>

namespace solar
{

    class OneAxisArmature : public Armature
    {
        public:
            OneAxisArmature();

            void setPara(const std::string& property_type, const QVariant& value) override;
            auto getPara(const std::string& property_type) -> QVariant override;
            [[nodiscard]] auto getType() const -> ArmatureType override { return type_; }
#include <utils/class_name.inc>

        private:
            Vec3 primary_shift_;
            Vec3 primary_axis_;
            Vec2 primary_angles_; // 角度为啥是两个分量？？？
            Vec3 facet_shift_;
            Vec3 facet_normal_;
            Vec2 angle_default_;

            ArmatureType type_;
            BOOST_DESCRIBE_CLASS(solar::OneAxisArmature, (solar::Armature), (), (),
                                 (primary_shift_, primary_axis_, primary_angles_, facet_shift_,
                                  facet_normal_, angle_default_))
    };

} // namespace solar