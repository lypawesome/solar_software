#ifndef CAMERA_H
#define CAMERA_H

#include "utils/Para.h"
#include "utils/Rotation.h"
#include "utils/Utils.h"
#include "utils/Vec3.h"

#include <boost/describe.hpp>

namespace solar
{
    class Camera : public Para
    {
        public:
            // Camera(){};
            Camera(const Vec3& position = Vec3(-2, -10, 2),
                   const Vec3& rotation_axis = Vec3(0, 1, 0), double rotation_angle = 0,
                   bool perspective = false)
                : position_(position), rotation_(Rotation(rotation_axis, rotation_angle)),
                  perspective_(perspective)
            {
            }

            void setPara(const std::string& property_type, const QVariant& value) override;
            [[nodiscard]] auto getPara(const std::string& property_type) -> QVariant override;
            void testPrint() const override;
#include <utils/class_name.inc>

        private:
            // 不进行计算的话，这几个参数没必要写
            //        Vec3 look_at_; // 相机看向的目标位置
            //        Vec3 up_;      // 相机向上的轴向
            //        Vec3 u_, v_, w_; // 相机上的标架，以position为坐标原点

            Vec3 position_;
            Rotation rotation_;
            bool perspective_;
            BOOST_DESCRIBE_CLASS(Camera, (Para), (), (), (position_, rotation_, perspective_))
    };

} // namespace solar

#endif
