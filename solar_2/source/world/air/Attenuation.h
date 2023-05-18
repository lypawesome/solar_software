
#ifndef ATTENUATION_H
#define ATTENUATION_H

#include <QDebug>

namespace solar
{

    enum AttenuationType
    {
        kAttenuationVacuum,      // 无大气衰减
        kAttenuationExponential, // 指数模型——Sengupta and Wagner大气衰减模型
        kAttenuationCustom       // 常用的经验模型--师姐文章中的
    };

    class Attenuation
    {
        public:
            [[nodiscard]] virtual auto getType() const -> AttenuationType = 0;
            virtual void setPara(double para) {}
            [[nodiscard]] virtual auto getPara() const -> double { return 0.0; }
            virtual void testPrint() const {}
            Attenuation() = default;
    };

} // namespace solar

#endif // ATTENUATION_H
