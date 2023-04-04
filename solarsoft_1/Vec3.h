#ifndef VEC3_H
#define VEC3_H



#include<cmath>
#include<iostream>
#include"QMetaType"



class Vec3
{
public:
    Vec3(){};
    Vec3(double a, double b, double c) :e{ a,b,c } {};

    inline double x() const { return e[0]; }
    inline double y() const { return e[1]; }
    inline double z() const { return e[2]; }

    inline void setx(double x) { e[0] = x; }
    inline void sety(double y) { e[1] = y; }
    inline void setz(double z) { e[2] = z; }

    //运算符重载
    inline const Vec3& operator+() const { return *this; }
    inline Vec3 operator-() const { return Vec3(-e[0], -e[1], -e[2]); }
    inline double operator[](int i) const { return e[i]; }
    inline double& operator[](int i) { return e[i]; }	//表示，可用于左值

    inline Vec3& operator+=(const Vec3& v);
    inline Vec3& operator-=(const Vec3& v);
    inline Vec3& operator*=(const Vec3& v);
    inline Vec3& operator/=(const Vec3& v);
    inline Vec3& operator*=(const double value);
    inline Vec3& operator/=(const double value);
    //inline Vec3& operator=(const Vec3& v);      //拷贝赋值函数----最好不要显式定义该函数，因为trival的函数xiaolv更高

    inline double squared_length() const { return e[0] * e[0] + e[1] * e[1] + e[2] * e[2]; }
    inline double length() const { return sqrt(squared_length()); }
    inline void make_unit_vector() {		//把除法写成乘法，更高效
        double k = 1 / length();
        e[0] *= k, e[1] *= k, e[2] *= k;
    }

private:
    double e[3];
};

/*
把Vec3声明为元数据，这样就可以把Vec3存到QVariant中
*/
Q_DECLARE_METATYPE(Vec3)


//成员函数
inline Vec3& Vec3::operator+=(const Vec3& v) {
    e[0] += v.e[0];
    e[1] += v.e[1];
    e[2] += v.e[2];
    return *this;
}
inline Vec3& Vec3::operator-=(const Vec3& v) {
    e[0] -= v.e[0];
    e[1] -= v.e[1];
    e[2] -= v.e[2];
    return *this;
}
inline Vec3& Vec3::operator*=(const Vec3& v) {
    e[0] *= v.e[0];
    e[1] *= v.e[1];
    e[2] *= v.e[2];
    return *this;
}
inline Vec3& Vec3::operator/=(const Vec3& v) {
    e[0] /= v.e[0];
    e[1] /= v.e[1];
    e[2] /= v.e[2];
    return *this;
}
inline Vec3& Vec3::operator*=(const double value) {
    e[0] *= value;
    e[1] *= value;
    e[2] *= value;
    return *this;
}
inline Vec3& Vec3::operator/=(const double value) {
    e[0] /= value;
    e[1] /= value;
    e[2] /= value;
    return *this;
}
/*
inline Vec3& Vec3::operator=(const Vec3& v) {
    if(this == &v) return *this;

    e[0] = v.x();
    e[1] = v.y();
    e[2] = v.z();

    return *this;
}
*/

inline Vec3 operator+(const Vec3& v1, const Vec3& v2) {
    return Vec3(v1.x() + v2.x(), v1.y() + v2.y(), v1.z() + v2.z());
}
inline Vec3 operator-(const Vec3& v1, const Vec3& v2) {
    return Vec3(v1.x() - v2.x(), v1.y() - v2.y(), v1.z() - v2.z());
}
inline Vec3 operator*(const Vec3& v1, const Vec3& v2) {
    return Vec3(v1.x() * v2.x(), v1.y() * v2.y(), v1.z() * v2.z());
}
inline Vec3 operator/(const Vec3& v1, const Vec3& v2) {
    return Vec3(v1.x() / v2.x(), v1.y() / v2.y(), v1.z() / v2.z());
}
inline Vec3 operator*(const Vec3& v1, const double t) {
    return Vec3(v1.x() *t, v1.y() *t, v1.z() *t);
}
inline Vec3 operator*( const double t, const Vec3& v1) {
    return v1*t;
}
inline Vec3 operator/(const Vec3& v1, const double t) {
    return v1*(1/t);
}


inline double dot(const Vec3& v1, const Vec3& v2) {
    return v1.x()*v2.x() + v1.y()*v2.y() + v1.z()*v2.z();
}
inline Vec3 cross(const Vec3& v1, const Vec3& v2) {
    return Vec3(	v1.y()*v2.z() - v1.z()*v2.y(),
                    v1.z()*v2.x() - v1.x()*v2.z(),
                    v1.x()*v2.y() - v1.y()*v2.x()	);
}
inline Vec3 unit_vector(const Vec3& v) {
    return v / v.length();
}

//计算3*3矩阵的行列式,a,b,c分别为矩阵的三列或者三行
inline double determinant(Vec3 a, Vec3 b, Vec3 c) {
    return (	a.x() * (b.y()*c.z() - b.z()*c.y())
              - a.y() * (b.x()*c.z() - b.z()*c.x())
              + a.z() * (b.x()*c.y() - b.y()*c.x())	);
}

//利用cramer法则求解线性方程组:[a,b,c]·X = Y
inline Vec3 cramer(Vec3 a, Vec3 b, Vec3 c, Vec3 y) {
    double deter = determinant(a, b, c);
    double deter_1 = determinant(y, b, c);
    double deter_2 = determinant(a, y, c);
    double deter_3 = determinant(a, b, y);

    return Vec3(deter_1, deter_2, deter_3) / deter;
}



#endif // VEC3_H
