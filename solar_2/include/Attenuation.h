
#ifndef ATTENUATION_H
#define ATTENUATION_H


namespace solar{

    enum AttenuationType
    {
        VACUUM,         //无大气衰减
        EXPONENTIAL,    //指数模型——Sengupta and Wagner大气衰减模型
        CUSTOM          // 常用的经验模型--师姐文章中的
    };

    class Attenuation
    {
        public:
            virtual auto getValue(double d)const ->double =0;  //返回一个η值，这个值要与最后算出的结果相乘
            virtual auto getType( )const -> AttenuationType =0;
            Attenuation() = default;
    };

    //无大气衰减，直接返回1
    class VacuumAttenuation : public Attenuation
    {
        public:
            VacuumAttenuation() : type(VACUUM) {}

            auto getValue(double d)const ->double override  ;
            auto getType()const -> AttenuationType override { return type; }

        private:
            AttenuationType type;
    };

    //指数模型，要设置一个参数
    class ExponentialAttenuation : public Attenuation
    {
        public:
            ExponentialAttenuation(double _beta=0.11) : beta(_beta), type(EXPONENTIAL) {}

            void setPara(double _beta)  { beta = _beta; }
            auto getPara()const -> double   { return beta; }
            auto getValue(double d)const ->double override;
            auto getType()const -> AttenuationType override { return type; }

        private:
            double beta;
            AttenuationType type;
    };

    //常用的经验模型，师姐文章中的
    class CustomAttenuation : public Attenuation
    {
        public:
            CustomAttenuation() : type(CUSTOM) {}

            auto getValue(double d)const ->double override;
            auto getType()const -> AttenuationType override { return type; }

        private:
            AttenuationType type;
    };
}



#endif // ATTENUATION_H
