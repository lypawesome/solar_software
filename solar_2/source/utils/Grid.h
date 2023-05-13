
#ifndef GRID_H
#define GRID_H

/*
 * 网格，用于需要划分成小格子的参数，如Terrain、Cloud
*/
#include <QVariant>

#include"utils/Vec3.h"
#include"utils/Utils.h"

namespace solar{

class Grid
{
public:
    Grid(bool grid = true, bool fill = true,
         const Vec3& steps = Vec3(1, 1, 1),
         const Vec3& divisions = Vec3(5, 5, 5),
         const Vec3& min = Vec3(-10, -10, 0),
         const Vec3& max = Vec3(10, 10, 0),
         const std::string& file = "")
        : grid_(grid), fill_(fill), steps_(steps), divisions_(divisions),
        min_(min), max_(max), file_(file)
        {};

    void setPara(const int property_type, const QVariant& value);
    auto getPara(const int property_type) const -> QVariant ;
    void testPrint() const;

private:
    bool grid_;  //是否是网格
    bool fill_;
    Vec3 steps_;         //三个方向上一个格子的大小
    Vec3 divisions_;     //三个方向上的格子数目
    Vec3 min_;           //网格看做Box，Box的三个方向上的最小点
    Vec3 max_;           //Box的三个方向上的最大点
    std::string file_;   //文件名，假如要给每个格子传入一个参数，，参数存在这个文件内

};

}   // namespace solar

#endif // GRID_H
