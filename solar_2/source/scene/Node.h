#ifndef NODE_H
#define NODE_H

#include "utils/Para.h"
#include "world/air/Attenuation.h"
#include "world/air/VacuumAttenuation.h"
#include "utils/Utils.h"

#include "utils/Rotation.h"


namespace solar{
   class Node : public Para
   {
   public:
       virtual ~Node() = default;
       Node(const Vec3& translation=Vec3(0,0,0), const Vec3& rotation_axis=Vec3(0,0,1),
            double rotation_angle=0.0, const Vec3& scale=Vec3(1,1,1))
           : translation_(translation), rotation_(Rotation(rotation_axis,rotation_angle)),scale_(scale)
       { }

       void setPara(const int property_type, const QVariant& value) override;
       [[nodiscard]] auto getPara(const int property_type) const
           -> QVariant override;
       void testPrint() const override;

   private:
       Vec3 translation_;     //位移
       Rotation rotation_;     //旋转
       Vec3 scale_;               //放缩
   };
    
}

#endif