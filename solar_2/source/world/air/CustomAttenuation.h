#include "world/air/Attenuation.h"

namespace solar
{
    // 常用的经验模型，师姐文章中的
    class CustomAttenuation : public Attenuation
    {
        public:
            CustomAttenuation() = default;

            [[nodiscard]] auto getType() const -> AttenuationType override { return type_; }
            void testPrint() const override { qDebug() << "\t CustomAttenuation"; }

        private:
            AttenuationType type_ = kAttenuationCustom;
    };
} // namespace solar