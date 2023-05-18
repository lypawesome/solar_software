#include "scene/Cloud.h"
#include <utils/Grid.h>
#include <utils/ParaUtils.h>

using namespace solar;

solar::Cloud::Cloud() { grid_ = std::make_shared<Grid>(); }

void solar::Cloud::setPara(const std::string& property_type, const QVariant& value)
{
    ::solar::setPara(property_type, value, this);
}

auto solar::Cloud::getPara(const std::string& property_type) -> QVariant
{
    return ::solar::getPara(property_type, this);
}

void solar::Cloud::testPrint() const
{
    qDebug() << "Cloud::";
    grid_->testPrint();
}

// namespace solar
// {

//    /*
//     * ==============================================Cloud==================================================
//     *      kGrid,
//            kFill,
//            kSteps,
//            kDivision,
//            kMin,
//            kMax,
//            kFile,
//    */
//    void Cloud::setPara(const int property_type, const QVariant& value)
//    {
//        switch (property_type)
//        {
//        case kGrid:
//        case kFill:
//        case kSteps:
//        case kDivision:
//        case kMin:
//        case kMax:
//        case kFile:
//        {
//            grid_->setPara(property_type,value);
//            break;
//        }
//        default:
//        {
//            throw "ERROR::Cloud::setPara()::no such property_type: "
//                + std::to_string(property_type);
//            break;
//        }
//        }
//    }
//    auto Cloud::getPara(const int property_type) const -> QVariant
//    {
//        QVariant ret;
//        switch (property_type)
//        {
//        case kGrid:
//        case kFill:
//        case kSteps:
//        case kDivision:
//        case kMin:
//        case kMax:
//        case kFile:
//        {
//            ret = grid_->getPara(property_type);
//            break;
//        }
//        default:
//        {
//            throw "ERROR::Cloud::getPara()::no such property_type: "
//                + std::to_string(property_type);
//            break;
//        }
//        }

//        return ret;
//    }
//    void Cloud::testPrint() const
//    {
//        qDebug() <<"Cloud::";
//        grid_->testPrint();
//    }

// }