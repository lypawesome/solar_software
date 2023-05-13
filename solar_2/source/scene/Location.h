#ifndef LOCATION_H
#define LOCATION_H

#include "utils/Para.h"
#include "utils/Utils.h"

namespace solar{

class Location : public Para
    {
    public:
        Location(std::string site_name = "unknown", double longitude = 0, double latitude = 0)
            : site_name_(site_name), longitude_(longitude), latitude_(latitude) {}


        void setPara(const int property_type, const QVariant& value) override;
        [[nodiscard]] auto getPara(const int property_type) const
            -> QVariant override;
        void testPrint() const override;

    private:
        std::string site_name_;
        double longitude_;
        double latitude_;
    };

}

#endif
