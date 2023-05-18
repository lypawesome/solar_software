#ifndef RECEIVER_H
#define RECEIVER_H

#include "utils/Para.h"
#include "utils/Utils.h"

#include <boost/describe.hpp>

namespace solar
{
    class Material;
    class Geometry;

    class Receiver : public Para
    {
        public:
            ~Receiver() override = default;
            Receiver() = default;

            void setPara(const std::string& property_type, const QVariant& value) override;
            [[nodiscard]] auto getPara(const std::string& property_type) -> QVariant override;
            void testPrint() const override;
#include <utils/class_name.inc>

        private:
            std::shared_ptr<Material> material_;
            std::shared_ptr<Geometry> geometry_;
            BOOST_DESCRIBE_CLASS(Receiver, (Para), (), (), (material_, geometry_))
    };

} // namespace solar

#endif