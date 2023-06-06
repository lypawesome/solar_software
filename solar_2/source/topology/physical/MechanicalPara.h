#ifndef MECHANICALPARA_H
#define MECHANICALPARA_H

/**
 * 力学参数，用于定日镜的有限元分析
 * ！！！！还有很多参数没有设置
*/

#include <QVariant>

#include <boost/describe.hpp>

namespace solar{

    class MechanicalPara
    {
    public:
        MechanicalPara(){}

        void setPara(const std::string& property_type, const QVariant& value);
        auto getPara(const std::string& property_type) -> QVariant ;
#include <utils/class_name.inc>

    private:
        double density_;    //密度
        double elastic_modulus_;    //弹性模量

        BOOST_DESCRIBE_CLASS(MechanicalPara, (), (), (), (density_, elastic_modulus_))
    };
}


#endif