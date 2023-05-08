
#include "Grid.h"
#include <QDebug>
#include <format>

namespace solar{
void Grid::setPara(const int property_type, const QVariant& value)
{
    switch(property_type)
    {
    case kGrid:
    {
        grid_ = value.toBool();
        break;
    }
    case kFill:
    {
        fill_ = value.toBool();
        break;
    }
    case kSteps:
    {
        steps_ = value.value<Vec3>();
        break;
    }
    case kDivision:
    {
        divisions_ = value.value<Vec3>();
        break;
    }
    case kMin:
    {
        min_ = value.value<Vec3>();
        break;
    }
    case kMax:
    {
        max_ = value.value<Vec3>();
        break;
    }
    case kFile:
    {
        file_ = value.toString().toStdString();
        break;
    }
    default:{
        throw "ERROR::Grid::setPara()::NO SUCH ENUM PROPERTY_TYPE: "
            +std::to_string(property_type);
    }
    }
}

auto Grid::getPara(const int property_type) const -> QVariant
{
    QVariant ret;
    switch(property_type)
    {
    case kGrid:
    {
        ret = grid_;
        break;
    }
    case kFill:
    {
        ret = fill_;
        break;
    }
    case kSteps:
    {
        ret = QVariant::fromValue(steps_);
        break;
    }
    case kDivision:
    {
        ret = QVariant::fromValue(divisions_);
        break;
    }
    case kMin:
    {
        ret = QVariant::fromValue(min_);
        break;
    }
    case kMax:
    {
        ret = QVariant::fromValue(max_);
        break;
    }
    case kFile:
    {
        ret = QString::fromStdString(file_);
        break;
    }
    default:{
        throw "ERROR::Grid::getPara()::NO SUCH ENUM PROPERTY_TYPE: "
            +std::to_string(property_type);
    }
    }
    return ret;
}

void Grid::testPrint() const
{
    qDebug() << std::format("\tGrid::grid={},fill={},steps=({},{},{}),divisions=({},{},{}),file={}",
                            "\n \t\t min=({},{},{}),max=({},{},{}),file={}",
                            grid_, fill_, steps_.x(),steps_.y(),steps_.z(), divisions_.x(), divisions_.y(), divisions_.z(),
                            min_.x(),min_.y(),min_.z(), max_.x(),max_.y(),max_.z(), file_    );
}

}

