#pragma once

#include "utils/HasValue.h"
#include <QString>
#include <QVariant>

#include <any>
#include <string>
#include <string_view>
#include <type_traits>
#include <version>

#include <boost/describe.hpp>

#include <utils/Concepts.h>
#include <utils/Format.h>
#include <utils/HasValue.h>
#include <utils/StringUtils.h>
#include <utils/config.h>

namespace solar
{
    template <ClassHasName NamedClass>
    void setPara(const std::string& property_type, const QVariant& value, NamedClass* object)
    {
        ASSUME(!property_type.empty());
        ASSUME(object);
        using D1 = boost::describe::describe_members<std::remove_reference_t<NamedClass>,
                                                     boost::describe::mod_any_access>;
        bool found = false;
        boost::mp11::mp_for_each<D1>(
            [&](auto&& D)
            {
                if (!found && D.name == property_type)
                {
                    // qDebug() << "D.name=" << D.name
                    //          << "  property_type=" << QString::fromStdString(property_type);

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
        ASSUME(!property_type.empty());
        ASSUME(object);
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
                    // qDebug() <<"----------*object.*D.pointer="<<*object.*D.pointer;
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
        // qDebug()<<"----------- ret = "<<ret;
        return ret;
    }

    template <ClassHasName NamedClass>
    void setPara(const std::string& property_type, const std::any& value, NamedClass* object)
    {
        ASSUME(!property_type.empty());
        ASSUME(object);
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
        ASSUME(!property_type.empty());
        ASSUME(object);
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

    template <ClassHasName NamedClass>
    [[nodiscard]] auto getParaPtr(const std::string& property_type, NamedClass* object) -> std::any
    {
        ASSUME(!property_type.empty());
        ASSUME(object);
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
                    ret = std::addressof(*object.*D.pointer);
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

    template <ClassHasName NamedClass>
    [[nodiscard]] auto getParaAsString(const std::string& property_type, NamedClass* object)
        -> std::string
    {
        ASSUME(!property_type.empty());
        ASSUME(object);
        std::string ret;
        using D1 = boost::describe::describe_members<std::remove_reference_t<NamedClass>,
                                                     boost::describe::mod_any_access>;
        bool found = false;
        boost::mp11::mp_for_each<D1>(
            [&](auto&& D)
            {
                if (!found && D.name == property_type)
                {
                    found = true;
                    if constexpr (ToStringConvertible<
                                      std::remove_reference_t<decltype(*object.*D.pointer)>>)
                    {
                        ret = ::solar::toString(*object.*D.pointer);
                    }
                    else
                    {
                        qDebug() << QString(
                            ::solar::format(R"(ERROR: solar::getParaAsString(): Can't convert "
                                            "property "{}" in "{}" to string)",
                                            NamedClass::name(), property_type)
                                .c_str());
                    }
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

    template <ClassHasName NamedClass>
    void setParaFromString(const std::string& property_type, const std::string& value,
                           NamedClass* object)
    {
        ASSUME(!property_type.empty());
        ASSUME(!value.empty());
        ASSUME(object);
        using D1 = boost::describe::describe_members<std::remove_reference_t<NamedClass>,
                                                     boost::describe::mod_any_access>;
        bool found = false;
        boost::mp11::mp_for_each<D1>(
            [&](auto&& D)
            {
                if (!found && D.name == property_type)
                {
                    found = true;
                    if constexpr (FromStringConvertible<
                                      std::remove_reference_t<decltype(*object.*D.pointer)>>)
                    {
                        *object.*D.pointer = ::solar::fromString<
                            std::remove_reference_t<decltype(*object.*D.pointer)>>(value);
                    }
                    else
                    {
                        qDebug() << QString(
                            ::solar::format(R"(ERROR: solar::setParaFromString(): Can't convert "
                                            "property "{}" in "{}" from string)",
                                            NamedClass::name(), property_type)
                                .c_str());
                    }
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
    auto paraHasValue(const std::string& property_type, NamedClass* object) -> bool
    {
        ASSUME(!property_type.empty());
        ASSUME(object);
        bool ret = false;
        using D1 = boost::describe::describe_members<std::remove_reference_t<NamedClass>,
                                                     boost::describe::mod_any_access>;
        bool found = false;
        boost::mp11::mp_for_each<D1>(
            [&](auto&& D)
            {
                if (!found && D.name == property_type)
                {
                    found = true;
                    ret = ::solar::hasValue(*object.*D.pointer);
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
