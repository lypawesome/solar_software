#include "scene/Terrain.h"
#include <utils/Grid.h>
#include <utils/ParaUtils.h>

using namespace solar;

solar::Terrain::Terrain() { grid_ = std::make_shared<Grid>(); }

void solar::Terrain::setPara(const std::string& property_type, const QVariant& value)
{
    ::solar::setPara(property_type, value, this);
}

auto solar::Terrain::getPara(const std::string& property_type) -> QVariant
{
    return ::solar::getPara(property_type, this);
}

void solar::Terrain::testPrint() const
{
    qDebug() << "Terrain::";
    grid_->testPrint();
}

// namespace solar
// {

//    /*
//     * ===========================================Terrain==============================================
//     *      kGrid,
//            kFill,
//            kSteps,
//            kDivision,
//            kMin,
//            kMax,
//            kFile,
//    */
//    void Terrain::setPara(const int property_type, const QVariant& value)
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
//            throw "ERROR::Terrain::setPara()::no such property_type: "
//                + std::to_string(property_type);
//            break;
//        }
//        }

//    }
//    auto Terrain::getPara(const int property_type) const -> QVariant
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
//            throw "ERROR::Terrain::getPara()::no such property_type: "
//                + std::to_string(property_type);
//            break;
//        }
//        }

//        return ret;
//    }
//    void Terrain::testPrint() const
//    {
//        qDebug() <<"Terrain::";
//        grid_->testPrint();
//    }

// }