#ifndef RECEIVER_H
#define RECEIVER_H

#include "utils/Para.h"
#include "topology/material/Material.h"
#include "topology/geometry/Geometry.h"
#include "utils/Utils.h"


namespace solar{
class Receiver: public Para
    {
        public:
            virtual ~Receiver()=default;
            Receiver(){}

            void setPara(const int property_type, const QVariant& value) override;
            [[nodiscard]] auto getPara(const int property_type) const
                        -> QVariant override;
            void testPrint() const override;

        private:
            std::shared_ptr<Material> material_;
            std::shared_ptr<Geometry> geometry_;


    };

    
}

#endif