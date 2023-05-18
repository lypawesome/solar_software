#include "world/sun/sunshape/SunShape.h"

namespace solar
{
    class GaussianSunShape : public SunShape
    {
    public:
        //GaussionSunShape() = default;
        explicit GaussianSunShape(double sigma=0.00251) : sigma_(sigma) {}

        void setPara(double para) override;
        [[nodiscard]] PURE_FUNCTION auto getPara() const -> double override;
        [[nodiscard]] PURE_FUNCTION auto getType() const -> SunShapeType override ;
        void testPrint() const override;

    private:
        SunShapeType type_ = kSunShapeGaussian;
        double sigma_{};
    };
}