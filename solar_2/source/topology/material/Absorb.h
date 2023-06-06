#ifndef ABSORB_H
#define ABSORB_H

#include "topology/material/Material.h"

namespace solar
{
    // Absorb：仅吸收
    class Absorb : public Material
    {
        public:
            virtual ~Absorb() = default;
            Absorb() : type_(kMaterialAbsorb) { absorptivity_ = 1;}

            void setPara(const std::string& property_type, const QVariant& value) override;
            auto getPara(const std::string& property_type) -> QVariant override;
            [[nodiscard]] auto getType() const -> MaterialType override;
            void testPrint() const override;
            
#include <utils/class_name.inc>

        private:
            double absorptivity_ ;      // 吸收率，默认为1，但是可以更改

            MaterialType type_;
            BOOST_DESCRIBE_CLASS(solar::Absorb, (solar::Material), (), (), (absorptivity_, type_))
    };

}

#endif
