#include "world/air/Attenuation.h"

namespace solar
{

    // 无大气衰减
    class VacuumAttenuation : public Attenuation
    {
        public:
            VacuumAttenuation() : type_(kAttenuationVacuum) {}

            [[nodiscard]] auto getType() const -> AttenuationType override { return type_; }
            void testPrint() const override { qDebug() << "\t VacuumAttenuation"; }

        private:
            AttenuationType type_;
    };
} // namespace solar