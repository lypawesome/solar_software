#include <analytical_model/Constants.h>
#include <analytical_model/HeliostatPara.h>
#include <analytical_model/HeliostatWithGlassPara.h>
#include <analytical_model/ModelPara.h>
#include <analytical_model/convolution/ConvolutionPara.h>
#include <analytical_model/convolution/HuangPara.h>
#include <analytical_model/convolution/ICauchyPara.h>
#include <analytical_model/convolution/UNIZARPara.h>
#include <analytical_model/simplified/BHFLCALPara.h>
#include <analytical_model/simplified/HFLCALPara.h>
#include <analytical_model/simplified/IHFLCALPara.h>
#include <analytical_model/simplified/NEGPara.h>
#include <analytical_model/simplified/SimplifiedPara.h>
#include <analytical_model/ui/AnalyticFunctionWindowAdapter.h>
#include <utils/Concepts.h>
#include <utils/Format.h>
#include <utils/ParaUtils.h>
#include <utils/config.h>

#include <QDebug>

#include <cstdint>
#include <exception>

// note: UI上显示字符为空时，无法编辑（也无法添加字符）

using namespace solar;

// Only for test
AnalyticFunctionWindowAdapter::AnalyticFunctionWindowAdapter()
{
    auto heliostat_para_0 = std::make_shared<HeliostatPara>();
    heliostat_para_0->setPara(toMemberName("heliostat_id"), 0);
    heliostat_para_0->setPara(toMemberName("receiver_id"), 0);
    this->heliostat_paras_[0] = heliostat_para_0;
    auto icauchy_para_0 = std::make_shared<ICauchyPara>();
    auto convolution_para_0 = std::make_shared<ConvolutionPara>();
    convolution_para_0->setPara(toMemberName("model_type"),
                                QVariant::fromValue(ConvolutionModelType::kiCauchy));
    // convolution_para_0->setPara(toMemberName("model_para"), QVariant::fromValue(icauchy_para_0));
    auto* ptr = std::any_cast<std::shared_ptr<ModelPara>*>(
        ::solar::getParaPtr(toMemberName("model_para"), convolution_para_0.get()));
    *ptr = icauchy_para_0;
    decltype(this->convolution_models_)::mapped_type icauchy_paras;
    icauchy_paras[0] = convolution_para_0;
    this->convolution_models_[ConvolutionModelType::kiCauchy] = icauchy_paras;
    // qDebug() << "icauchy_paras_0_ptr: " <<
    // this->convolution_models_[ConvolutionModelType::kiCauchy][0]->getPara(toMemberName("model_para")).value<std::shared_ptr<ModelPara>>().get();
}

void AnalyticFunctionWindowAdapter::testConnect() const { qDebug() << "Adapter Connected"; }

auto AnalyticFunctionWindowAdapter::getProjectionType() const -> ProjectionType
{
    return this->projection_type_;
}

void AnalyticFunctionWindowAdapter::setProjectionType(const ProjectionType& type)
{
    this->projection_type_ = type;
}

auto AnalyticFunctionWindowAdapter::getModelType() const -> ModelType { return this->model_type_; }

void AnalyticFunctionWindowAdapter::setModelType(const ModelType& type)
{
    this->model_type_ = type;
}

auto AnalyticFunctionWindowAdapter::getSimplifiedModelType() const -> SimplifiedModelType
{
    return this->simplified_model_type_;
}

void AnalyticFunctionWindowAdapter::setSimplifiedModelType(const SimplifiedModelType& type)
{
    this->simplified_model_type_ = type;
}

auto AnalyticFunctionWindowAdapter::getConvolutionModelType() const -> ConvolutionModelType
{
    return this->convolution_model_type_;
}

void AnalyticFunctionWindowAdapter::setConvolutionModelType(const ConvolutionModelType& type)
{
    this->convolution_model_type_ = type;
}

auto AnalyticFunctionWindowAdapter::getHeliostatType() const -> HeliostatType
{
    return this->heliostat_type_;
}

void AnalyticFunctionWindowAdapter::setHeliostatType(const HeliostatType& type)
{
    this->heliostat_type_ = type;
}

auto AnalyticFunctionWindowAdapter::getCommonPara(const QString& key) -> QString
{
    ASSUME(!key.isEmpty());
    if (::solar::paraHasValue(key.toStdString(), std::addressof(this->common_para_)))
    {
        return QString::fromStdString(
            ::solar::getParaAsString(key.toStdString(), std::addressof(this->common_para_)));
    }
    return " ";
}

void AnalyticFunctionWindowAdapter::setCommonPara(const QString& key, const QString& value)
{
    ASSUME(!key.isEmpty());
    if (value.isEmpty() || value == " ") [[unlikely]]
    {
        return;
    }
    try
    {
        ::solar::setParaFromString(key.toStdString(), value.toStdString(),
                                   std::addressof(this->common_para_));
    }
    catch (const std::string& message)
    {
        qDebug() << QString::fromStdString(::solar::format(
            "[ERROR] An error occurred in \"{}\": \n    {}", PRETTY_FUNCTION_NAME, message));
    }
    catch (const std::exception& e)
    {
        qDebug() << QString::fromStdString(::solar::format(
            "[ERROR] An error occurred in \"{}\": \n    {}", PRETTY_FUNCTION_NAME, e.what()));
    }
}

auto AnalyticFunctionWindowAdapter::getScenePara(const QString& key) -> QString
{
    ASSUME(!key.isEmpty());
    if (::solar::paraHasValue(key.toStdString(), std::addressof(this->scene_para_)))
    {
        return QString::fromStdString(
            ::solar::getParaAsString(key.toStdString(), std::addressof(this->scene_para_)));
    }
    return " ";
}

void AnalyticFunctionWindowAdapter::setScenePara(const QString& key, const QString& value)
{
    ASSUME(!key.isEmpty());
    if (value.isEmpty() || value == " ") [[unlikely]]
    {
        return;
    }
    try
    {
        ::solar::setParaFromString(key.toStdString(), value.toStdString(),
                                   std::addressof(this->scene_para_));
    }
    catch (const std::string& message)
    {
        qDebug() << QString::fromStdString(::solar::format(
            "[ERROR] An error occurred in \"{}\": \n    {}", PRETTY_FUNCTION_NAME, message));
    }
    catch (const std::exception& e)
    {
        qDebug() << QString::fromStdString(::solar::format(
            "[ERROR] An error occurred in \"{}\": \n    {}", PRETTY_FUNCTION_NAME, e.what()));
    }
}

auto AnalyticFunctionWindowAdapter::getSimulationPara(const QString& key) -> QString
{
    ASSUME(!key.isEmpty());
    if (::solar::paraHasValue(key.toStdString(), std::addressof(this->simulation_para_)))
    {
        return QString::fromStdString(
            ::solar::getParaAsString(key.toStdString(), std::addressof(this->simulation_para_)));
    }
    return " ";
}

void AnalyticFunctionWindowAdapter::setSimulationPara(const QString& key, const QString& value)
{
    ASSUME(!key.isEmpty());
    if (value.isEmpty() || value == " ") [[unlikely]]
    {
        return;
    }
    try
    {
        ::solar::setParaFromString(key.toStdString(), value.toStdString(),
                                   std::addressof(this->simulation_para_));
    }
    catch (const std::string& message)
    {
        qDebug() << QString::fromStdString(::solar::format(
            "[ERROR] An error occurred in \"{}\": \n    {}", PRETTY_FUNCTION_NAME, message));
    }
    catch (const std::exception& e)
    {
        qDebug() << QString::fromStdString(::solar::format(
            "[ERROR] An error occurred in \"{}\": \n    {}", PRETTY_FUNCTION_NAME, e.what()));
    }
}

auto AnalyticFunctionWindowAdapter::getNumberOfHeliostats() const -> std::uint64_t
{
    return this->heliostat_paras_.size();
}

auto AnalyticFunctionWindowAdapter::getHeliostatIndices() const -> QVariantList
{
    QVariantList list;
    for (const auto& [key, value] : this->heliostat_paras_)
    {
        list.append(key);
    }
    return list;
}

auto AnalyticFunctionWindowAdapter::getHeliostatPara(std::uint64_t heliostat_index,
                                                     const QString& key) -> QString
{
    ASSUME(!key.isEmpty());
    if (this->heliostat_paras_.contains(heliostat_index)) [[likely]]
    {
        if (::solar::paraHasValue(key.toStdString(),
                                  this->heliostat_paras_.at(heliostat_index).get()))
        {
            return QString::fromStdString(::solar::getParaAsString(
                key.toStdString(), this->heliostat_paras_.at(heliostat_index).get()));
        }
    }
    return " ";
}

void AnalyticFunctionWindowAdapter::setHeliostatPara(std::uint64_t heliostat_index,
                                                     const QString& key, const QString& value)
{
    ASSUME(!key.isEmpty());
    if (value.isEmpty() || value == " ") [[unlikely]]
    {
        return;
    }
    if (this->heliostat_paras_.contains(heliostat_index)) [[likely]]
    {
        try
        {
            ::solar::setParaFromString(key.toStdString(), value.toStdString(),
                                       this->heliostat_paras_.at(heliostat_index).get());
        }
        catch (const std::string& message)
        {
            qDebug() << QString::fromStdString(::solar::format(
                "[ERROR] An error occurred in \"{}\": \n    {}", PRETTY_FUNCTION_NAME, message));
        }
        catch (const std::exception& e)
        {
            qDebug() << QString::fromStdString(::solar::format(
                "[ERROR] An error occurred in \"{}\": \n    {}", PRETTY_FUNCTION_NAME, e.what()));
        }
    }
}

auto AnalyticFunctionWindowAdapter::getHeliostatWithGlassPara(std::uint64_t heliostat_index,
                                                              const QString& key) -> QString
{
    ASSUME(!key.isEmpty());
    if (this->heliostat_paras_.contains(heliostat_index)) [[likely]]
    {
        auto* ptr = this->heliostat_paras_.at(heliostat_index)
                        .get()
                        ->getPara(toMemberName("heliostat_glass_para"))
                        .value<std::shared_ptr<HeliostatWithGlassPara>>()
                        .get();
        if (::solar::paraHasValue(key.toStdString(), ptr))
        {
            return QString::fromStdString(::solar::getParaAsString(key.toStdString(), ptr));
        }
    }
    return " ";
}

void AnalyticFunctionWindowAdapter::setHeliostatWithGlassPara(std::uint64_t heliostat_index,
                                                              const QString& key,
                                                              const QString& value)
{
    ASSUME(!key.isEmpty());
    if (value.isEmpty() || value == " ") [[unlikely]]
    {
        return;
    }
    if (this->heliostat_paras_.contains(heliostat_index)) [[likely]]
    {
        try
        {
            auto* ptr = this->heliostat_paras_.at(heliostat_index)
                            ->getPara(toMemberName("heliostat_glass_para"))
                            .value<std::shared_ptr<HeliostatWithGlassPara>>()
                            .get();
            ::solar::setParaFromString(key.toStdString(), value.toStdString(), ptr);
        }
        catch (const std::string& message)
        {
            qDebug() << QString::fromStdString(::solar::format(
                "[ERROR] An error occurred in \"{}\": \n    {}", PRETTY_FUNCTION_NAME, message));
        }
        catch (const std::exception& e)
        {
            qDebug() << QString::fromStdString(::solar::format(
                "[ERROR] An error occurred in \"{}\": \n    {}", PRETTY_FUNCTION_NAME, e.what()));
        }
    }
}

auto AnalyticFunctionWindowAdapter::getModelPara(std::uint64_t heliostat_index,
                                                 ModelType model_type, int detail_model_type,
                                                 const QString& key) -> QString
{
    ASSUME(!key.isEmpty());
    auto get_para_function = [&]<Pointer T>(T ptr) -> QString
    {
        if (::solar::paraHasValue(key.toStdString(), ptr))
        {
            return QString::fromStdString(::solar::getParaAsString(key.toStdString(), ptr));
        }
        return " ";
    };
    if (this->heliostat_paras_.contains(heliostat_index)) [[likely]]
    {
        if (model_type == ModelType::kSimplified)
        {
            auto* raw_ptr = this->simplified_models_.at(SimplifiedModelType(detail_model_type))
                                .at(heliostat_index)
                                ->getPara(toMemberName("model_para"))
                                .value<std::shared_ptr<ModelPara>>()
                                .get();
            switch (SimplifiedModelType(detail_model_type))
            {
                using enum solar::SimplifiedModelType;
            case kHFLCAL:
                return get_para_function(dynamic_cast<HFLCALPara*>(raw_ptr));
            case kiHFLCAL:
                return get_para_function(dynamic_cast<IHFLCALPara*>(raw_ptr));
            case kbHFLCAL:
                return get_para_function(dynamic_cast<BHFLCALPara*>(raw_ptr));
            case kNEG:
                return get_para_function(dynamic_cast<NEGPara*>(raw_ptr));
            }
        }
        if (model_type == ModelType::kConvolution)
        {
            auto* raw_ptr = this->convolution_models_.at(ConvolutionModelType(detail_model_type))
                                .at(heliostat_index)
                                ->getPara(toMemberName("model_para"))
                                .value<std::shared_ptr<ModelPara>>()
                                .get();
            qDebug() << raw_ptr;
            switch (ConvolutionModelType(detail_model_type))
            {
                using enum solar::ConvolutionModelType;
            case kUNIZAR:
                return get_para_function(dynamic_cast<UNIZARPara*>(raw_ptr));
            case kHuang:
                return get_para_function(dynamic_cast<HuangPara*>(raw_ptr));
            case kiCauchy:
                return get_para_function(dynamic_cast<ICauchyPara*>(raw_ptr));
            }
        }
    }
    return " ";
}

void AnalyticFunctionWindowAdapter::setModelPara(std::uint64_t heliostat_index,
                                                 ModelType model_type, int detail_model_type,
                                                 const QString& key, const QString& value)
{
    ASSUME(!key.isEmpty());
    if (value.isEmpty() || value == " ") [[unlikely]]
    {
        return;
    }
    auto set_para_function = [&]<Pointer T>(T ptr)
    {
        try
        {
            ::solar::setParaFromString(key.toStdString(), value.toStdString(), ptr);
        }
        catch (const std::string& message)
        {
            qDebug() << QString::fromStdString(::solar::format(
                "[ERROR] An error occurred in \"{}\": \n    {}", PRETTY_FUNCTION_NAME, message));
        }
        catch (const std::exception& e)
        {
            qDebug() << QString::fromStdString(::solar::format(
                "[ERROR] An error occurred in \"{}\": \n    {}", PRETTY_FUNCTION_NAME, e.what()));
        }
    };
    if (this->heliostat_paras_.contains(heliostat_index)) [[likely]]
    {
        if (model_type == ModelType::kSimplified)
        {
            auto* raw_ptr = this->simplified_models_.at(SimplifiedModelType(detail_model_type))
                                .at(heliostat_index)
                                ->getPara(toMemberName("model_para"))
                                .value<std::shared_ptr<ModelPara>>()
                                .get();
            switch (SimplifiedModelType(detail_model_type))
            {
                using enum solar::SimplifiedModelType;
            case kHFLCAL:
                return set_para_function(dynamic_cast<HFLCALPara*>(raw_ptr));
            case kiHFLCAL:
                return set_para_function(dynamic_cast<IHFLCALPara*>(raw_ptr));
            case kbHFLCAL:
                return set_para_function(dynamic_cast<BHFLCALPara*>(raw_ptr));
            case kNEG:
                return set_para_function(dynamic_cast<NEGPara*>(raw_ptr));
            }
        }
        if (model_type == ModelType::kConvolution)
        {
            auto* raw_ptr = this->convolution_models_.at(ConvolutionModelType(detail_model_type))
                                .at(heliostat_index)
                                ->getPara(toMemberName("model_para"))
                                .value<std::shared_ptr<ModelPara>>()
                                .get();
            switch (ConvolutionModelType(detail_model_type))
            {
                using enum solar::ConvolutionModelType;
            case kUNIZAR:
                return set_para_function(dynamic_cast<UNIZARPara*>(raw_ptr));
            case kHuang:
                return set_para_function(dynamic_cast<HuangPara*>(raw_ptr));
            case kiCauchy:
                return set_para_function(dynamic_cast<ICauchyPara*>(raw_ptr));
            }
        }
    }
}
