#ifndef RECEIVER_H
#define RECEIVER_H

#include "utils/Para.h"
#include "utils/Utils.h"

#include <boost/describe.hpp>

#include <cstdlib>

namespace solar
{
    class Material;
    class Geometry;

    class Receiver : public Para
    {
        public:
            ~Receiver() override = default;
            Receiver() ;

            void setPara(const std::string& property_type, const QVariant& value) override;
            [[nodiscard]] auto getPara(const std::string& property_type) -> QVariant override;
            void testPrint() const override;
#include <utils/class_name.inc>
            static int receiver_cnt_;
        private:
            std::uint64_t id_ ;
            std::shared_ptr<Material> material_;
            std::shared_ptr<Geometry> geometry_;
            BOOST_DESCRIBE_CLASS(Receiver, (Para), (), (), (id_,material_, geometry_))
    };


} // namespace solar

#endif