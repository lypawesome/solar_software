#ifndef TERRAIN_H
#define TERRAIN_H

#include "boost/describe/class.hpp"
#include "utils/Para.h"
#include "utils/Utils.h"

#include <boost/describe.hpp>

namespace solar
{
    class Grid;

    class Terrain : public Para
    {
        public:
            ~Terrain() override = default;
            Terrain();

            void setPara(const std::string& property_type, const QVariant& value) override;
            [[nodiscard]] auto getPara(const std::string& property_type) -> QVariant override;
            void testPrint() const override;
#include <utils/class_name.inc>

        private:
            void readFile(); // 从file中导入heights

            std::shared_ptr<Grid> grid_;
            std::vector<std::vector<double>> heights_; // 从file中导入的，每个格子的高度
            BOOST_DESCRIBE_CLASS(Terrain, (Para), (), (), (grid_, heights_))
    };
} // namespace solar

#endif