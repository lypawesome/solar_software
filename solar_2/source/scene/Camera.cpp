#include "scene/Camera.h"

namespace solar
{
    
//    /*
//     * =========================================Camera===========================================
//     *
//     *     kPosition,
//    kAxis,
//    kAngle,
//    kPerspective,
//    */
//    void Camera::setPara(const int property_type, const QVariant& value)
//    {
//        switch(property_type)
//        {
//        case kPosition:
//        {
//            position_ = value.value<Vec3>();
//            break;
//        }
//        case kAxis:
//        case kAngle:
//        {
//            rotation_.setPara(property_type, value);
//            break;
//        }
//        case kPerspective:
//        {
//            perspective_ = value.toBool();
//            break;
//        }
//        default:
//        {
//            throw "ERROR::Camera::setPara()::no such property_type: "+std::to_string(property_type);
//            break;
//        }
//        }
//    }

//    auto Camera::getPara(const int property_type) const -> QVariant
//    {
//        QVariant ret;
//        switch(property_type)
//        {
//        case kPosition:
//        {
//            ret = QVariant::fromValue(position_);
//            break;
//        }
//        case kAxis:
//        case kAngle:
//        {
//            ret = rotation_.getPara(property_type);
//            break;
//        }
//        case kPerspective:
//        {
//            ret = perspective_;
//            break;
//        }
//        default:
//        {
//            throw "ERROR::Camera::setPara()::no such property_type: "+std::to_string(property_type);
//            break;
//        }
//        }
//        return ret;
//    }
//    void Camera::testPrint() const
//    {
//        qDebug() << std::format("Camera::position=({},{},{}),perspective={}",
//                                position_.x(), position_.y(), position_.z(), perspective_);
//        rotation_.testPrint();
//    }

}