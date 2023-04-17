
#include "Para.h"

#include <format>
#include <iostream>
#include <stdexcept>

namespace solar
{

    /*
    ==================================Location====================================
    */
    void Location::setPara(const std::string& name, const QVariant& value)
    {
        std::any temp_value;
        if(name=="site_name") temp_value = (value.toString()).toStdString();
        else temp_value = value.toDouble();

        params[name] = temp_value;
    }
    auto Location::getPara(const std::string& name) const -> QVariant
    {
        QVariant ret;
        if(name == "site_name") ret = QString::fromStdString(std::any_cast<std::string>(params.at(name)));
        return ret;
    }

    void Location::testPrint() const
    {
        qDebug() << std::format("WorldPara::Location: site_name={}, "
                            "longitude={},  latitude={}",
                            std::any_cast<std::string>(getPara("site_name")),
                            std::any_cast<double>(getPara("longitude")),
                            std::any_cast<double>(getPara("latitude")));
    }

    /*
    ==========================================Sun===============================================

    */

    void Sun::setPara(const std::string& name, const QVariant& value)
    {
        //if(name == "sunshape" || name == "position")    //尽量不让QVariant指向std智能指针
        //    params[name] = value;
        if(name == "azimuth" || name=="elevation" || name=="irradiance"||name=="trackable")
        {

            std::shared_ptr<SunPosition> position =
                std::any_cast<std::shared_ptr<SunPosition>>(params.at(name));
            std::any temp_value;
            if(name=="trackable") temp_value = value.toBool();
            else temp_value = value.toDouble();
            position->setPara(name, temp_value);
        }
        else if(name=="csr" || name =="sigma" || name == "theta_max")
        {
            std::shared_ptr<SunShape> sunshape =
                std::any_cast<std::shared_ptr<SunShape>>(params.at(name));
            int type = sunshape->getType();
            switch(type)
            {
            case GAUSSIAN:
                if(name != "sigma")
                    throw std::invalid_argument("Invalid name in Func setPara()::not sigma in gaussion sunshape");
                break;
            case BUIE:
                if(name != "csr")
                    throw std::invalid_argument("Invalid name in Func setPara()::not csr in gaussion sunshape");
                break;
            case PILLBOX:
                if(name != "theta_max")
                    throw std::invalid_argument("Invalid name in Func setPara()::not theta_max in gaussion sunshape");
                break;
            }
            sunshape->setPara( value.toDouble() );
        }
    }
    auto Sun::getPara(const std::string& name) const -> QVariant
    {
        //if(name=="sunshape" || name=="position")
        //    return params.at(name);
        if(name == "azimuth" || name=="elevation" || name=="irradiance"||name=="trackable")
        {

            std::shared_ptr<SunPosition> position =
                std::any_cast<std::shared_ptr<SunPosition>>(params.at("position"));
            QVariant ret;
            if(name == "trackable") ret = std::any_cast<bool>(position->getPara(name));
            else ret = std::any_cast<double>(position->getPara(name));
            return ret;
        }
        else if(name=="csr" || name =="sigma" || name == "theta_max")
        {
            std::shared_ptr<SunShape> sunshape =
                std::any_cast<std::shared_ptr<SunShape>>(params.at("sunshape"));
            int type = sunshape->getType();
            switch(type)
            {
            case GAUSSIAN:
                if(name != "sigma")
                    throw std::invalid_argument("Invalid name in Func setPara()::not sigma in gaussion sunshape");
                break;
            case BUIE:
                if(name != "csr")
                    throw std::invalid_argument("Invalid name in Func setPara()::not csr in gaussion sunshape");
                break;
            case PILLBOX:
                if(name != "theta_max")
                    throw std::invalid_argument("Invalid name in Func setPara()::not theta_max in gaussion sunshape");
                break;
            }
            return sunshape->getPara();
        }
        return -1 ;
    }

    void Sun::testPrint() const
    {

        std::shared_ptr<SunShape> sunshape = std::any_cast<std::shared_ptr<SunShape>>(params.at("sunshape"));

        qDebug() << std::format(
            "WorldPara::Sun: azimuth={}, elevation={}, irradiance={},"
            " trackable={}, sun_shape_type={}, sun_shape.para={}",
            std::any_cast<double>(getPara("azimuth")),      std::any_cast<double>(getPara("elevation")),
            std::any_cast<double>(getPara("irradiance")),   std::any_cast<bool>(getPara("trackable")),
            (int)(sunshape->getType()),                     //这里返回的是枚举，需要转换为int型
            std::any_cast<double>(sunshape->getPara())
            );
    }

    /*
    ============================================Air============================================
    */

    void Air::setPara(const std::string& name, const QVariant& value)
    {
        //if(name=="attenuation")     //表示value指向一个Attenuation智能指针
        //    params[name] = value;
        if(name=="beta")       //修改ExponenatialAttenuation下的beta成员
        {
            std::shared_ptr<Attenuation> attenuation
                = std::any_cast<std::shared_ptr<Attenuation>>(params.at("attenuation"));
            int type = attenuation->getType();
            if(type == EXPONENTIAL){
                auto exponential_attenuation =
                    std::dynamic_pointer_cast<ExponentialAttenuation>(attenuation);
                exponential_attenuation->setPara(value.toDouble());
            }
        }
    }
    auto Air::getPara(const std::string& name) const -> QVariant
    {
        //if(name=="attenuation")
        //    return params.at(name);
        if(name == "beta")
        {
            std::shared_ptr<Attenuation> attenuation
                = std::any_cast<std::shared_ptr<Attenuation>>(params.at("attenuation"));
            int type = attenuation->getType();
            if(type == EXPONENTIAL){
                auto exponential_attenuation =
                    std::dynamic_pointer_cast<ExponentialAttenuation>(attenuation);
                return exponential_attenuation->getPara();
            }
        }
        return -1;
    }
    void Air::testPrint() const
    {
        std::shared_ptr<Attenuation> attenuation
            = std::any_cast<std::shared_ptr<Attenuation>>(params.at("attenuation"));
        qDebug() << std::format(
            "WorldPara::Air: air_model_type={}",
            (int)(attenuation->getType())   );
    }


} // namespace std

