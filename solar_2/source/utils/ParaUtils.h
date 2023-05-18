#pragma once

#include <QVariant>

#include <string>
#include <string_view>
#include <type_traits>

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
                if (D.name == property_type)
                {
                    found = true;
                    *object.*D.pointer =
                        value.value<std::remove_reference_t<decltype(*object.*D.pointer)>>();
                }
            });
        if (!found) [[unlikely]]
        {
            qDebug() << ::solar::format("ERROR: {}::setPara(): No such property: {}", NamedClass::name(),
                               property_type);
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
                if (D.name == property_type)
                {
                    found = true;
                    ret.setValue(*object.*D.pointer);
                }
            });
        if (!found) [[unlikely]]
        {
            qDebug() << ::solar::format("ERROR: {}::getPara(): No such property: {}", NamedClass::name(),
                               property_type);
            throw ::solar::format("ERROR: {}::getPara(): No such property: {}", NamedClass::name(),
                         property_type);
        }
        return ret;
    }

    PURE_FUNCTION constexpr auto toMemberName(const std::string& original_name) -> std::string
    {
        return original_name + "_";
    }
} // namespace solar
