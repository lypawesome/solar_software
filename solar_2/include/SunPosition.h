
#ifndef SUNPOSITION_H
#define SUNPOSITION_H

/*

*/

#include <QVariant>

#include <variant>
#include <any>
#include <QDebug>

#include "Utils.h"

namespace solar{

    class SunPosition
    {
    public:
        SunPosition( double azimuth=0,double elevation=90,double irradiance=1000,bool trackable=true)
            :azimuth_(azimuth), elevation_(elevation), irradiance_(irradiance), trackable_(trackable)
        {  }


        void setPara(const int property_type, const QVariant& value) ;
        auto getPara(const int property_type) const -> QVariant ;
        void testPrint() const ;


    private:
                double azimuth_;     //方位角
                double elevation_;   //高度角
                double irradiance_;  //辐射强度
                bool trackable_;     //是否可追踪
};


} // namespace solar


#endif // SUNPOSITION_H
