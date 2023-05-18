
#include "utils/Grid.h"
#include "utils/ParaUtils.h"
#include <utils/Format.h>

#include <QDebug>
// #include <format>

namespace solar
{
    void Grid::setPara(const std::string& property_type, const QVariant& value)
    {
        ::solar::setPara(property_type, value, this);
    }

    auto Grid::getPara(const std::string& property_type) -> QVariant
    {
        return ::solar::getPara(property_type, this);
    }

    void Grid::testPrint() const
    {
        qDebug() << format("\tGrid::grid={},fill={},steps=({},{},{}),divisions=({},{},{}),file={}",
                           "\n \t\t min=({},{},{}),max=({},{},{}),file={}", grid_, fill_,
                           steps_.x(), steps_.y(), steps_.z(), divisions_.x(), divisions_.y(),
                           divisions_.z(), min_.x(), min_.y(), min_.z(), max_.x(), max_.y(),
                           max_.z(), file_);
    }

} // namespace solar
