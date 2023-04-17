
#ifndef SUNPOSITION_H
#define SUNPOSITION_H

/*
这里采用Para.h中同样的方法，采用unordered_map来记录所有的属性
但是，是否应该这样写？还是要把这些属性全部定义为类的成员变量，然后给美俄个变量写set和get函数呢
*/


#include <unordered_map>
#include <variant>
#include <any>

namespace solar{

    class SunPosition
    {
    public:
        SunPosition(
            double _azimuth=0,double _elevation=90,double _irradiance=1000,bool _trackable=true)
        {
            this->params = {
                {"azimuth", _azimuth},          //方位角---double
                {"elevation", _elevation},      //高度角---double
                {"irradiance", _irradiance},    //辐射强度---double
                {"trackable", _trackable}       //是否可追踪---bool
                                                };
        }
        void setPara(std::string name, std::any value){
            params[name] = value;
        }
        auto getPara(std::string name)const ->std::any
        {
            return params.at(name);
        }


    private:
        std::unordered_map<std::string, std::any> params;
        //        double azimuth;     //方位角
        //        double elevation;   //高度角
        //        double irradiance;  //辐射强度
        //        bool trackable;     //是否可追踪
};


} // namespace solar


#endif // SUNPOSITION_H
