#pragma once

#include <any>
#include <string>

namespace solar
{
    // 模型参数的基类
    // 不参与UI交互
    class ModelPara
    {
        public:
            virtual void setPara(const std::string& property_type, const std::any& value) = 0;
            [[nodiscard]] virtual auto getPara(const std::string& property_type) -> std::any = 0;

        protected:
            ModelPara() = default;
            ~ModelPara() = default;
    };
} // namespace solar
