#ifndef HELIOSTAT_H
#define HELIOSTAT_H

#include "topology/physical/MechanicalPara.h"
#include "utils/Para.h"
#include "utils/Utils.h"
#include <utils/Vec3.h>

#include <boost/describe.hpp>

#include <cstdlib>

namespace solar
{
    class Material;
    class Geometry;

    class Heliostat : public Para
    {
        public:
            virtual ~Heliostat() = default;
            Heliostat();

            void setPara(const std::string& property_type, const QVariant& value) override;
            [[nodiscard]] auto getPara(const std::string& property_type) -> QVariant override;
            void testPrint() const override;
#include <utils/class_name.inc>
            static int heliostat_cnt_;

        private:
            std::uint64_t id_; // 当前镜子的id，id无法更改
            std::shared_ptr<Material> material_;
            std::shared_ptr<Geometry> geometry_;

            // ！！！！应该还有很多其他要补充的参数
            double thickness_; // 厚度
            bool has_brace_;   // 是否有支架

            // 力学参数
            std::shared_ptr<MechanicalPara> mechanical_para_;

            // ！！！！目标点----还没加，记得加上
            Vec3 target_;
            BOOST_DESCRIBE_CLASS(Heliostat, (Para), (), (),
                                 (id_, material_, geometry_, thickness_, has_brace_,
                                  mechanical_para_))
    };

} // namespace solar

#endif
