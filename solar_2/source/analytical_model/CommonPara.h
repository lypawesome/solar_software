#pragma once

#include <boost/describe.hpp>

#include <utils/Para.h>

#include <cstdlib>

namespace solar
{
    class CommonPara : public Para
    {
        public:
            CommonPara() = default;
            void setPara(const std::string& property_type, const QVariant& value) override;
            [[nodiscard]] auto getPara(const std::string& property_type) -> QVariant override;
            void testPrint() const override;
#include <utils/class_name.inc>

        private:
            std::uint32_t num_gpu_threads_ = 512; // GPU线程数
            BOOST_DESCRIBE_CLASS(CommonPara, (Para), (), (), (num_gpu_threads_))
    };
} // namespace solar
