
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
#include <vector>

#include "SunShape.h"
#include "SunPosition.h"
#include "Attenuation.h"
#include "Vec3.h"
#include "Rotation.h"
#include "Grid.h"
#include "Geometry.h"
#include "Profile.h"
#include "Material.h"
#include "Armature.h"
#include "Target.h"

namespace solar{




    class Para
    {
    public:
        virtual void setPara(
            const int property_type,
            const QVariant&
                value) = 0; // 纯虚函数,用来设置一个参数的值[不要加const，因为要对值进行修改]
        [[nodiscard]] virtual auto getPara(const int property_type) const
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
        Location(std::string site_name = "unknown", double longitude = 0, double latitude = 0)
            : site_name_(site_name), longitude_(longitude), latitude_(latitude) {}


        void setPara(const int property_type, const QVariant& value) override;
        [[nodiscard]] auto getPara(const int property_type) const
            -> QVariant override;
        void testPrint() const override;

    private:
        std::string site_name_;
        double longitude_;
        double latitude_;
    };

    /*
     * ================================Sun====================================
     * 这里可以用工厂模式重构一下
    */
    class Sun : public Para
    {
    public:
        Sun()
        {
            sunshape_ = std::make_shared<PillboxSunShape>();       //先放高斯
            sun_position_ = std::make_shared<SunPosition>();
        }


        void setPara(const int property_type, const QVariant& value) override;
        [[nodiscard]] auto getPara(const int property_type) const
            -> QVariant override;
        void testPrint() const override;

    private:
        std::shared_ptr<SunShape> sunshape_;
        std::shared_ptr<SunPosition> sun_position_;
    };

//    /*
//    =======================================Air============================================
//    */
//    class Air : public Para
//    {
//    public:
//        virtual ~Air() = default;
//        Air()
//        {
//            attenuation_ =std::make_shared<VacuumAttenuation>();
//        }

//        void setPara(const int property_type, const QVariant& value) override;
//        [[nodiscard]] auto getPara(const int property_type) const
//            -> QVariant override;
//        void testPrint() const override;

//    private:
//        std::shared_ptr<Attenuation> attenuation_;
//    };

//    /*
//    ====================================Camera=================================================
//    相机可以设置的参数为：position、rotation、perspective，其他的要么是默认的，要么需要通过计算得出
//    */
//    class Camera : public Para
//    {
//    public:
//        // Camera(){};
//        Camera(const Vec3& position = Vec3(-2, -10, 2),
//               const Vec3& rotation_axis = Vec3(0, 1, 0),
//               double rotation_angle = 0, bool perspective = false)
//            : position_(position),rotation_(Rotation(rotation_axis,rotation_angle)), perspective_(perspective)
//        { }

//        void setPara(const int property_type, const QVariant& value) override;
//        [[nodiscard]] auto getPara(const int property_type) const
//            -> QVariant override;
//        void testPrint() const override;

//    private:
//        //不进行计算的话，这几个参数没必要写
////        Vec3 look_at_; // 相机看向的目标位置
////        Vec3 up_;      // 相机向上的轴向
////        Vec3 u_, v_, w_; // 相机上的标架，以position为坐标原点

//        Vec3 position_;
//        Rotation rotation_;
//        bool perspective_;
//    };

//    /*
//    ====================================Terrain====================================================
//    Terrain类还需要补充完善
//    */
//    class Terrain : public Para
//    {
//    public:
//        virtual ~Terrain() = default;
//        Terrain()
//        {
//            grid_ = std::make_shared<Grid>();
//        }

//        void setPara(const int property_type, const QVariant& value) override;
//        [[nodiscard]] auto getPara(const int property_type) const
//            -> QVariant override;
//        void testPrint() const override;

//    private:
//        void readFile();        //从file中导入heights

//    private:
//        std::shared_ptr<Grid> grid_;
//        std::vector<std::vector<double>> heights_; // 从file中导入的，每个格子的高度
//    };

//    /*
//     ================================================Cloud===================================================
//    这里的成员变量可能还要更改
//        也用Grid来写
//    */
//    class Cloud : public Para
//    {
//    public:
//        virtual ~Cloud() = default;
//        // Cloud(){};
//        Cloud()
//        {
//            grid_ = std::make_shared<Grid>();
//        }

//        void setPara(const int property_type, const QVariant& value) override;
//        [[nodiscard]] auto getPara(const int property_type) const
//            -> QVariant override;
//        void testPrint() const override;

//    private:
//        void readFile();
//    private:
//        std::shared_ptr<Grid> grid_;
//        std::vector<std::vector<double>> k_; // 衰减因子k的数组，从文件中读取获得当光线经过云层时，DNI变为k*DNI

//    };

//    /*
//     * ================================================Node================================================
//        Node这里，放一个Transform，由位移、旋转、放缩组成
//        kTranslation, kAxis, kAngle, kScale
//    */
//    class Node : public Para
//    {
//    public:
//        virtual ~Node() = default;
//        Node(const Vec3& translation=Vec3(0,0,0), const Vec3& rotation_axis=Vec3(0,0,1),
//             double rotation_angle=0.0, const Vec3& scale=Vec3(1,1,1))
//            : translation_(translation), rotation_(Rotation(rotation_axis,rotation_angle)),scale_(scale)
//        { }

//        void setPara(const int property_type, const QVariant& value) override;
//        [[nodiscard]] auto getPara(const int property_type) const
//            -> QVariant override;
//        void testPrint() const override;

//    private:
//        Vec3 translation_;     //位移
//        Rotation rotation_;     //旋转
//        Vec3 scale_;               //放缩
//    };


//        /*
//         * ==============================================Shape===================================================
//         Material还没写好，先放着
//        kGeometry, kA, kB, kC, kFile
//        kProfile, kRectU, kRectV,kCircleRadius, kCirclePhi,kRegularEdgeLength, kRegularEdgeCnt,
//                    kTriA, kTriB, kTriC, kPolyPoints,
//        kMaterial

//        增加吸热管组成的面板
//        */
//    class Shape : public Para
//    {
//        public:
//            virtual ~Shape() = default;
//            Shape()
//            {
//                geometry_ = std::make_shared<Planar>();         //这里可以用工厂模式重构
//                profile_ = std::make_shared<Rectangular>();
//                material_ = std::make_shared<Reflect>();
//            }

//            void setPara(const int property_type, const QVariant& value) override;
//            [[nodiscard]] auto getPara(const int property_type) const
//                -> QVariant override;
//            void testPrint() const override;

//        private:
//            std::shared_ptr<Geometry> geometry_;
//            std::shared_ptr<Profile> profile_;
//            std::shared_ptr<Material> material_;
//            std::shared_ptr<HeatTubePaneReceiver> heat_tube_pane_;


//    };

//        /*
//         * ==============================================Tracker===================================================
//        跟踪器
//         */

//    class Tracker : public Para
//    {
//        public:
//            virtual ~Tracker() = default;
//            Tracker():enabled_(false)
//            {
//                armature_ = std::make_shared<OneAxis>();
//                target_ = std::make_shared<Target>();
//            }

//            void setPara(const int property_type, const QVariant& value) override;
//            [[nodiscard]] auto getPara(const int property_type) const
//                                -> QVariant override;
//            void testPrint() const override;

//        private:
//            bool enabled_;
//            std::shared_ptr<Armature> armature_;
//            std::shared_ptr<Target> target_;
//    };

//        /*
//         * ==============================================Array===================================================
//        array的部分，感觉有点鸡肋，可能需要删去
//         */
//        class Array : public Para
//        {
//            public:
//                virtual ~Array() = default;
//                Array(const std::string& positions, int nMax)
//                    : positions_(positions), nMax_(nMax) {}


//                void setPara(const int property_type, const QVariant& value) override;
//                [[nodiscard]] auto getPara(const int property_type) const
//                    -> QVariant override;
//                void testPrint() const override;

//            private:
//                std::string positions_;    //按照[1,0,0 0,1,0]来输入点的位置
//                int nMax_;                 //最大个数

//        };

} //namespace std

#endif // PARA_H
