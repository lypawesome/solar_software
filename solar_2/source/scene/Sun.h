#ifndef SUN_H
#define SUN_H

#include "utils/Para.h"
#include "world/sun/sun_position/SunPosition.h"
#include "world/sun/sunshape/SunShape.h"
#include "world/sun/sunshape/PillboxSunShape.h"
#include "world/sun/sunshape/BuieSunShape.h"
#include "world/sun/sunshape/GaussianSunShape.h"
#include "utils/Utils.h"


namespace solar{
    class Sun : public Para
    {
    public:
        Sun()
        {
            sunshape_ = std::make_shared<PillboxSunShape>();       //先放高斯
            sun_position_ = std::make_shared<SunPosition>();
        }


        void setPara(const int property_type, const QVariant& value) override;
        [[nodiscard]] auto getPara(const int property_type) const
            -> QVariant override;
        void testPrint() const override;

    private:
        std::shared_ptr<SunShape> sunshape_;
        std::shared_ptr<SunPosition> sun_position_;
    };

}

#endif