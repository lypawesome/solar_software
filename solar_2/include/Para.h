
#ifndef PARA_H
#define PARA_H


/*
所有需要设置参数的类，在这里定义，包括右上方world和topo的参数
一个虚基类：Para
其他为派生类：Location、Sun、Air、Camera、Terrain、Cloud、Node、Shape、Tracker、Array

para中的每个类的params中，存的都是在UI中可以更改的属性

注意，这个类文件里，采用C++的数据类型

！！！！除了要与UI交互的函数用QVariant，其他的都用std::any
*/

#include <QList>
#include <QString>
#include <QDebug>
#include <QVariant>

#include <memory>
#include <unordered_map>
#include <utility>
#include <variant>
#include <any>

#include "SunShape.h"
#include "SunPosition.h"
#include "Attenuation.h"
#include "Vec3.h"
#include "Rotation.h"

namespace solar{



    class Para
    {
    public:
        virtual void setPara(
            const std::string& name,
            const QVariant&
                value) = 0; // 纯虚函数,用来设置一个参数的值[不要加const，因为要对值进行修改]
        [[nodiscard]] virtual auto getPara(const std::string& name) const
            -> QVariant = 0;
        virtual void testPrint() const = 0; // 纯虚函数，输出参数的内容进行测试

    protected:
        Para() = default;
    };

    /*
     * ===========================Location===================================

    */
    class Location : public Para
    {
    public:
        Location(std::string _name = "", double _longitude = 0,
                 double _latitude = 0)
        {
            this->params = {{"site_name", _name},           //地名----std::string
                            {"longitude", _longitude},      //经度----double
                            {"latitude", _latitude}};       //纬度----double
        }

        void setPara(const std::string& name, const QVariant& value) override;
        [[nodiscard]] auto getPara(const std::string& name) const
            -> QVariant override;
        void testPrint() const override;

    private:
        std::unordered_map<std::string, std::any> params;
    };

    /*
     * ================================Sun====================================
    */
    class Sun : public Para
    {
    public:
        Sun()
        {
            std::shared_ptr<SunShape> _sunshape = std::make_shared<GaussianSunShape>();
            std::shared_ptr<SunPosition> _position = std::make_shared<SunPosition>();
            this->params = {
                {"sunshape", _sunshape},        //太阳形状---std::shared_ptr<SunShape>
                {"position", _position}         //太阳的位置--std::shared_ptr<SunPosition>
            };
        }


        void setPara(const std::string& name, const QVariant& value) override;
        [[nodiscard]] auto getPara(const std::string& name) const
            -> QVariant override;
        void testPrint() const override;

    private:
        std::unordered_map<std::string, std::any> params;
    };

    /*
    =======================================Air============================================
    */
    class Air : public Para
    {
    public:
        virtual ~Air() = default;
        Air()
        {
            std::shared_ptr<Attenuation> _attenuation =std::make_shared<VacuumAttenuation>();
            this->params = {
                {"attenuation", _attenuation}       //大气衰减模型---std::shared_ptr<Attenuation>
            };
        }

        void setPara(const std::string& name, const QVariant& value) override;
        [[nodiscard]] auto getPara(const std::string& name) const
            -> QVariant override;
        void testPrint() const override;

    private:
        std::unordered_map<std::string, std::any> params;
    };

    /*
    ====================================Camera=================================================
    相机可以设置的参数为：position、rotation、perspective，其他的要么是默认的，要么需要通过计算得出
    ！！！camera类还需要补充完善
    */
    class Camera : public Para
    {
    public:
        // Camera(){};
        Camera(const Vec3& _position = Vec3(-2, -10, 2),
               const Vec3& _rotation_axis = Vec3(0, 1, 0),
               double _rotation_angle = 0, bool _perspective = false)
        {
            this->params = {{"look_at", Vec3(0, 0, 0)},         // 看向的点----Vec3
                            {"up", Vec3(0, 1, 0)},              //相机向上的方向---Vec3
                            {"position", _position},            //相机位置---Vec3
                            {"rotation", Rotation(_rotation_axis, _rotation_angle)},    //旋转---Rotation
                            {"perspective", _perspective}};     //是否透视---bool
            this->look_at = {0, 0, 0};
            this->up = {0, 1, 0};

            calculateUVW();
        }

        void setPara(const std::string& name, const QVariant& value) override;
        [[nodiscard]] auto getPara(const std::string& name) const
            -> QVariant override;
        void testPrint() const override;

    private:
        void calculateUVW(); // 计算得到uvw

    private:
        Vec3 look_at; // 相机看向的目标位置
        Vec3 up;      // 相机向上的轴向
        Vec3 u, v, w; // 相机上的标架，以position为坐标原点

        std::unordered_map<std::string, std::any> params;
    };

    /*
    ====================================Terrain====================================================
    Terrain类还需要补充完善
    */
    class Terrain : public Para
    {
    public:
        virtual ~Terrain() = default;
        // Terrain(){};
        Terrain(bool _grid = true, bool _fill = true,
                const Vec3& _steps = Vec3(1, 1, 1),
                const Vec3& _division = Vec3(5, 5, 5),
                const Vec3& _min = Vec3(-10, -10, 0),
                const Vec3& _max = Vec3(10, 10, 0),
                const std::string& _file = "")
        {
            this->params = {{"grid", _grid},
                            {"fill", _fill},
                            {"steps", _steps},
                            {"division", _division},
                            {"min", _min},
                            {"max", _max},
                            {"file", _file}};
            //补充：从文件file中读取每个格子的高度

        }
        void setPara(const std::string& name, const QVariant& value) override;
        [[nodiscard]] auto getPara(const std::string& name) const
            -> QVariant override;
        void testPrint() const override;

    private:
        void readFile();        //从file中导入heights

    private:
        QList<QList<double>> heights; // 从file中导入的，每个格子的高度
        std::unordered_map<std::string, std::any> params;
    };

    /*
     ================================================Cloud===================================================
    这里的成员变量可能还要更改
    */
    class Cloud : public Para
    {
    public:
        virtual ~Cloud() = default;
        // Cloud(){};
        Cloud(const Vec3& _coordinate = Vec3(10, 0, 0), double _length = 0,
              double _width = 0, const std::string& _file = "")
        {
            this->params = {{"coordinate", _coordinate},        //云层中心坐标---Vec3
                            {"length", _length},                //云层的长------double
                            {"width", _width},                  //云层的宽------double
                            {"file", _file}};                   //保存衰减因子k的文件名---std::string
            //补充：：从文件中读取数据
        }

        void setPara(const std::string& name, const QVariant& value) override;
        [[nodiscard]] auto getPara(const std::string& name) const
            -> QVariant override;
        void testPrint() const override;

    private:

        QList<QList<double>> k; // 衰减因子k的数组，从文件中读取获得当光线经过云层时，DNI变为k*DNI

        std::unordered_map<std::string, std::any> params;
    };

    /*
     * ================================================Node================================================
        Node这里，放一个Transform，由位移、旋转、放缩组成
    */
    class Node : public Para
    {
    public:
        virtual ~Node() = default;
        Node(const Vec3& _translation=Vec3(0,0,0), const Vec3& _rotation_axis=Vec3(0,0,1),
             double _rotation_angle=0.0, const Vec3& _scale=Vec3(1,1,1))
        {
            this->params = {    {"translation", _translation},          // 位移---Vec3
                                {"rotation", Rotation(_rotation_axis,_rotation_angle)},     //旋转---Rotation
                                {"scale", _scale}           //缩放---Vec3
                                                    };
        }

        void setPara(const std::string& name, const QVariant& value) override;
        [[nodiscard]] auto getPara(const std::string& name) const
            -> QVariant override;
        void testPrint() const override;

    private:
        //Vec3 translation;     //位移
        //Vec3 rotation_axis;   //旋转轴
        //double rotation_angle;    //旋转角度
        //Vec3 scale;               //放缩
        std::unordered_map<std::string, std::any > params;
    };


        /*
         * ==============================================Shape===================================================
         另外写类：shapeRT、profileRT、materialRT、material
        */
        class Shape : public Para
        {
            public:
                virtual ~Shape() = default;
                Shape()
                {}

                void setPara(const std::string& name, const QVariant& value) override;
                [[nodiscard]] auto getPara(const std::string& name) const
                    -> QVariant override;
                void testPrint() const override;

            private:
                //std::shared_ptr<ShapeRT> shapeRT;
                //std::shared_ptr<ProfileRT> profileRT;
                //std::shared_ptr<MaterialRT> materialRT;
                //std::shared_ptr<Material> material;

                std::unordered_map<QString, QVariant> params;
        };

        /*
         * ==============================================Tracker===================================================
        跟踪器
         */
        class Tracker : public Para
        {
            public:
                virtual ~Tracker() = default;
                Tracker()
                {}

            private:
                bool enabled;
                std::shared_ptr<Armature> armature;
                std::shared_ptr<Target> target;

                std::unordered_map<QString, QVariant> params;
        };

        /*
         * ==============================================Array===================================================
        array的部分，感觉有点鸡肋，看看tonatiuh是怎么用的
         */
        class Array : public Para
        {
            public:
                virtual ~Array() = default;
                Array(const std::string& _positions, int _nMax)
                {
                    this->params = {
                                    {"positions", _positions},
                                    {"nMax", _nMax}                  };
                }

            private:
                //std::string positions;    //按照[1,0,0 0,1,0]来输入点的位置
                //int nMax;                 //最大个数
                //QVariant与std::any类似
                std::unordered_map<std::string, std::variant<std::string,int>> params;
        };

} //namespace std

#endif // PARA_H
