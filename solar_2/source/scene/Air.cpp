#include "scene/Air.h"
#include <utils/ParaUtils.h>
#include <world/air/Attenuation.h>
#include <world/air/VacuumAttenuation.h>

using namespace solar;

solar::Air::Air() { attenuation_ = std::make_shared<VacuumAttenuation>(); }

void solar::Air::setPara(const std::string& property_type, const QVariant& value)
{
    ::solar::setPara(property_type, value, this);
}

auto solar::Air::getPara(const std::string& property_type) -> QVariant
{
    return ::solar::getPara(property_type, this);
}

void solar::Air::testPrint() const
{
    qDebug() << "Air::";
    attenuation_->testPrint();
}

// namespace solar
// {

// //    /*
// //    ============================================Air============================================
// //    kAttenuation,
// //    kBeta
// //    */

// //    void Air::setPara(const int property_type, const QVariant& value)
// //    {
// //        AttenuationType current_attenuation_type = attenuation_->getType();
// //        switch(property_type)
// //        {
// //        case kAttenuation:          //更改Attenuation的类型
// //        {
// //            int next_attenuation_type = value.toInt();
// //            if(current_attenuation_type == next_attenuation_type) break;

// //            switch (next_attenuation_type)
// //            {
// //            case kAttenuationVacuum: attenuation_ = std::make_shared<VacuumAttenuation>();
// break;
// //            case kAttenuationExponential: attenuation_ =
// std::make_shared<ExponentialAttenuation>(); break;
// //            case kAttenuationCustom: attenuation_ = std::make_shared<CustomAttenuation>();
// break;
// //            default: throw "ERROR::Air::setPara()::no such attenuation type:
// "+std::to_string(next_attenuation_type);  break;
// //            }
// //            break;
// //        }
// //        case kBeta:
// //        {
// //            if(current_attenuation_type == kAttenuationExponential)
// //            {
// //                attenuation_->setPara(value.toDouble());
// //            }
// //            else{
// //                throw "ERROR::Air::setPara()::property_type not match attenuation_type:
// property_type="
// //                    + std::to_string(property_type)
// //                    +" attenuation_type="+std::to_string(current_attenuation_type);
// //            }
// //            break;
// //        }
// //        default:
// //        {
// //            throw "ERROR::Air::setPara()::NO SUCH PARA_PROPERTY:
// "+std::to_string(property_type);
// //            break;
// //        }
// //        }
// //    }
// //    auto Air::getPara(const int property_type) const -> QVariant
// //    {
// //        QVariant ret;
// //        AttenuationType current_attenuation_type = attenuation_->getType();
// //        switch(property_type)
// //        {
// //        case kAttenuation:
// //        {
// //            ret = current_attenuation_type;
// //            break;
// //        }
// //        case kBeta:
// //        {
// //            if(current_attenuation_type == kAttenuationExponential)
// //            {
// //                ret = attenuation_->getPara();
// //            }
// //            else{

// //                throw "ERROR::Air::getPara()::property_type not match attenuation_type:
// property_type="
// //                    + std::to_string(property_type)
// //                        +" attenuation_type="+std::to_string(current_attenuation_type);
// //            }
// //            break;
// //        }
// //        default:
// //        {
// //            throw "ERROR::Air::getPara()::NO SUCH PARA_PROPERTY:
// "+std::to_string(property_type);
// //            break;
// //        }
// //        }
// //        return ret;
// //    }

// //    void Air::testPrint() const
// //    {
// //        qDebug() << "Air::";
// //        attenuation_->testPrint();
// //    }
// }