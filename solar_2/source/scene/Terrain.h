#ifndef TERRAIN_H
#define TERRAIN_H

#include "boost/describe/class.hpp"
#include "utils/Para.h"
#include "utils/Utils.h"
#include "utils/Vec3.h"

#include <boost/describe.hpp>

namespace solar
{

    class Terrain : public Para
    {
        public:
            ~Terrain() override = default;
            Terrain(std::string dem_file = "null") : dem_file_(dem_file) {};

            void setPara(const std::string& property_type, const QVariant& value) override;
            [[nodiscard]] auto getPara(const std::string& property_type) -> QVariant override;
            void testPrint() const override;
#include <utils/class_name.inc>

        private:
            void readFile(); // 从file中导入heights

            std::string dem_file_;
            std::vector<std::vector<Vec3>> heights_; // 从file中导入的，每个格子的高度-----不可通过UI更改
            BOOST_DESCRIBE_CLASS(Terrain, (Para), (), (), (dem_file_))
    };
} // namespace solar

#endif