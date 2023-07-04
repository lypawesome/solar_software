#pragma once

#include <concepts>
#include <string>
#include <string_view>
#include <type_traits>

namespace solar
{
    template <typename T>
    concept Number = std::integral<T> || std::floating_point<T>;

    template <typename T>
    concept Pointer = std::is_pointer_v<T>;

    template <typename T>
    concept ClassWithHasValue = requires(T value) {
        {
            value.hasValue()
        } -> std::same_as<bool>;
    };

    template <class T>
    concept ClassHasName = requires {
        {
            T::name()
        } -> std::same_as<std::string_view>;
    };

    template <typename T>
    concept ClassWithEmpty = requires(T value) {
        {
            value.empty()
        } -> std::same_as<bool>;
    };

    template <typename T>
    concept ClassWithToString = requires(T value) {
        {
            value.toString()
        } -> std::same_as<std::string>;
    };

    template <typename T>
    concept ClassWithFromString = requires(const std::string& input) {
        {
            T::fromString(input)
        } -> std::same_as<T>;
    };

    template <typename T>
    concept StringLike = std::is_same_v<std::string, T> || std::is_same_v<std::string_view, T>;

    template <typename T>
    concept Enum = std::is_enum_v<T>;

    template <typename T>
    concept ToStringConvertible = ClassWithToString<T> || StringLike<T> || Number<T> || Enum<T>;

    template <typename T>
    concept FromStringConvertible = ClassWithFromString<T> || StringLike<T> || Number<T> || Enum<T>;
} // namespace solar
