#ifndef AIR_H
#define AIR_H

#include "utils/Para.h"
#include "world/air/Attenuation.h"
#include "world/air/VacuumAttenuation.h"
#include "utils/Utils.h"

namespace solar{

    class Air : public Para
   {
   public:
       virtual ~Air() = default;
       Air()
       {
           attenuation_ =std::make_shared<VacuumAttenuation>();
       }

       void setPara(const int property_type, const QVariant& value) override;
       [[nodiscard]] auto getPara(const int property_type) const
           -> QVariant override;
       void testPrint() const override;

   private:
       std::shared_ptr<Attenuation> attenuation_;
   };

}

#endif