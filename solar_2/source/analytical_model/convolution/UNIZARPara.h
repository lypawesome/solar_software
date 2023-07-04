#pragma once

#include <boost/describe.hpp>

#include <analytical_model/ModelPara.h>
#include <utils/HasValue.h>

namespace solar
{
    class UNIZARPara : public ModelPara
    {
        public:
            UNIZARPara() = default;
            void setPara(const std::string& property_type, const std::any& value) override;
            [[nodiscard]] auto getPara(const std::string& property_type) -> std::any override;
#include <utils/class_name.inc>
        private:
            // empty for now
            // 看起来UNIZAR仅使用场景参数
            BOOST_DESCRIBE_CLASS(UNIZARPara, (ModelPara), (), (), ())
    };
} // namespace solar
