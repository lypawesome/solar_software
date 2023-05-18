#include "scene/Node.h"
#include <utils/ParaUtils.h>

using namespace solar;

void solar::Node::setPara(const std::string& property_type, const QVariant& value)
{
    ::solar::setPara(property_type, value, this);
}

auto solar::Node::getPara(const std::string& property_type) -> QVariant
{
    return ::solar::getPara(property_type, this);
}

void solar::Node::testPrint() const
{
    qDebug() << ::solar::format("Node::translation=({},{},{}),scale=({},{},{})", translation_.x(),
                            translation_.y(), translation_.z(), scale_.x(), scale_.y(), scale_.z());
    rotation_.testPrint();
}

// namespace solar
// {

//    /*
//     * =====================================Node======================================
//     *      kTranslation,
//     *      kAxis,
//     *      kAngle
//            kScale,
//    */
//    void Node::setPara(const int property_type, const QVariant& value)
//    {
//        switch(property_type)
//        {
//        case kTranslation:
//        {
//            translation_ = value.value<Vec3>();
//            break;
//        }
//        case kAxis:
//        case kAngle:
//        {
//            rotation_.setPara(property_type,value);
//            break;
//        }
//        case kScale:
//        {
//            scale_ = value.value<Vec3>();
//            break;
//        }
//        default:
//        {
//            throw "ERROR::Node::setPara()::no such property_type"
//                + std::to_string(property_type);
//            break;
//        }
//        }
//    }
//    auto Node::getPara(const int property_type) const -> QVariant
//    {
//        QVariant ret;
//        switch(property_type)
//        {
//        case kTranslation:
//        {
//            ret = QVariant::fromValue(ret);
//            break;
//        }
//        case kAxis:
//        case kAngle:
//        {
//            ret = rotation_.getPara(property_type);
//            break;
//        }
//        case kScale:
//        {
//            ret = QVariant::fromValue(scale_);
//            break;
//        }
//        default:
//        {
//            throw "ERROR::Node::getPara()::no such property_type"
//                + std::to_string(property_type);
//            break;
//        }
//        }
//        return ret;
//    }
//    void Node::testPrint() const
//    {
//        qDebug() << std::format("Node::translation=({},{},{}),scale=({},{},{})",
//                                translation_.x(),translation_.y(),translation_.z(),
//                                scale_.x(), scale_.y(), scale_.z());
//        rotation_.testPrint();
//    }

// }