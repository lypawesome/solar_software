
#ifndef HEATTUBEPLANE_H
#define HEATTUBEPLANE_H

/*
 * 表示接收器上由吸热管组成的一个面板（接收器由若干个面板围成）
*/

namespace solar
{


class HeatTubePlane
{
public:
    HeatTubePlane();

private:
    int tube_cnt_;      //一个面板上有几根吸热管
};

} // namespace solar

#endif // HEATTUBEPLANE_H
