
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "boost/describe/modifiers.hpp"
#include "scene/Scene.h"
#include "utils/Rotation.h"

#include <boost/describe.hpp>
#include <qdebug.h>
#include <qvariant.h>

#include <memory>
#include <string>
#include <type_traits>
#include <typeinfo>

namespace test1
{
    class A
    {
        public:
#include "class_name.inc"

    };
    class B
    {
        public:
#include "class_name.inc"

    };
}

    class test
    {
        public:
            void setPara(const std::string& property_type, const QVariant& value);
            [[nodiscard]] auto getPara(const std::string& property_type) const -> QVariant;
            void print() { qDebug() << "test: " << num1 << " " << num2; }

        private:
            int num1{};
            int num2{};
            std::shared_ptr<int> ptr1;
            BOOST_DESCRIBE_CLASS(test, (), (), (), (num1, num2, ptr1))
    };
    void test::setPara(const std::string& property_type, const QVariant& value)
    {
        using D1 = boost::describe::describe_members<std::remove_reference_t<decltype(*this)>,
                                                     boost::describe::mod_any_access>;
        bool found = false;
        boost::mp11::mp_for_each<D1>(
            [&](auto&& D)
            {
                if (D.name == property_type)
                {
                    found = true;
                    *this.*D.pointer =
                        value.value<std::remove_reference_t<decltype(*this.*D.pointer)>>();
                }
            });
        if (!found)
        {
            throw "ERROR::test::setPara()::NO SUCH PARA_PROPERTY: " + property_type;
        }
    }

    [[nodiscard]] auto test::getPara(const std::string& property_type) const -> QVariant
    {
        QVariant ret;
        using D1 = boost::describe::describe_members<test, boost::describe::mod_any_access>;
        bool found = false;
        boost::mp11::mp_for_each<D1>(
            [&](auto&& D)
            {
                if (D.name == property_type)
                {
                    found = true;
                    ret.setValue(*this.*D.pointer);
                }
            });
        return found ? ret
                     : throw "ERROR::test::getPara()::NO SUCH PARA_PROPERTY: " + property_type;
    }

    auto main(int argc, char* argv[]) -> int
    {
        // qDebug() << test1::A::name();
        // qDebug() << test1::B::name();
        // using D1 = boost::describe::describe_members<solar::Sun, boost::describe::mod_any_access>;
        // boost::mp11::mp_for_each<D1>([&](auto&& D) { qDebug() << D.name; });
        // test a;
        // auto ptr = std::make_shared<int>(3);
        // a.print();
        // QVariant var1 = 1;
        // QVariant var2 = 2;
        // QVariant var3;
        // var3.setValue(ptr);
        // a.setPara("num1", var1);
        // a.setPara("num2", var2);
        // a.setPara("ptr1", var3);
        // a.print();
        // qDebug() << "test: num1: " << a.getPara("num1");
        // qDebug() << "test: ptr1: " << *(a.getPara("ptr1").value<std::shared_ptr<int>>().get());
        qDebug() << solar::Rotation::name();
        solar::Rotation rotation;
        QVariant var1 = 2.0;
        rotation.setPara("angle_", var1);
        qDebug() << rotation.getPara("angle_");

        QGuiApplication app(argc, argv);

        QQmlApplicationEngine engine;
        const QUrl url(u"qrc:/solar_2/Main.qml"_qs);
        QObject::connect(
            &engine, &QQmlApplicationEngine::objectCreationFailed, &app,
            []() { QCoreApplication::exit(-1); }, Qt::QueuedConnection);

        // 设置上下文环境
        solar::Scene scene; // 要给scene类设置Q_OBJECT
        engine.rootContext()->setContextProperty(
            "topoControl",
            scene.topo_tree_control.get()); // 这里传入的应该是普通指针
        engine.rootContext()->setContextProperty("paraControl", scene.para_tree_control.get());

        engine.load(url);

        return QGuiApplication::exec();
    }
