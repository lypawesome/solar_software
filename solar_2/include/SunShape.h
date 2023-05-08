
#ifndef SUNSHAPE_H
#define SUNSHAPE_H




#include "config.h"

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
        [[nodiscard]] virtual auto getType() const -> SunShapeType =0;
    protected:
        SunShape() = default;
    };

    class GaussianSunShape : public SunShape
    {
    public:
        //GaussionSunShape() = default;
        GaussianSunShape(double sigma=0.00251) : sigma_(sigma), type_(kSunShapeGaussian) {}

        void setPara(double para) override;
        [[nodiscard]] PURE_FUNCTION auto getPara() const -> double override;
        [[nodiscard]] PURE_FUNCTION auto getType() const -> SunShapeType override ;
        void testPrint() const override;

    private:
        SunShapeType type_;
        double sigma_{};
    };

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


} //namespace solar

#endif // SUNSHAPE_H
