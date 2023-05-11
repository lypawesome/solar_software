
#include "Para.h"

//#include <format>
#include <iostream>
#include <stdexcept>

namespace solar
{

    /*
    ==================================Location====================================
    kSiteName,
    kLongitude,
    kLatitude,
    */
    void Location::setPara(const int property_type, const QVariant& value)
    {
        switch(property_type)
        {
        case kSiteName:
        {
            site_name_ = value.toString().toStdString();
            break;
        }
        case kLongitude:
        {
            longitude_ = value.toDouble();
            break;
        }
        case kLatitude:
        {
            latitude_ = value.toDouble();
            break;
        }
        default:
        {
            throw "ERROR::Location::setPara()::NO SUCH PARA_PROPERTY:" + std::to_string(property_type);
        }
        }
    }
    auto Location::getPara(const int property_type) const -> QVariant
    {
        QVariant ret ;
        switch (property_type)
        {
        case kSiteName:
        {
            ret = QString::fromStdString(site_name_);
            break;
        }
        case kLongitude:
        {
            ret = longitude_;
            break;
        }
        case kLatitude:
        {
            ret = latitude_;
            break;
        }
        default:
        {
            throw "ERROR::Location::getPara()::NO SUCH PARA_PROPERTY:" + std::to_string(property_type);
            break;
        }
        }

        return ret;
    }

    void Location::testPrint() const
    {
//        qDebug() << std::format("Location: site_name={}, "
//                            "longitude={},  latitude={}",
//                            site_name_, longitude_, latitude_);
    }

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


//    /*
//    ============================================Air============================================
//    kAttenuation,
//    kBeta
//    */

//    void Air::setPara(const int property_type, const QVariant& value)
//    {
//        AttenuationType current_attenuation_type = attenuation_->getType();
//        switch(property_type)
//        {
//        case kAttenuation:          //更改Attenuation的类型
//        {
//            int next_attenuation_type = value.toInt();
//            if(current_attenuation_type == next_attenuation_type) break;

//            switch (next_attenuation_type)
//            {
//            case kAttenuationVacuum: attenuation_ = std::make_shared<VacuumAttenuation>(); break;
//            case kAttenuationExponential: attenuation_ = std::make_shared<ExponentialAttenuation>(); break;
//            case kAttenuationCustom: attenuation_ = std::make_shared<CustomAttenuation>(); break;
//            default: throw "ERROR::Air::setPara()::no such attenuation type: "+std::to_string(next_attenuation_type);  break;
//            }
//            break;
//        }
//        case kBeta:
//        {
//            if(current_attenuation_type == kAttenuationExponential)
//            {
//                attenuation_->setPara(value.toDouble());
//            }
//            else{
//                throw "ERROR::Air::setPara()::property_type not match attenuation_type: property_type="
//                    + std::to_string(property_type)
//                    +" attenuation_type="+std::to_string(current_attenuation_type);
//            }
//            break;
//        }
//        default:
//        {
//            throw "ERROR::Air::setPara()::NO SUCH PARA_PROPERTY: "+std::to_string(property_type);
//            break;
//        }
//        }
//    }
//    auto Air::getPara(const int property_type) const -> QVariant
//    {
//        QVariant ret;
//        AttenuationType current_attenuation_type = attenuation_->getType();
//        switch(property_type)
//        {
//        case kAttenuation:
//        {
//            ret = current_attenuation_type;
//            break;
//        }
//        case kBeta:
//        {
//            if(current_attenuation_type == kAttenuationExponential)
//            {
//                ret = attenuation_->getPara();
//            }
//            else{

//                throw "ERROR::Air::getPara()::property_type not match attenuation_type: property_type="
//                    + std::to_string(property_type)
//                        +" attenuation_type="+std::to_string(current_attenuation_type);
//            }
//            break;
//        }
//        default:
//        {
//            throw "ERROR::Air::getPara()::NO SUCH PARA_PROPERTY: "+std::to_string(property_type);
//            break;
//        }
//        }
//        return ret;
//    }

//    void Air::testPrint() const
//    {
//        qDebug() << "Air::";
//        attenuation_->testPrint();
//    }

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

//    /*
//     * ======================================Shape=======================================
//     * ！！！！！没有写完，还需要补充
//     *  kGeometry, kA, kB, kC, kFile
//        kProfile, kRectU, kRectV,kCircleRadius, kCirclePhi,kRegularEdgeLength, kRegularEdgeCnt,
//                    kTriA, kTriB, kTriC, kPolyPoints,
//        kMaterial
//    */
//    void Shape::setPara(const int property_type, const QVariant& value)
//    {
//        switch(property_type)
//        {
//        case kGeometry:     //更换Geometry的类别
//        {
//            GeometryType current_geometry_type = geometry_->getType();
//            int next_geometry_type = value.toInt();
//            if(current_geometry_type == next_geometry_type) break;

//            switch(next_geometry_type)
//            {
//            case kGeometryPlanar:       geometry_ = std::make_shared<Planar>();   break;
//            case kGeometryParabolic:    geometry_ = std::make_shared<Parabolic>(); break;
//            case kGeometryHyperbolic:   geometry_ = std::make_shared<Hyperbolic>(); break;
//            case kGeometryElliptic:     geometry_ = std::make_shared<Elliptic>(); break;
//            case kGeometryBSpline:      geometry_ = std::make_shared<BSpline>(); break;
//            case kGeometryMap:       geometry_ = std::make_shared<Map>(); break;
//            default:
//                throw "ERROR::Shape::setPara()::no such geometry type"
//                    + std::to_string(next_geometry_type);
//                break;
//            }

//            break;
//        }
//        case kProfile:      //更换Profile的类别：kProfileRectangular,kProfileCircular,kProfileRegular,kProfileTriangle, kProfilePolygon
//        {
//            ProfileType current_profile_type = profile_->getType();
//            int next_profile_type = value.toInt();
//            if(current_profile_type == next_profile_type) break;

//            switch (next_profile_type)
//            {
//            case kProfileRectangular:   profile_ = std::make_shared<Rectangular>(); break;
//            case kProfileCircular:      profile_ = std::make_shared<Circular>(); break;
//            case kProfileRegular:       profile_ = std::make_shared<Regular>(); break;
//            case kProfileTriangle:      profile_ = std::make_shared<Triangle>(); break;
//            case kProfilePolygon:       profile_ = std::make_shared<Polygon>(); break;
//            default:
//                throw "ERROR::Shape::setPara()::no such profile type"
//                    + std::to_string(next_profile_type);
//                break;
//            }

//            break;
//        }
//        case kMaterial:     //！！！！先空着，明天往往师姐
//        {
//            break;
//        }
//        case kA:
//        case kB:
//        case kC:
//        case kFile:
//        {
//            geometry_->setPara(property_type,value);
//            break;
//        }
//        case kRectU:
//        case kRectV:
//        case kCircleRadius:
//        case kCirclePhi:
//        case kRegularEdgeLength:
//        case kRegularEdgeCnt:
//        case kTriA:
//        case kTriB:
//        case kTriC:
//        case kPolyPoints:
//        {
//            profile_->setPara(property_type,value);
//            break;
//        }

//        default:
//        {
//            throw "ERROR::Shape::setPara()::no such property type: "
//                + std::to_string(property_type);
//            break;
//        }
//        }
//    }
//    auto Shape::getPara(const int property_type) const -> QVariant
//    {
//        QVariant ret;
//        switch(property_type)
//        {
//        case kGeometry:
//        {
//            GeometryType current_geometry_type = geometry_->getType();
//            ret = current_geometry_type;
//            break;
//        }
//        case kProfile:
//        {
//            ProfileType current_profile_type = profile_->getType();
//            ret = current_profile_type;
//            break;
//        }
//        case kMaterial:     //！！！！先空着，明天往往师姐
//        {
//            break;
//        }
//        case kA:
//        case kB:
//        case kC:
//        case kFile:
//        {
//            ret = geometry_->getPara(property_type);
//            break;
//        }
//        case kRectU:
//        case kRectV:
//        case kCircleRadius:
//        case kCirclePhi:
//        case kRegularEdgeLength:
//        case kRegularEdgeCnt:
//        case kTriA:
//        case kTriB:
//        case kTriC:
//        case kPolyPoints:
//        {
//            ret = profile_->getPara(property_type);
//            break;
//        }

//        default:
//        {
//            throw "ERROR::Shape::getPara()::no such property type: "
//                + std::to_string(property_type);
//            break;
//        }
//        }
//    }
//    void Shape::testPrint() const
//    {

//    }

//    /*
//     * ======================================Tracker=======================================
//    */
//    void Tracker::setPara(const int property_type, const QVariant& value)
//    {
//        switch(property_type)
//        {
//        case kArmature:         // 更改Armature的类型
//        {
//            ArmatureType current_armature_type = armature_->getType();
//            int next_armature_type = value.toInt();
//            if(current_armature_type == next_armature_type) break;
//            switch (next_armature_type) {
//            case kOneAxis:  armature_ = std::make_shared<OneAxis>();        break;
//            case kTwoAxis:  armature_ = std::make_shared<TwoAxis>();        break;
//            case kTwoAxisWithDrives: armature_ = std::make_shared<TwoAxisWithDrives>();     break;
//            default:
//                throw "ERROR::Tracker::setPara()::no such armature type: "
//                    +std::to_string(next_armature_type);
//                break;
//            }
//            break;
//        }
//        case kPrimaryShift:
//        case kPrimaryAxis:
//        case kPrimaryAngles:
//        case kSecondaryShift:
//        case kSecondaryAxis:
//        case kSecondaryAngles:
//        case kFacetShift:
//        case kFacetNormal:
//        case kAngleDefault:
//        case kDrivePrimaryR:
//        case kDrivePrimaryP:
//        case kDriveSecondaryP:
//        case kDriveSecondaryS:
//        {
//            armature_->setPara(property_type,value);
//            break;
//        }
//        case kAimingType:
//        case kAimingPoint:
//        case kAngle:
//        {
//            target_->setPara(property_type,value);
//            break;
//        }
//        default:
//        {
//            throw "ERROR::Tracker::setPara()::no such property type: "
//                +std::to_string(property_type);
//            break;
//        }
//        }
//    }
//    auto Tracker::getPara(const int property_type) const -> QVariant
//    {
//        QVariant ret;
//        switch(property_type)
//        {
//        case kArmature:         // 更改Armature的类型
//        {
//            ArmatureType current_armature_type = armature_->getType();
//            ret = current_armature_type;
//            break;
//        }
//        case kPrimaryShift:
//        case kPrimaryAxis:
//        case kPrimaryAngles:
//        case kSecondaryShift:
//        case kSecondaryAxis:
//        case kSecondaryAngles:
//        case kFacetShift:
//        case kFacetNormal:
//        case kAngleDefault:
//        case kDrivePrimaryR:
//        case kDrivePrimaryP:
//        case kDriveSecondaryP:
//        case kDriveSecondaryS:
//        {
//            ret = armature_->getPara(property_type);
//            break;
//        }
//        case kAimingType:
//        case kAimingPoint:
//        case kAngle:
//        {
//            ret = target_->getPara(property_type);
//            break;
//        }
//        default:
//        {
//            throw "ERROR::Tracker::setPara()::no such property type: "
//                +std::to_string(property_type);
//            break;
//        }
//        }
//    }
//    void Tracker::testPrint() const
//    {

//    }

//    /*
//     * ======================================Array=======================================
//    */
//    void Array::setPara(const int property_type, const QVariant& value)
//    {

//    }
//    auto Array::getPara(const int property_type) const -> QVariant
//    {

//    }
//    void Array::testPrint() const
//    {

//    }



} // namespace std

