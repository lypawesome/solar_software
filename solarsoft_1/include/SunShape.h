#pragma once

#include "config.h"

namespace solar
{
    class SunShape
    {
        public:
            virtual ~SunShape() = default;

            virtual void testPrint() const = 0;
            virtual void setPara(double para) = 0;
            [[nodiscard]] virtual auto getPara() const -> double = 0;

        protected:
            SunShape() = default;
    };

    class GaussionSunShape : public SunShape
    {
        public:
            GaussionSunShape() = default;
            GaussionSunShape(double para) : sigma(para) {}

            void setPara(double para) override;
            [[nodiscard]] PURE_FUNCTION auto getPara() const -> double override;
            void testPrint() const override;

        private:
            double sigma{};
    };

    class PillboxSunShape : public SunShape
    {
        public:
            PillboxSunShape() = default;
            PillboxSunShape(double para) : theta_max(para) {}

            void setPara(double para) override;
            [[nodiscard]] PURE_FUNCTION auto getPara() const -> double override;
            void testPrint() const override;

        private:
            double theta_max{};
    };

    class BuieSunShape : public SunShape
    {
        public:
            BuieSunShape() = default;
            BuieSunShape(double para) : csr(para) {}

            void setPara(double para) override;
            [[nodiscard]] PURE_FUNCTION auto getPara() const -> double override;
            void testPrint() const override;

        private:
            double csr{};
    };

} // namespace solar
