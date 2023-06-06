#ifndef THERMODYNAMICPARA_H
#define THERMODYNAMICPARA_H

/**
 * 热力学参数，用于由吸热管组成的接收器
 * ！！！目前还没搞清楚需要哪些参数，先放着
*/

#include <boost/describe.hpp>
#include <QVariant>

namespace solar{

    class ThermodynamicPara
    {
    public:
        ThermodynamicPara(){}

        void setPara(const std::string& property_type, const QVariant& value);
        auto getPara(const std::string& property_type) -> QVariant ;
#include <utils/class_name.inc>

    private:


        BOOST_DESCRIBE_CLASS(ThermodynamicPara, (), (), (), ())
    };
}


#endif