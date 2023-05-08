
#ifndef ATTENUATION_H
#define ATTENUATION_H

#include <QDebug>

namespace solar{

    enum AttenuationType
    {
        kAttenuationVacuum,         //无大气衰减
        kAttenuationExponential,    //指数模型——Sengupta and Wagner大气衰减模型
        kAttenuationCustom          // 常用的经验模型--师姐文章中的
    };

    class Attenuation
    {
        public:
            virtual auto getType( )const -> AttenuationType =0;
            virtual void setPara(double para) {}
            virtual  auto getPara()const -> double {return 0.0; }
            virtual void testPrint() const;
            Attenuation() = default;
    };

    //无大气衰减
    class VacuumAttenuation : public Attenuation
    {
        public:
            VacuumAttenuation() : type_(kAttenuationVacuum) {}

            auto getType()const -> AttenuationType override { return type_; }
            void testPrint() const override
            {qDebug() << "\t VacuumAttenuation"; }
        private:
            AttenuationType type_;
    };

    //指数模型，要设置一个参数
    class ExponentialAttenuation : public Attenuation
    {
        public:
            ExponentialAttenuation(double beta=0.11) : beta_(beta), type_(kAttenuationExponential) {}

            void setPara(double beta) override { beta_ = beta; }
            auto getPara()const -> double override  { return beta_; }
            auto getType()const -> AttenuationType override { return type_; }
            void testPrint() const override
            {qDebug() << "\t ExponentialAttenuation: beta="<<beta_ ; }
        private:
            double beta_;
            AttenuationType type_;
    };

    //常用的经验模型，师姐文章中的
    class CustomAttenuation : public Attenuation
    {
        public:
            CustomAttenuation() : type_(kAttenuationCustom) {}

            auto getType()const -> AttenuationType override { return type_; }
            void testPrint() const override
            {qDebug() << "\t CustomAttenuation"; }
        private:
            AttenuationType type_;
    };
}



#endif // ATTENUATION_H
