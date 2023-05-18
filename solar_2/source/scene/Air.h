#ifndef AIR_H
#define AIR_H

#include "utils/Para.h"
#include "utils/Utils.h"

#include <boost/describe.hpp>

namespace solar
{
    class Attenuation;

    class Air : public Para
    {
        public:
            virtual ~Air() = default;
            Air();

            void setPara(const std::string& property_type, const QVariant& value) override;
            [[nodiscard]] auto getPara(const std::string& property_type) -> QVariant override;
            void testPrint() const override;
#include <utils/class_name.inc>

        private:
            std::shared_ptr<Attenuation> attenuation_;
            BOOST_DESCRIBE_CLASS(Air, (Para), (), (), (attenuation_))
    };

} // namespace solar

#endif