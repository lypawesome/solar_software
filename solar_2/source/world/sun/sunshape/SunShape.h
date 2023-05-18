
#ifndef SUNSHAPE_H
#define SUNSHAPE_H

#include "utils/config.h"

namespace solar
{
    enum SunShapeType
    {
        kSunShapePillbox,
        kSunShapeBuie,
        kSunShapeGaussian
    };

    class SunShape
    {
        public:
            virtual ~SunShape() = default;

            virtual void testPrint() const = 0;
            virtual void setPara(double para) = 0;
            [[nodiscard]] virtual auto getPara() const -> double = 0;
            [[nodiscard]] virtual auto getType() const -> SunShapeType = 0;

        protected:
            SunShape() = default;
    };

} // namespace solar

#endif // SUNSHAPE_H
