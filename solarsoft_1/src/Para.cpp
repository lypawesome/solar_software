#include "Para.h"
#include "SunShape.h"

#include <QVariant>

#include <format>
#include <iostream>
#include <stdexcept>

namespace solar
{
    /*
    ==================================Location====================================
    */
    void Location::setPara(const QString& name, const QVariant& value)
    {
        switch (this->params.at(name).index())
        {
        case 0:
            this->params[name] = value.toString();
            break;
        case 1:
            this->params[name] = value.toDouble();
        }
    }
    auto Location::getPara(const QString& name) const -> QVariant
    {
        auto index = this->params.at(name).index();
        switch (index)
        {
        case 0:
            return std::get<0>(this->params.at(name));
        case 1:
            return std::get<1>(this->params.at(name));
        }
        qDebug() << std::format("In function {}:\n Invalid param key: {}",
                                __PRETTY_FUNCTION__, name.toStdString());
        throw std::invalid_argument("Invalid Param Key");
    }

    void Location::testPrint() const
    {
        qDebug() << std::format("WorldPara::Location: site_name={}, "
                                "longitude={},  latitude={}",
                                getPara("site_name").toString().toStdString(),
                                getPara("longitude").toDouble(),
                                getPara("latitude").toDouble());
    }

    /*
    ==========================================Sun===============================================

    */
    Sun::Sun(double _azimuth, double _elevation, double _irradiance,
             bool _trackable, SunShapeType _sunshape_type, double _sunshape)
    {
        std::shared_ptr<SunShape> sun_shape_ptr = nullptr;
        switch (_sunshape_type)
        {
        case PILLBOX:
            sun_shape_ptr = std::make_shared<PillboxSunShape>();
            break;
        case BUIE:
            sun_shape_ptr = std::make_shared<BuieSunShape>();
            break;
        case GAUSSION:
            sun_shape_ptr = std::make_shared<GaussionSunShape>();
            break;
        }
        sun_shape_ptr->setPara(_sunshape);
        this->params = {{"azimuth", _azimuth},
                        {"elevation", _elevation},
                        {"irradiance", _irradiance},
                        {"trackable", _trackable},
                        {"sun_shape_type", _sunshape_type},
                        {"sun_shape", sun_shape_ptr}};

        // if (sunshape)
        //     sunshape->setPara(_sunshape);
    }
    Sun::~Sun() = default;
    void Sun::setPara(const QString& name, const QVariant& value)
    {
        // switch (_hash.at(name))
        // {
        // case 0:
        //     azimuth = value.toDouble();
        //     break;
        // case 1:
        //     elevation = value.toDouble();
        //     break;
        // case 2:
        //     irradiance = value.toDouble();
        //     break;
        // case 3:
        //     trackable = value.toBool();
        //     break;
        // case 4: // 重新设置sunshape的类型
        // {
        //     reallocateSunshape(SunShapeType(value.toInt()));
        //     break;
        // }
        // case 5:
        //     sunshape->setPara(value.toDouble());
        //     break;
        // }
        switch (this->params.at(name).index())
        {
        case 0:
        {
            if (name == "sun_shape")
            {
                std::get<3>(this->params["sun_shape"])
                    ->setPara(value.toDouble());
            }
            else
            {
                this->params[name] = value.toDouble();
            }
            break;
        }

        case 1:
            this->params[name] = value.toBool();
            break;
        case 2:
        {
            std::shared_ptr<SunShape> sun_shape_ptr = nullptr;
            switch (SunShapeType(value.toInt()))
            {
            case PILLBOX:
                sun_shape_ptr = std::make_shared<PillboxSunShape>();
                break;
            case BUIE:
                sun_shape_ptr = std::make_shared<BuieSunShape>();
                break;
            case GAUSSION:
                sun_shape_ptr = std::make_shared<GaussionSunShape>();
                break;
            }
            sun_shape_ptr->setPara(
                std::get<3>(this->params["sun_shape"])->getPara());
            this->params[name] = SunShapeType(value.toInt());
            this->params["sun_shape"] = sun_shape_ptr;
            break;
        }
        }
    }
    auto Sun::getPara(const QString& name) const -> QVariant
    {
        // QVariant ret;
        // switch (_hash.at(name))
        // {
        // case 0:
        //     ret = azimuth;
        //     break;
        // case 1:
        //     ret = elevation;
        //     break;
        // case 2:
        //     ret = irradiance;
        //     break;
        // case 3:
        //     ret = trackable;
        //     break;
        // case 4:
        //     ret = sunshape_type;
        //     break;
        // case 5:
        //     ret = sunshape->getPara();
        //     break;
        // }
        // return ret;
        auto index = this->params.at(name).index();
        switch (index)
        {
        case 0:
        {
            if (name == "sun_shape")
            {
                return std::get<3>(this->params.at("sun_shape"))->getPara();
            }
            else
            {
                return std::get<0>(this->params.at(name));
            }
        }
        case 1:
            return std::get<1>(this->params.at(name));
        case 2:
            return std::get<2>(this->params.at(name));
        }
        qDebug() << std::format("In function {}:\n Invalid param key: {}",
                                __PRETTY_FUNCTION__, name.toStdString());
        throw std::invalid_argument("Invalid Param Key");
    }

    void Sun::testPrint() const
    {
        // qDebug() << "WorldPara::Sun: azimuth=" << azimuth
        //          << " elevation=" << elevation << " irradiance=" <<
        //          irradiance
        //          << " trackable=" << trackable << "\n \t\t"
        //          << " sunshape_type=" << sunshape_type
        //          << " sunshape.para=" << sunshape->getPara();
        qDebug() << std::format(
            "WorldPara::Sun: azimuth={}, elevation={}, irradiance={}, "
            "trackable={}, sun_shape_type={}, sun_shape.para={}",
            getPara("azimuth").toDouble(), getPara("elevation").toDouble(),
            getPara("irradiance").toDouble(), getPara("trackable").toBool(),
            static_cast<int>(getPara("sun_shape_type").value<SunShapeType>()),
            getPara("sun_shape").toDouble());
    }

    /*
    ============================================Air============================================
    */

    void Air::setPara(const QString& name, const QVariant& value)
    {
        // switch (_hash.at(name))
        // {
        // case 0:
        //     air_model_type = value.toInt();
        //     break;
        // }
        switch (this->params.at(name).index())
        {
        case 0:
            this->params[name] = AttenuationType(value.toInt());
        }
    }
    auto Air::getPara(const QString& name) const -> QVariant
    {
        // QVariant ret;
        // switch (_hash.at(name))
        // {
        // case 0:
        //     ret = air_model_type;
        //     break;
        // }
        // return ret;
        auto index = this->params.at(name).index();
        switch (index)
        {
        case 0:
            return std::get<0>(this->params.at(name));
        }
    }
    void Air::testPrint() const
    {
        qDebug() << std::format(
            "WorldPara::Air: air_model_type={}",
            static_cast<int>(
                getPara("air_model_type").value<AttenuationType>()));
    }

    /*
     * ==========================================Camera================================================
     */

    Camera::Camera(const Vec3& _position, const Vec3& _rotation_axis,
                   double _rotation_angle, bool _perspective)
    {
        this->params = {{"look_at", Vec3(0, 0, 0)},
                        {"up", Vec3(0, 1, 0)},
                        {"position", _position},
                        {"rotation_axis", _rotation_axis},
                        {"rotation_angle", _rotation_angle},
                        {"perspective", _perspective}};
        this->look_at = {0, 0, 0};
        this->up = {0, 1, 0};

        calculateUVW();
    }
    /*
    这个函数仍需完善：
            当position改变时，uvw也需要改变
            当rotation改变时，lookat、uvw均需要改变【这里是否需要矩阵计算？？】
            ！！！！！！！！！！还需要参考一下learnopengl中camera视角移动的部分
    */
    void Camera::setPara(const QString& name, const QVariant& value)
    {
        // switch (_hash.at(name))
        // {
        // case 0:
        //     position = value.value<Vec3>();
        //     calculateUVW();
        //     break;
        // case 1:
        //     rotation_axis = value.value<Vec3>();
        //     break;
        // case 2:
        //     rotation_angle = value.toDouble();
        //     break;
        // case 3:
        //     perspective = value.toBool();
        //     break;
        // }
        switch (this->params.at(name).index())
        {
        case 0:
            this->params[name] = value.value<Vec3>();
            break;
        case 1:
            this->params[name] = value.toDouble();
            break;
        case 2:
            this->params[name] = value.toBool();
        }
    }

    auto Camera::getPara(const QString& name) const -> QVariant
    {
        // QVariant ret;
        // switch (_hash.at(name))
        // {
        // case 0:
        //     ret.setValue(position);
        //     break;
        // case 1:
        //     ret.setValue(rotation_angle);
        //     break;
        // case 2:
        //     ret = rotation_angle;
        //     break;
        // case 3:
        //     ret = perspective;
        //     break;
        // }
        // return ret;
        auto index = this->params.at(name).index();
        QVariant ret;
        switch (index)
        {
        case 0:
            ret.setValue(std::get<0>(this->params.at(name)));
            break;
        case 1:
            ret.setValue(std::get<1>(this->params.at(name)));
            break;
        case 2:
            ret.setValue(std::get<2>(this->params.at(name)));
        }
        return ret;
    }

    void Camera::testPrint() const
    {
        // qDebug() << "WorldPara::Camera: position = (" << position.x() << ","
        //          << position.y() << "," << position.z()
        //          << ")  rotation_axis = (" << rotation_axis.x() << ","
        //          << rotation_axis.y() << "," << rotation_axis.z()
        //          << ")  rotation_angle = " << rotation_angle
        //          << "  perspective = " << perspective;
        qDebug() << std::format(
            "WorldPara::Camera: position={}, rotation_axis={}, "
            "rotation_angle={}, perspective={}",
            getPara("position").value<Vec3>().to_string(),
            getPara("rotation_axis").value<Vec3>().to_string(),
            getPara("rotation_angle").toDouble(),
            getPara("perspective").toBool());
    }

    void Camera::calculateUVW()
    {
        w = unit_vector(std::get<0>(this->params["position"]) -
                        look_at); // 注意，屏幕中心在w轴的负半轴上
        u = unit_vector(cross(up, w)); // 对应屏幕上的x轴
        v = cross(w, u);
    }

    /*
     * ==============================================Terrain========================================================

    */
    void Terrain::setPara(const QString& name, const QVariant& value)
    {
        // switch (_hash.at(name))
        // {
        // case 0:
        //     grid = value.toBool();
        //     break;
        // case 1:
        //     fill = value.toBool();
        //     break;
        // case 2:
        //     steps = value.value<Vec3>();
        //     break;
        // case 3:
        //     division = value.value<Vec3>();
        //     break;
        // case 4:
        //     min = value.value<Vec3>();
        //     break;
        // case 5:
        //     max = value.value<Vec3>();
        //     break;
        // case 6:
        //     file = value.toString();
        //     break;
        // }
        switch (this->params.at(name).index())
        {
        case 0:
            this->params[name] = value.toBool();
            break;
        case 1:
            this->params[name] = value.value<Vec3>();
            break;
        case 2:
            this->params[name] = value.toString();
        }
    }

    auto Terrain::getPara(const QString& name) const -> QVariant
    {
        // QVariant ret;
        // switch (_hash.at(name))
        // {
        // case 0:
        //     ret = grid;
        //     break;
        // case 1:
        //     ret = fill;
        //     break;
        // case 2:
        //     ret.setValue(steps);
        //     break;
        // case 3:
        //     ret.setValue(division);
        //     break;
        // case 4:
        //     ret.setValue(min);
        //     break;
        // case 5:
        //     ret.setValue(max);
        //     break;
        // case 6:
        //     ret = file;
        //     break;
        // }
        // return ret;
        QVariant ret;
        auto index = this->params.at(name).index();
        switch (index)
        {
        case 0:
            ret.setValue(std::get<0>(this->params.at(name)));
            break;
        case 1:
            ret.setValue(std::get<1>(this->params.at(name)));
            break;
        case 2:
            ret.setValue(std::get<2>(this->params.at(name)));
        }
        return ret;
    }

    void Terrain::testPrint() const {}

    /*
    ======================================================Cloud===============================================================
    */
    void Cloud::setPara(const QString& name, const QVariant& value)
    {
        // switch (_hash.at(name))
        // {
        // case 0:
        //     coordinate = value.value<Vec3>();
        //     break;
        // case 1:
        //     length = value.toDouble();
        //     break;
        // case 2:
        //     width = value.toDouble();
        //     break;
        // case 3:
        //     file = value.toString();
        //     break;
        // }
        switch (this->params.at(name).index())
        {
        case 0:
            this->params[name] = value.value<Vec3>();
            break;
        case 1:
            this->params[name] = value.toDouble();
            break;
        case 2:
            this->params[name] = value.toString();
        }
    }
    auto Cloud::getPara(const QString& name) const -> QVariant
    {
        // QVariant ret;
        // switch (_hash.at(name))
        // {
        // case 0:
        //     ret.setValue(coordinate);
        //     break;
        // case 1:
        //     ret = length;
        //     break;
        // case 2:
        //     ret = width;
        //     break;
        // case 3:
        //     ret = file;
        //     break;
        // }
        // return ret;
        QVariant ret;
        auto index = this->params.at(name).index();
        switch (index)
        {
        case 0:
            ret.setValue(std::get<0>(this->params.at(name)));
            break;
        case 1:
            ret.setValue(std::get<1>(this->params.at(name)));
            break;
        case 2:
            ret.setValue(std::get<2>(this->params.at(name)));
        }
        return ret;
    }
    void Cloud::testPrint() const {}

} // namespace solar
