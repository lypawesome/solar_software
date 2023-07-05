#pragma once

#include <QObject>

namespace solar
{
    class AnalyticFunctionWindowEnums : public QObject
    {
            Q_OBJECT
        public:
            explicit AnalyticFunctionWindowEnums() = default;
            // 与Constants.h中的enum顺序相同，首字母需大写（QML BUG？）

            enum class ProjectionType
            {
                Parallel, // 斜平行投影
                Gnomonic, // 带投影校正的斜平行投影 [NEG]
            };

            enum class SimplifiedModelType
            {
                HFLCAL,
                IHFLCAL,
                BHFLCAL,
                NEG,
            };

            enum class ConvolutionModelType
            {
                UNIZAR,
                ICauchy,
                Huang,
            };

            enum class ModelType
            {
                Simplified,
                Convolution,
            };

            enum class HeliostatType
            {
                WithoutGlass,
                WithGlass,
            };

            // UI only part

            enum class TableViewType
            {
                HFLCALBasedTableView,
                UNIZARTableView,
                ICauchyTableView,
                HuangTableView,
                HuangWithGlassTableView,
            };
            Q_ENUM(ProjectionType)
            Q_ENUM(ModelType)
            Q_ENUM(SimplifiedModelType)
            Q_ENUM(ConvolutionModelType)
            Q_ENUM(HeliostatType)
            Q_ENUM(TableViewType)
    };
} // namespace solar
