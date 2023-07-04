#pragma once

#include <boost/describe.hpp>

#include <analytical_model/Constants.h>
#include <utils/Para.h>


#include <memory>

namespace solar
{
    class ModelPara;

    class ConvolutionPara : public Para
    {
        public:
            ConvolutionPara() = default;

            void setPara(const std::string& property_type, const QVariant& value) override;
            [[nodiscard]] auto getPara(const std::string& property_type) -> QVariant override;
            void testPrint() const override;
#include <utils/class_name.inc>

        private:
            ConvolutionModelType model_type_;
            std::shared_ptr<ModelPara> model_para_;

            BOOST_DESCRIBE_CLASS(ConvolutionPara, (Para), (), (),
                                 (model_type_, model_para_))
    };
} // namespace solar
