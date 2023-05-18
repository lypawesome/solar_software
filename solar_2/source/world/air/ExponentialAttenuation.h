#include "world/air/Attenuation.h"

namespace solar
{
    // 指数模型，要设置一个参数
    class ExponentialAttenuation : public Attenuation
    {
        public:
            ExponentialAttenuation(double beta = 0.11) : beta_(beta), type_(kAttenuationExponential)
            {
            }

            void setPara(double beta) override { beta_ = beta; }
            [[nodiscard]] auto getPara() const -> double override { return beta_; }
            [[nodiscard]] auto getType() const -> AttenuationType override { return type_; }
            void testPrint() const override
            {
                qDebug() << "\t ExponentialAttenuation: beta=" << beta_;
            }

        private:
            double beta_;
            AttenuationType type_;
    };
} // namespace solar