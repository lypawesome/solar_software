#include "scene/Sun.h"

namespace solar
{
    /*
    ==========================================Sun===============================================
    kSunShape,
    kCSR,
    kSigma,
    kThetaMax,
    kAzimuth,
    kElevation,
    kIrradiance,
    kTrackable,
    */

    void Sun::setPara(const int property_type, const QVariant& value)
    {
        SunShapeType current_sunshape_type = sunshape_->getType();
        switch(property_type)
        {
        case kSunShape:         //重新分配sunshape
        {
            int next_sunshape_type = value.toInt();
            if(current_sunshape_type == next_sunshape_type) break;

            switch (next_sunshape_type)
            {
            case kSunShapeBuie:     sunshape_ = std::make_shared<BuieSunShape>();        break;
            case kSunShapeGaussian: sunshape_ = std::make_shared<GaussianSunShape>();    break;
            case kSunShapePillbox:  sunshape_ = std::make_shared<PillboxSunShape>();     break;
            default:
                throw "ERROR::NO SUCH SUNSHAPE TYPE IN Sun::setPara() : "
                    +std::to_string(next_sunshape_type) ;
                break;
            }
        }
        case kCSR:
        case kSigma:
        case kThetaMax:
        {
            if(    (property_type == kCSR && current_sunshape_type == kSunShapeBuie)
                || (property_type == kThetaMax && current_sunshape_type == kSunShapePillbox)
                || (property_type == kSigma && current_sunshape_type == kSunShapeGaussian) )
            {
                sunshape_->setPara(value.toDouble());
            }
            else {
                throw "ERROR::Sun::setPara()::property_type not match current sunshape_type: property_type="
                    +std::to_string(property_type)
                    +" sunshape_type=" + std::to_string(current_sunshape_type);
            }
            break;
        }
        case kAzimuth:
        case kElevation:
        case kIrradiance:
        case kTrackable:
        {
            sun_position_->setPara(property_type,value);
            break;
        }
        default:
        {
            throw "ERROR::Sun::setPara()::NO SUCH PARA_PROPERTY: "+std::to_string(property_type);
            break;
        }
        }

    }

    auto Sun::getPara(const int property_type) const -> QVariant
    {
        QVariant ret;

        SunShapeType current_sunshape_type = sunshape_->getType();
        switch(property_type)
        {
        case kSunShape:         //这里返回sunshape的类型
        {
            ret = current_sunshape_type;
            break;
        }
        case kCSR:
        case kSigma:
        case kThetaMax:
        {
            //这里有问题，不知为啥会运行到throw
            qDebug()<<property_type<<"  "<<current_sunshape_type;
            if(    (property_type == kCSR && current_sunshape_type == kSunShapeBuie)
                || (property_type == kThetaMax && current_sunshape_type == kSunShapePillbox)
                || (property_type == kSigma && current_sunshape_type == kSunShapeGaussian) )
            {
                qDebug()<<"....";
                ret = sunshape_->getPara();
            }
            else {

                throw "ERROR::Sun::getPara()::property_type not match current sunshape_type: property_type="
                    + std::to_string(property_type)
                    +" sunshape_type="+std::to_string(current_sunshape_type);
            }
            break;
        }
        case kAzimuth:
        case kElevation:
        case kIrradiance:
        case kTrackable:
        {
            ret = sun_position_->getPara(property_type);
            break;
        }
        default:
        {
            throw "ERROR::Sun::getPara()::NO SUCH PARA_PROPERTY: "+std::to_string(property_type);
            break;
        }
        }

        return ret;
    }

    void Sun::testPrint() const
    {
        qDebug() << "Sun::";
        sunshape_->testPrint();
        sun_position_->testPrint();
    }
}