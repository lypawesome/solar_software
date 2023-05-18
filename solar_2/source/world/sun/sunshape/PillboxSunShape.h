#include "world/sun/sunshape/SunShape.h"

namespace solar
{
    class PillboxSunShape : public SunShape
    {
        public:
            // PillboxSunShape() = default;
            explicit PillboxSunShape(double theta_max = 0.00465) : theta_max_(theta_max) {}

            void setPara(double para) override;
            [[nodiscard]] PURE_FUNCTION auto getPara() const -> double override;
            [[nodiscard]] PURE_FUNCTION auto getType() const -> SunShapeType override;
            void testPrint() const override;

        private:
            SunShapeType type_ = kSunShapePillbox;
            double theta_max_{};
    };

} // namespace solar