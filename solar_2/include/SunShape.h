
#ifndef SUNSHAPE_H
#define SUNSHAPE_H




#include "config.h"

namespace solar
{
    enum SunShapeType
    {
        PILLBOX,
        BUIE,
        GAUSSIAN
    };

    class SunShape
    {
    public:
        virtual ~SunShape() = default;

        virtual void testPrint() const = 0;
        virtual void setPara(double para) = 0;
        [[nodiscard]] virtual auto getPara() const -> double = 0;
        [[nodiscard]] virtual auto getType() const -> SunShapeType =0;
    protected:
        SunShape() = default;
    };

    class GaussianSunShape : public SunShape
    {
    public:
        //GaussionSunShape() = default;
        GaussianSunShape(double para=0.00251) : sigma(para) {}

        void setPara(double para) override;
        [[nodiscard]] PURE_FUNCTION auto getPara() const -> double override;
        [[nodiscard]] PURE_FUNCTION auto getType() const -> SunShapeType override ;
        void testPrint() const override;

    private:
        SunShapeType type = GAUSSIAN;
        double sigma{};
    };

    class PillboxSunShape : public SunShape
    {
    public:
        //PillboxSunShape() = default;
        PillboxSunShape(double para = 0.00465) : theta_max(para) {}

        void setPara(double para) override;
        [[nodiscard]] PURE_FUNCTION auto getPara() const -> double override;
        [[nodiscard]] PURE_FUNCTION auto getType() const -> SunShapeType override ;
        void testPrint() const override;

    private:
        SunShapeType type = PILLBOX;
        double theta_max{};
    };

    class BuieSunShape : public SunShape
    {
    public:
        //BuieSunShape() = default;
        BuieSunShape(double para = 0.02) : csr(para) {}

        void setPara(double para) override;
        [[nodiscard]] PURE_FUNCTION auto getPara() const -> double override;
        [[nodiscard]] PURE_FUNCTION auto getType() const -> SunShapeType override ;
        void testPrint() const override;

    private:
        SunShapeType type = BUIE;
        double csr{};
    };


} //namespace solar

#endif // SUNSHAPE_H
