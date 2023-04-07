#pragma once

/*
 * worldpara是全局的一些参数：sun，location，air，camera，terrain
 *
 *
 */

#include <QList>
#include <QString>


#include "SunShape.h"
#include "Vec3.h"

namespace solar
{
    class WorldPara
    {
        public:
            WorldPara(){};

            // 这个虚函数有点问题-----无法设置具体的某个参数
            // 解决方法：：：给每个参数分配一个index
            virtual void setPara(
                QString name,
                QVariant
                    value) = 0; // 纯虚函数,用来设置一个参数的值[不要加const，因为要对值进行修改]
            virtual QVariant getPara(QString name) const = 0; // 获取某个参数
            virtual void
            testPrint() const = 0; // 纯虚函数，输出参数的内容进行测试
    };

    /*
     * ===========================Location===================================

    */
    class Location : public WorldPara
    {
        public:
            Location(){};
            Location(QString _name, double _longitude, double _latitude)
                : site_name(_name), longitude(_longitude),
                  latitude(_latitude){};

            virtual void setPara(QString name, QVariant value) override;
            virtual QVariant getPara(QString name) const override;
            virtual void testPrint() const override;

        private:
            QString site_name; // 地名
            double longitude;  // 经度
            double latitude;   // 纬度

            std::unordered_map<QString, int> _hash{
                {"site_name", 0}, {"longitude", 1}, {"latitude", 2}};
    };

    /*
     * ================================Sun====================================
        sun中的sunshape有不同种类的，每种sunshape的参数类型不一样，如何解决？？？
        解决方案：写一个sunshape的基类，不同sunshape类型如高斯，pillbox等，分别写一个派生类
    */
    class Sun : public WorldPara
    {
            enum SunShapeType
            {
                PILLBOX,
                BUIE,
                GAUSSION
            };

        public:
            Sun(double _azimuth, double _elevation, double _irradiance,
                bool _trackable, int _sunshape_type);
            ~Sun(); // 在构造函数用new分配的空间要手动释放

            virtual void setPara(QString name, QVariant value) override; //
            virtual QVariant getPara(QString name) const override;
            virtual void testPrint() const override;

        private:
            void
            reallocateSunshape(int _sunshape_type); // 重新分配sunshape的内存

        private:
            // position
            double azimuth;    // 方位角
            double elevation;  // 天顶角
            double irradiance; // 辐射度
            bool trackable;    // 是否可追踪

            // sunshape
            int sunshape_type;
            SunShape* sunshape = nullptr; // 太阳形状

            std::unordered_map<QString, int> _hash{
                {"azimuth", 0},   {"elevation", 1},    {"irradiance", 2},
                {"trackable", 3}, {"sunshapeKind", 4}, {"sunshape", 5}};
    };

    /*
    =======================================Air============================================
    大气衰减模型---再查一下资料，把这一部分的模型写好
    */
    class Air : public WorldPara
    {
            enum AttenuationType
            {
                VACUUM,
                EXPONENTIAL,
                CUSTOM // 无大气衰减，指数模型，常用的经验模型
            };

        public:
            Air(){};
            Air(int _air_model_type) : air_model_type(_air_model_type){};

            virtual void setPara(QString name, QVariant value) override;
            virtual QVariant getPara(QString name) const override;
            virtual void testPrint() const override;

        private:
            int air_model_type;
            // AttenuationModel* air_model;    //写一个大气衰减模型的类和子类

            std::unordered_map<QString, int> _hash{{"air_model_type", 0}};
    };

    /*
    ====================================Camera=================================================
    相机可以设置的参数为：position、rotation、perspective，其他的要么是默认的，要么需要通过计算得出

    */
    class Camera : public WorldPara
    {
        public:
            Camera(){};
            Camera(const Vec3& _position, const Vec3& _rotation_axis,
                   double _rotation_angle, bool _perspective);

            virtual void setPara(QString name, QVariant value) override;
            virtual QVariant getPara(QString name) const override;
            virtual void testPrint() const override;

        private:
            void calculateUVW(); // 计算得到uvw

        private:
            Vec3 position; // 相机所在的位置
            Vec3 lookat;   // 相机看向的目标位置
            Vec3 up;       // 相机向上的轴向

            Vec3 u, v, w;  // 相机上的标架，以position为坐标原点

            Vec3 rotation_axis;
            double rotation_angle;
            bool perspective;

            std::unordered_map<QString, int> _hash{{"position", 0},
                                                   {"rotation_axis", 1},
                                                   {"rotation_angle", 2},
                                                   {"perspective", 3}};
    };

    /*
    ====================================Terrain====================================================
    */
    class Terrain : public WorldPara
    {
        public:
            Terrain(){};
            Terrain(bool _grid, bool _fill, const Vec3& _steps,
                    const Vec3& _division, const Vec3& _min, const Vec3& _max,
                    const QString& _file)
                : grid(_grid), fill(_fill), steps(_steps), division(_division),
                  min(_min), max(_max), file(_file){};

            virtual void setPara(QString name, QVariant value) override;
            virtual QVariant getPara(QString name) const override;
            virtual void testPrint() const override;

        private:
            bool grid;
            bool fill;
            Vec3 steps;
            Vec3 division;
            Vec3 min;
            Vec3 max;
            QString file;

            QList<QList<double>> height; // 从file中导入的，每个格子的高度

            std::unordered_map<QString, int> _hash{
                {"grid", 0}, {"fill", 1}, {"steps", 2}, {"division", 3},
                {"min", 4},  {"max", 5},  {"file", 6}};
    };

    /*
     ================================================Cloud===================================================
    这里的成员变量可能还要更改
    */
    class Cloud : public WorldPara
    {
        public:
            Cloud(){};
            Cloud(const Vec3& _coordinate, double _length, double _width,
                  QString _file)
                : coordinate(_coordinate), length(_length), width(_width),
                  file(_file){};

            virtual void setPara(QString name, QVariant value) override;
            virtual QVariant getPara(QString name) const override;
            virtual void testPrint() const override;

        private:
            Vec3 coordinate; // 云层中心的坐标
            double length;   // 云层的长、宽
            double width;
            QString file;    // 文件名

            QList<QList<double>>
                k; // 衰减因子k的数组，当光线经过云层时，DNI变为k*DNI

            std::unordered_map<QString, int> _hash{
                {"coordinate", 0}, {"length", 1}, {"width", 2}, {"file", 3}};
    };

} // namespace solar
