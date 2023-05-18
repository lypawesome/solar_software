
#ifndef HEATTUBEPANERECEIVER_H
#define HEATTUBEPANERECEIVER_H

#include <QVariant>

#include <boost/describe.hpp>

namespace solar
{
    class HeatTubePaneReceiver
    {
        public:
            HeatTubePaneReceiver() = default;

            void setPara(const std::string& property_type, const QVariant& value);
            auto getPara(const std::string& property_type) -> QVariant;
            void testPrint() const;
#include <utils/class_name.inc>

        private:
            int pane_cnt_;                  // 面板个数
            int tube_cnt_per_pane_;         // 每个面板上的吸热管的个数
            double tube_length_;            // 吸热管长度
            double tube_diameter_;          // 吸热管的直径
            double interval_between_tubes_; // 吸热管之间的间隔
            double interval_between_panes_; // 面板之间的间隔？？？【这里不确定】
            BOOST_DESCRIBE_CLASS(HeatTubePaneReceiver, (), (), (),
                                 (pane_cnt_, tube_cnt_per_pane_, tube_length_, tube_diameter_,
                                  interval_between_tubes_, interval_between_panes_))
    };

} // namespace solar

#endif // HEATTUBEPANERECEIVER_H
