#include "world/sun/sunshape/SunShape.h"

namespace solar
{
    class PillboxSunShape : public SunShape
    {
    public:
        //PillboxSunShape() = default;
        PillboxSunShape(double theta_max = 0.00465) : theta_max_(theta_max), type_(kSunShapePillbox) {}

        void setPara(double para) override;
        [[nodiscard]] PURE_FUNCTION auto getPara() const -> double override;
        [[nodiscard]] PURE_FUNCTION auto getType() const -> SunShapeType override ;
        void testPrint() const override;

    private:
        SunShapeType type_;
        double theta_max_{};
    };

}