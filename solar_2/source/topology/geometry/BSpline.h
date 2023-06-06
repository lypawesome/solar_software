#ifndef BSPLINE_H
#define BSPLINE_H


#include "topology/geometry/Geometry.h"
#include <utils/Vec3.h>

#include <vector>

#include <boost/describe.hpp>


/**
 * 定义好BSpline的文件，所有相关参数直接从文件中读取
*/
namespace solar
{
    /*
     * B样条曲面--无理B样条
     * 第一种方法：进行插值计算，计算得出B样条曲面
     *      给出插值点，两个方向上插值点的个数，两个方向上的阶数，以及节点向量生成方法、参数生成方法
     *      插值得出控制顶点，即得到了B样条曲面的表达式
     * 第二种方法：插值过程另外计算，直接给出B样条曲面的表达式
     *      给出：控制顶点、两个方向上控制顶点的个数、两个方向上的节点向量、两个方向上的阶数
     *      每次给定(u,v)值，计算出两个方向上的基函数，通过B样条曲面的公式计算得到一个值w
     *      取若干个这样的(u,v)点，则（u，v，w）组成的面就是B样条曲面
     * 选择第二种方法
     * 【参考-应用几何造型GM09章节ppt、教材-非均匀有理B样条】
     * 问题：是否需要使用NURBS进行表示？？？
     */
    class BSpline : public Geometry
    {
        public:
            BSpline() {}

            void setPara(const std::string& property_type, const QVariant& value) override;
            auto getPara(const std::string& property_type) -> QVariant override;
            [[nodiscard]] auto getType() const -> GeometryType override { return type_; }
            void readFile(); // 读取文件
#include <utils/class_name.inc>

        private:
            std::string file_; // 文件，从该文件中读入B样条曲面的各种信息

            GeometryType type_ = kGeometryBSpline;

            int cnt_u_, cnt_v_;     // 两个方向的控制点个数分别为：cnt_u + 1,  cnt_v+1
            int order_u_, order_v_; // 两个方向的阶数分别为：order_u、order_v
            std::vector<std::vector<Vec3>> control_points_; // 控制顶点
            std::vector<double> knot_u_, knot_v_;           // 两个方向的节点向量
            BOOST_DESCRIBE_CLASS(BSpline, (Geometry), (), (), (file_))
    };

} // namespace solar

#endif