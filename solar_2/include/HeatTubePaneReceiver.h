
#ifndef HEATTUBEPANERECEIVER_H
#define HEATTUBEPANERECEIVER_H


#include <QVariant>

namespace solar
{

class HeatTubePaneReceiver
{
public:
    HeatTubePaneReceiver();

    void setPara(const int property_type, const QVariant& value);
    auto getPara(const int property_type) const -> QVariant ;
    void testPrint() const;

private:
    int pane_cnt_;  // 面板个数
    int tube_cnt_per_pane_;  //每个面板上的吸热管的个数
    double tube_length_;    //吸热管长度
    double tube_diameter_;    //吸热管的直径
    double interval_between_tubes_;     //吸热管之间的间隔
    double interval_between_panes_;     //面板之间的间隔？？？【这里不确定】
};

}

#endif // HEATTUBEPANERECEIVER_H
