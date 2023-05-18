#ifndef LOCATION_H
#define LOCATION_H

#include <utility>

#include "utils/Para.h"
#include "utils/Utils.h"

#include <boost/describe.hpp>

namespace solar
{

    class Location : public Para
    {
        public:
            Location(std::string site_name = "unknown", double longitude = 0, double latitude = 0)
                : site_name_(std::move(site_name)), longitude_(longitude), latitude_(latitude)
            {
            }

            void setPara(const std::string& property_type, const QVariant& value) override;
            [[nodiscard]] auto getPara(const std::string& property_type) -> QVariant override;
            void testPrint() const override;
#include <utils/class_name.inc>

        private:
            std::string site_name_;
            double longitude_;
            double latitude_;
            BOOST_DESCRIBE_CLASS(Location, (Para), (), (), (site_name_, longitude_, latitude_))
    };

} // namespace solar

#endif
