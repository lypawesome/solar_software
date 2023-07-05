#pragma once

#include <QObject>
#include <QString>

#include <boost/describe.hpp>
#include <boost/unordered/unordered_flat_map.hpp>

#include <cstdlib>
#include <memory>
#include <unordered_set>
#include <vector>


#include <analytical_model/CommonPara.h>
#include <analytical_model/Constants.h>
#include <analytical_model/ScenePara.h>
#include <analytical_model/SimulationPara.h>
#include <analytical_model/ui/AnalyticFunctionWindowEnums.h>

namespace solar
{
    class Para;
    class HeliostatPara;
    class SimplifiedPara;
    class ConvolutionPara;

    /// \brief 解析模型设置界面-C++交互部分
    class AnalyticFunctionWindowAdapter : public QObject
    {
            Q_OBJECT

        public:
#include <utils/class_name.inc>
            AnalyticFunctionWindowAdapter();
            Q_INVOKABLE void testConnect() const;
            // NOLINTNEXTLINE(modernize-use-trailing-return-type)
            Q_INVOKABLE [[nodiscard]] ProjectionType getProjectionType() const;
            Q_INVOKABLE void setProjectionType(const ProjectionType& type);
            // NOLINTNEXTLINE(modernize-use-trailing-return-type)
            Q_INVOKABLE [[nodiscard]] ModelType getModelType() const;
            Q_INVOKABLE void setModelType(const ModelType& type);
            // NOLINTNEXTLINE(modernize-use-trailing-return-type)
            Q_INVOKABLE [[nodiscard]] SimplifiedModelType getSimplifiedModelType() const;
            Q_INVOKABLE void setSimplifiedModelType(const SimplifiedModelType& type);
            // NOLINTNEXTLINE(modernize-use-trailing-return-type)
            Q_INVOKABLE [[nodiscard]] ConvolutionModelType getConvolutionModelType() const;
            Q_INVOKABLE void setConvolutionModelType(const ConvolutionModelType& type);
            // NOLINTNEXTLINE(modernize-use-trailing-return-type)
            Q_INVOKABLE [[nodiscard]] HeliostatType getHeliostatType() const;
            Q_INVOKABLE void setHeliostatType(const HeliostatType& type);
            // NOLINTNEXTLINE(modernize-use-trailing-return-type)
            Q_INVOKABLE [[nodiscard]] QString getCommonPara(const QString& key);
            Q_INVOKABLE void setCommonPara(const QString& key, const QString& value);
            // NOLINTNEXTLINE(modernize-use-trailing-return-type)
            Q_INVOKABLE [[nodiscard]] QString getScenePara(const QString& key);
            Q_INVOKABLE void setScenePara(const QString& key, const QString& value);
            // NOLINTNEXTLINE(modernize-use-trailing-return-type)
            Q_INVOKABLE [[nodiscard]] QString getSimulationPara(const QString& key);
            Q_INVOKABLE void setSimulationPara(const QString& key, const QString& value);
            // NOLINTNEXTLINE(modernize-use-trailing-return-type)
            Q_INVOKABLE [[nodiscard]] std::uint64_t getNumberOfHeliostats() const;
            // NOLINTNEXTLINE(modernize-use-trailing-return-type)
            Q_INVOKABLE [[nodiscard]] QVariantList getHeliostatIndices() const;
            // NOLINTBEGIN(modernize-use-trailing-return-type)
            Q_INVOKABLE [[nodiscard]] QString getHeliostatPara(std::uint64_t heliostat_index,
                                                               const QString& key);
            // NOLINTEND(modernize-use-trailing-return-type)
            Q_INVOKABLE void setHeliostatPara(std::uint64_t heliostat_index, const QString& key,
                                              const QString& value);
            // NOLINTBEGIN(modernize-use-trailing-return-type)
            Q_INVOKABLE [[nodiscard]] QString
            getHeliostatWithGlassPara(std::uint64_t heliostat_index, const QString& key);
            // NOLINTEND(modernize-use-trailing-return-type)
            Q_INVOKABLE void setHeliostatWithGlassPara(std::uint64_t heliostat_index,
                                                       const QString& key, const QString& value);
            // NOLINTBEGIN(modernize-use-trailing-return-type)
            Q_INVOKABLE [[nodiscard]] QString getModelPara(std::uint64_t heliostat_index,
                                                           ModelType model_type,
                                                           int detail_model_type,
                                                           const QString& key);
            // NOLINTEND(modernize-use-trailing-return-type)
            Q_INVOKABLE void setModelPara(std::uint64_t heliostat_index, ModelType model_type,
                                          int detail_model_type, const QString& key,
                                          const QString& value);
            Q_INVOKABLE void addRowChanged(const AnalyticFunctionWindowEnums::TableViewType& type,
                                           const std::uint64_t& row);
            // NOLINTBEGIN(modernize-use-trailing-return-type)
            Q_INVOKABLE [[nodiscard]] QVariantList
            getRowsChanged(const AnalyticFunctionWindowEnums::TableViewType& type) const;
            // NOLINTEND(modernize-use-trailing-return-type)
            Q_INVOKABLE void
            clearRowsChanged(const AnalyticFunctionWindowEnums::TableViewType& type);
            // NOLINTNEXTLINE(modernize-use-trailing-return-type)
            Q_INVOKABLE [[nodiscard]] bool dataChangedFromExternal() const;
            Q_INVOKABLE void dataSyncedWithUI();

        private:
            ProjectionType projection_type_ = ProjectionType::kParallel;
            ModelType model_type_ = ModelType::kSimplified;
            HeliostatType heliostat_type_ = HeliostatType::kWithoutGlass;
            SimplifiedModelType simplified_model_type_ = SimplifiedModelType::kHFLCAL;
            ConvolutionModelType convolution_model_type_ = ConvolutionModelType::kUNIZAR;
            boost::unordered::unordered_flat_map<
                SimplifiedModelType, boost::unordered::unordered_flat_map<
                                         std::uint64_t, std::shared_ptr<SimplifiedPara>>>
                simplified_models_;
            boost::unordered::unordered_flat_map<
                ConvolutionModelType, boost::unordered::unordered_flat_map<
                                          std::uint64_t, std::shared_ptr<ConvolutionPara>>>
                convolution_models_;
            boost::unordered::unordered_flat_map<std::uint64_t, std::shared_ptr<HeliostatPara>>
                heliostat_paras_;
            SimulationPara simulation_para_;
            ScenePara scene_para_;
            CommonPara common_para_;

            // UI only part

            boost::unordered::unordered_flat_map<AnalyticFunctionWindowEnums::TableViewType,
                                                 std::unordered_set<std::uint64_t>>
                rows_changed;
            bool data_changed_from_external = false;
            BOOST_DESCRIBE_CLASS(AnalyticFunctionWindowAdapter, (QObject), (), (),
                                 (projection_type_, model_type_, simplified_model_type_,
                                  convolution_model_type_, simplified_models_, convolution_models_,
                                  heliostat_paras_, rows_changed, data_changed_from_external))
    };
} // namespace solar
