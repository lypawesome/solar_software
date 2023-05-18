#ifndef CLOUD_H
#define CLOUD_H

#include "utils/Para.h"
#include "utils/Utils.h"

#include <boost/describe.hpp>

namespace solar
{
    class Grid;

    class Cloud : public Para
    {
        public:
            virtual ~Cloud() = default;
            Cloud();

            void setPara(const std::string& property_type, const QVariant& value) override;
            [[nodiscard]] auto getPara(const std::string& property_type) -> QVariant override;
            void testPrint() const override;
#include <utils/class_name.inc>

        private:
            void readFile();

        private:
            std::shared_ptr<Grid> grid_;
            // 衰减因子k的数组，从文件中读取获得当光线经过云层时，DNI变为k*DNI
            std::vector<std::vector<double>> k_;
            BOOST_DESCRIBE_CLASS(Cloud, (Para), (), (), (grid_, k_))
    };

} // namespace solar

#endif