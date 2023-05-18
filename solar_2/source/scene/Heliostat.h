#ifndef HELIOSAT_H
    #define HELIOSAT

    #include "utils/Para.h"
    #include "utils/Utils.h"

    #include <boost/describe.hpp>

namespace solar
{
    class Material;
    class Geometry;

    class Heliostat : public Para
    {
        public:
            virtual ~Heliostat() = default;
            Heliostat() = default;

            void setPara(const std::string& property_type, const QVariant& value) override;
            [[nodiscard]] auto getPara(const std::string& property_type) -> QVariant override;
            void testPrint() const override;
    #include <utils/class_name.inc>

        private:
            std::shared_ptr<Material> material_;
            std::shared_ptr<Geometry> geometry_;
            // std::shared_ptr<Tracker> tracker_;    //tracker要创建
            BOOST_DESCRIBE_CLASS(Heliostat, (Para), (), (), (material_, geometry_))
    };

} // namespace solar

#endif
