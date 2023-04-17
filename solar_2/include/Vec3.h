#pragma once

#include <QMetaType>

#include <array>
#include <string>

#include "config.h"

#include <vectorclass.h>

namespace solar
{
class Vec3
{
public:
    Vec3() = default;
    Vec3(double input_x, double input_y, double input_z)
        : internal_vector(input_x, input_y, input_z, 0)
    {
    }
    Vec3(const vcl::Vec4d& vec) : internal_vector(vec) {}

    [[nodiscard]] PURE_FUNCTION auto x() const -> double;
    [[nodiscard]] PURE_FUNCTION auto y() const -> double;
    [[nodiscard]] PURE_FUNCTION auto z() const -> double;

    void set_x(double input_x);
    void set_y(double input_y);
    void set_z(double input_z);

    // 运算符重载
    // [[nodiscard]] PURE_FUNCTION auto operator+() const -> Vec3;
    [[nodiscard]] PURE_FUNCTION auto operator-() const -> Vec3;
    // [[nodiscard]] PURE_FUNCTION auto operator[](int index) const
    //     -> double;
    //  double& operator[](int i);

    auto operator+=(const Vec3& vec) -> Vec3;
    auto operator-=(const Vec3& vec) -> Vec3;
    auto operator*=(const Vec3& vec) -> Vec3;
    auto operator/=(const Vec3& vec) -> Vec3;
    auto operator*=(const double& value) -> Vec3;
    auto operator/=(const double& value) -> Vec3;
    //  Vec3& operator=(const Vec3& v);
    // //拷贝赋值函数----最好不要显式定义该函数，因为trival的函数xiaolv更高

    [[nodiscard]] PURE_FUNCTION auto squared_length() const -> double;
    [[nodiscard]] PURE_FUNCTION auto length() const -> double;
    void make_unit_vector();
    [[nodiscard]] PURE_FUNCTION auto get_vec() const -> vcl::Vec4d;
    [[nodiscard]] PURE_FUNCTION auto data() const
        -> std::array<double, 3>;
    [[nodiscard]] PURE_FUNCTION auto to_string() const -> std::string;

private:
    vcl::Vec4d internal_vector{};
};

[[nodiscard]] PURE_FUNCTION auto operator+(const Vec3& vec1,
                                           const Vec3& vec2) -> Vec3;
[[nodiscard]] PURE_FUNCTION auto operator-(const Vec3& vec1,
                                           const Vec3& vec2) -> Vec3;
[[nodiscard]] PURE_FUNCTION auto operator*(const Vec3& vec1,
                                           const Vec3& vec2) -> Vec3;
[[nodiscard]] PURE_FUNCTION auto operator/(const Vec3& vec1,
                                           const Vec3& vec2) -> Vec3;
[[nodiscard]] PURE_FUNCTION auto operator*(const Vec3& vec1,
                                           const double& value) -> Vec3;
[[nodiscard]] PURE_FUNCTION auto operator*(const double& value,
                                           const Vec3& vec1) -> Vec3;
[[nodiscard]] PURE_FUNCTION auto operator/(const Vec3& vec1,
                                           const double& value) -> Vec3;
[[nodiscard]] PURE_FUNCTION auto dot(const Vec3& vec1, const Vec3& vec2)
    -> double;
[[nodiscard]] PURE_FUNCTION auto unit_vector(const Vec3& vec) -> Vec3;
[[nodiscard]] PURE_FUNCTION auto cross(const Vec3& vec1, const Vec3& vec2)
    -> Vec3;
/// 矩阵[a, b, c]的行列式
[[nodiscard]] PURE_FUNCTION auto
determinant(const Vec3& vec1, const Vec3& vec2, const Vec3& vec3) -> double;
/// 利用cramer法则求解线性方程组:[a, b, c]·X = Y
[[nodiscard]] PURE_FUNCTION auto cramer(const Vec3& vec1, const Vec3& vec2,
                                        const Vec3& vec3,
                                        const Vec3& result) -> Vec3;

} // namespace solar

// 把Vec3声明为元数据，这样就可以把Vec3存到QVariant中
Q_DECLARE_METATYPE(solar::Vec3)
