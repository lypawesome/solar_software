#include "world/sun/sunshape/SunShape.h"

namespace solar
{
    class BuieSunShape : public SunShape
    {
    public:
        //BuieSunShape() = default;
        BuieSunShape(double csr = 0.02) : csr_(csr), type_(kSunShapeBuie) {}

        void setPara(double para) override;
        [[nodiscard]] PURE_FUNCTION auto getPara() const -> double override;
        [[nodiscard]] PURE_FUNCTION auto getType() const -> SunShapeType override ;
        void testPrint() const override;

    private:
        SunShapeType type_ ;
        double csr_{};
    };
}