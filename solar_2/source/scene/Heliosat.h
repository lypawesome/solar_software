#ifndef HELIOSAT_H
#define HELIOSAT

#include "utils/Para.h"
#include "topology/material/Material.h"
#include "topology/geometry/Geometry.h"
#include "utils/Utils.h"


namespace solar{
class Heliosat: public Para
    {
        public:
            virtual ~Heliosat()=default;
            Heliosat(){}

            void setPara(const int property_type, const QVariant& value) override;
            [[nodiscard]] auto getPara(const int property_type) const
                        -> QVariant override;
            void testPrint() const override;

        private:
            std::shared_ptr<Material> material_;
            std::shared_ptr<Geometry> geometry_;
            //std::shared_ptr<Tracker> tracker_;    //tracker要创建
            
    };
    
}

#endif