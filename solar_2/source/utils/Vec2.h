
#ifndef VEC2_H
#define VEC2_H

#include "utils/Utils.h"
#include <QMetaType>

namespace solar
{

    class Vec2
    {
        public:
            Vec2() = default;
            Vec2(double x, double y) : e{x, y} {}

            [[nodiscard]] constexpr auto x() const -> double { return e[0]; }
            [[nodiscard]] constexpr auto y() const -> double { return e[1]; }
            void constexpr setX(double x) { e[0] = x; }
            void constexpr setY(double y) { e[1] = y; }

            auto operator[](int index) -> double& { return e[index]; }

            [[nodiscard]] auto toString() const -> std::string;
            static auto fromString(const std::string& input) -> Vec2;

        private:
            double e[2];
    };

} // namespace solar
Q_DECLARE_METATYPE(solar::Vec2)

#endif // VEC2_H
