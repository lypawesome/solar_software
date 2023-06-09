#pragma once

#include <QString>
#include <QVariant>

#include <any>
#include <string>
#include <string_view>
#include <type_traits>
#include <version>

#include <boost/describe.hpp>

#include <utils/Format.h>
#include <utils/config.h>

namespace solar
{
    template <class T>
    concept ClassHasName = requires {
        {
            T::name()
        } -> std::same_as<std::string_view>;
    };

    template <ClassHasName NamedClass>
    void setPara(const std::string& property_type, const QVariant& value, NamedClass* object)
    {
        using D1 = boost::describe::describe_members<std::remove_reference_t<NamedClass>,
                                                     boost::describe::mod_any_access>;
        bool found = false;
        boost::mp11::mp_for_each<D1>(
            [&](auto&& D)
            {
                if (!found && D.name == property_type)
                {
                    qDebug() <<"D.name="<<D.name<<"  property_type="<<QString::fromStdString(property_type);
                    
                    found = true;
                    *object.*D.pointer =
                        value.value<std::remove_reference_t<decltype(*object.*D.pointer)>>();
                }
            });
        if (!found) [[unlikely]]
        {
            qDebug() << QString(::solar::format("ERROR: {}::setPara(): No such property: {}",
                                                NamedClass::name(), property_type)
                                    .c_str());
            throw ::solar::format("ERROR: {}::setPara(): No such property: {}", NamedClass::name(),
                                  property_type);
        }
    }

    template <ClassHasName NamedClass>
    [[nodiscard]] auto getPara(const std::string& property_type, const NamedClass* const object)
        -> QVariant
    {
        QVariant ret;
        using D1 = boost::describe::describe_members<std::remove_reference_t<NamedClass>,
                                                     boost::describe::mod_any_access>;
        bool found = false;
        boost::mp11::mp_for_each<D1>(
            [&](auto&& D)
            {
                if (!found && D.name == property_type)
                {
                    found = true;
                    ret.setValue(*object.*D.pointer);
                    //qDebug() <<"----------*object.*D.pointer="<<*object.*D.pointer;
                }
            });
        if (!found) [[unlikely]]
        {
            qDebug() << QString(::solar::format("ERROR: {}::getPara(): No such property: {}",
                                                NamedClass::name(), property_type)
                                    .c_str());
            throw ::solar::format("ERROR: {}::getPara(): No such property: {}", NamedClass::name(),
                                  property_type);
        }
        //qDebug()<<"----------- ret = "<<ret;
        return ret;
    }

    template <ClassHasName NamedClass>
    void setPara(const std::string& property_type, const std::any& value, NamedClass* object)
    {
        using D1 = boost::describe::describe_members<std::remove_reference_t<NamedClass>,
                                                     boost::describe::mod_any_access>;
        bool found = false;
        boost::mp11::mp_for_each<D1>(
            [&](auto&& D)
            {
                if (!found && D.name == property_type)
                {
                    found = true;
                    *object.*D.pointer =
                        std::any_cast<std::remove_reference_t<decltype(*object.*D.pointer)>>(value);
                }
            });
        if (!found) [[unlikely]]
        {
            qDebug() << QString(::solar::format("ERROR: {}::setPara(): No such property: {}",
                                                NamedClass::name(), property_type)
                                    .c_str());
            throw ::solar::format("ERROR: {}::setPara(): No such property: {}", NamedClass::name(),
                                  property_type);
        }
    }

    template <ClassHasName NamedClass>
    [[nodiscard]] auto getParaAsAny(const std::string& property_type,
                                    const NamedClass* const object) -> std::any
    {
        std::any ret;
        using D1 = boost::describe::describe_members<std::remove_reference_t<NamedClass>,
                                                     boost::describe::mod_any_access>;
        bool found = false;
        boost::mp11::mp_for_each<D1>(
            [&](auto&& D)
            {
                if (!found && D.name == property_type)
                {
                    found = true;
                    ret = *object.*D.pointer;
                }
            });
        if (!found) [[unlikely]]
        {
            qDebug() << QString(::solar::format("ERROR: {}::getPara(): No such property: {}",
                                                NamedClass::name(), property_type)
                                    .c_str());
            throw ::solar::format("ERROR: {}::getPara(): No such property: {}", NamedClass::name(),
                                  property_type);
        }
        return ret;
    }

#ifdef _GLIBCXX_VERSION_INCLUDED
    PURE_FUNCTION inline auto toMemberName(const std::string& original_name) -> std::string
    {
        return original_name + "_";
    }
#else
    PURE_FUNCTION constexpr auto toMemberName(const std::string& original_name) -> std::string
    {
        return original_name + "_";
    }
#endif

} // namespace solar
