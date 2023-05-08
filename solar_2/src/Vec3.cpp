#include "Vec3.h"
#include "Utils.h"

#include <cmath>
#include <format>

namespace solar
{
[[nodiscard]] PURE_FUNCTION auto Vec3::x() const -> double
{
    return this->internal_vector[0];
}

[[nodiscard]] PURE_FUNCTION auto Vec3::y() const -> double
{
    return this->internal_vector[1];
}

[[nodiscard]] PURE_FUNCTION auto Vec3::z() const -> double
{
    return this->internal_vector[2];
}

void Vec3::set_x(double input_x)
{
    this->internal_vector.insert(0, input_x);
}

void Vec3::set_y(double input_y)
{
    this->internal_vector.insert(1, input_y);
}

void Vec3::set_z(double input_z)
{
    this->internal_vector.insert(2, input_z);
}

[[nodiscard]] PURE_FUNCTION auto Vec3::operator-() const -> Vec3
{
    return -this->internal_vector;
}

auto Vec3::operator+=(const Vec3& vec) -> Vec3
{
    this->internal_vector += vec.internal_vector;
    return *this;
}

auto Vec3::operator-=(const Vec3& vec) -> Vec3
{
    this->internal_vector -= vec.internal_vector;
    return *this;
}

auto Vec3::operator*=(const Vec3& vec) -> Vec3
{
    this->internal_vector *= vec.internal_vector;
    return *this;
}

auto Vec3::operator/=(const Vec3& vec) -> Vec3
{
    this->internal_vector /= vec.internal_vector;
    return *this;
}

auto Vec3::operator*=(const double& value) -> Vec3
{
    this->internal_vector *= value;
    return *this;
}

auto Vec3::operator/=(const double& value) -> Vec3
{
    this->internal_vector /= value;
    return *this;
}

[[nodiscard]] PURE_FUNCTION auto Vec3::squared_length() const -> double
{
    return vcl::horizontal_add(vcl::square(this->internal_vector));
}

[[nodiscard]] PURE_FUNCTION auto Vec3::length() const -> double
{
    return std::sqrt(squared_length());
}

void Vec3::make_unit_vector()
{
    this->internal_vector *= inv_sqrt(squared_length());
}

[[nodiscard]] PURE_FUNCTION auto Vec3::get_vec() const -> vcl::Vec4d
{
    return this->internal_vector;
}

[[nodiscard]] PURE_FUNCTION auto Vec3::data() const -> std::array<double, 3>
{
    std::array<double, 3> result = {};
    this->internal_vector.store_partial(3, result.data());
    return result;
}

[[nodiscard]] PURE_FUNCTION auto Vec3::to_string() const -> std::string
{
    auto internal_data = data();
    return std::format("({}, {}, {})", internal_data[0], internal_data[1], internal_data[2]);
}

[[nodiscard]] PURE_FUNCTION auto operator+(const Vec3& vec1,
                                           const Vec3& vec2) -> Vec3
{
    return vec1.get_vec() + vec2.get_vec();
}

[[nodiscard]] PURE_FUNCTION auto operator-(const Vec3& vec1,
                                           const Vec3& vec2) -> Vec3
{
    return vec1.get_vec() - vec2.get_vec();
}

[[nodiscard]] PURE_FUNCTION auto operator*(const Vec3& vec1,
                                           const Vec3& vec2) -> Vec3
{
    return vec1.get_vec() * vec2.get_vec();
}

[[nodiscard]] PURE_FUNCTION auto operator/(const Vec3& vec1,
                                           const Vec3& vec2) -> Vec3
{
    return vec1.get_vec() / vec2.get_vec();
}

[[nodiscard]] PURE_FUNCTION auto operator*(const Vec3& vec1,
                                           const double& value) -> Vec3
{
    return vec1.get_vec() * value;
}

[[nodiscard]] PURE_FUNCTION auto operator*(const double& value,
                                           const Vec3& vec1) -> Vec3
{
    return vec1.get_vec() * value;
}

[[nodiscard]] PURE_FUNCTION auto operator/(const Vec3& vec1,
                                           const double& value) -> Vec3
{
    return vec1.get_vec() / value;
}

[[nodiscard]] PURE_FUNCTION auto dot(const Vec3& vec1, const Vec3& vec2)
    -> double
{
    return vcl::horizontal_add((vec1 * vec2).get_vec());
}

[[nodiscard]] PURE_FUNCTION auto unit_vector(const Vec3& vec) -> Vec3
{
    return vec * inv_sqrt(vec.squared_length());
}

[[nodiscard]] PURE_FUNCTION auto cross(const Vec3& vec1, const Vec3& vec2)
    -> Vec3
{
    // return Vec3(v1.y() * v2.z() - v1.z() * v2.y(),
    //         v1.z() * v2.x() - v1.x() * v2.z(),
    //         v1.x() * v2.y() - v1.y() * v2.x());

    auto temp_vec1 = vcl::permute4<1, 2, 0, -1>(vec1.get_vec());
    auto temp_vec2 = vcl::permute4<2, 0, 1, -1>(vec2.get_vec());
    auto temp_vec3 = vcl::permute4<2, 0, 1, -1>(vec1.get_vec());
    auto temp_vec4 = vcl::permute4<1, 2, 0, -1>(vec2.get_vec());
    return temp_vec1 * temp_vec2 - temp_vec3 * temp_vec4;
}

[[nodiscard]] PURE_FUNCTION auto
determinant(const Vec3& vec1, const Vec3& vec2, const Vec3& vec3) -> double
{
    //     return (a.x() * (b.y() * c.z() - b.z() * c.y()) -
    //             a.y() * (b.x() * c.z() - b.z() * c.x()) +
    //             a.z() * (b.x() * c.y() - b.y() * c.x()));

    auto temp_vec1 = vcl::permute4<1, 0, 0, -1>(vec2.get_vec());
    auto temp_vec2 = vcl::permute4<2, 2, 1, -1>(vec3.get_vec());
    auto temp_vec3 = vcl::permute4<2, 2, 1, -1>(vec2.get_vec());
    auto temp_vec4 = vcl::permute4<1, 0, 0, -1>(vec3.get_vec());
    vcl::Vec4d sign_vec = {1, -1, 1, 0};
    return vcl::horizontal_add(
        sign_vec * vec1.get_vec() *
        (temp_vec1 * temp_vec2 - temp_vec3 * temp_vec4));
}

[[nodiscard]] PURE_FUNCTION auto cramer(const Vec3& vec1, const Vec3& vec2,
                                        const Vec3& vec3,
                                        const Vec3& result) -> Vec3
{
    //     double deter = determinant(a, b, c);
    //     double deter_1 = determinant(y, b, c);
    //     double deter_2 = determinant(a, y, c);
    //     double deter_3 = determinant(a, b, y);
    //     return Vec3(deter_1, deter_2, deter_3) / deter;

    auto deter = determinant(vec1, vec2, vec3);
    auto deter_1 = determinant(result, vec2, vec3);
    auto deter_2 = determinant(vec1, result, vec3);
    auto deter_3 = determinant(vec1, vec2, result);
    return Vec3(deter_1, deter_2, deter_3) / deter;
}
} // namespace solar
