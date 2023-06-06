#ifndef ORDINARY_H
#define ORDINARY_H

#include "utils/Para.h"
#include "topology/material/Material.h"
#include "topology/geometry/Geometry.h"
#include "utils/Utils.h"

#include <boost/describe.hpp>

namespace solar{

    class Ordinary : public Para
    {
        public:
            virtual ~Ordinary(){}
            Ordinary();

            void setPara(const std::string& property_type, const QVariant& value) override;
            [[nodiscard]] auto getPara(const std::string& property_type) -> QVariant override;
            void testPrint() const override;
#include <utils/class_name.inc>

        private:
            std::shared_ptr<Geometry> geometry_;
            BOOST_DESCRIBE_CLASS(Ordinary, (Para), (), (), (geometry_))


    };

}


#endif