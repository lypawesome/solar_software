
#ifndef MULTIPANELCOMPRISEDOFHEATTUBE_H
#define MULTIPANELCOMPRISEDOFHEATTUBE_H

/**
 * 目前只有几何参数，没有热力学参数
 * 热力学参数可以单独写成一个类，然后这里持有一个指向那个类的指针

*/

#include "topology/geometry/Geometry.h"

#include <QVariant>

#include <boost/describe.hpp>

namespace solar
{
    class MultiPanelComprisedOfHeatTube : public Geometry
    {
        public:
            MultiPanelComprisedOfHeatTube() = default;

            void setPara(const std::string& property_type, const QVariant& value) override;
            auto getPara(const std::string& property_type) -> QVariant override;
            [[nodiscard]] auto getType() const -> GeometryType override { return type_; }
            void testPrint() const;
#include <utils/class_name.inc>

        private:
            int panel_cnt_;                  // 面板个数
            int tube_cnt_per_panel_;         // 每个面板上的吸热管的个数
            double tube_length_;             // 吸热管长度
            double tube_diameter_;           // 吸热管的直径
            double interval_between_tubes_;  // 吸热管之间的间隔
            double interval_between_panels_; // 面板之间的间隔？？？【这里不确定】

            GeometryType type_ = kGeometryMultiPanelComprisedOfHeatTube;

            BOOST_DESCRIBE_CLASS(MultiPanelComprisedOfHeatTube, (Geometry), (), (),
                                 (panel_cnt_, tube_cnt_per_panel_, tube_length_, tube_diameter_,
                                  interval_between_tubes_, interval_between_panels_))
    };

} // namespace solar

#endif // HEATTUBEPANERECEIVER_H
