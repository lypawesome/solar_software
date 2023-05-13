#ifndef TERRAIN_H
#define TERRAIN_H

#include "utils/Para.h"
#include "utils/Grid.h"
#include "utils/Utils.h"


namespace solar{

   class Terrain : public Para
   {
   public:
       virtual ~Terrain() = default;
       Terrain()
       {
           grid_ = std::make_shared<Grid>();
       }

       void setPara(const int property_type, const QVariant& value) override;
       [[nodiscard]] auto getPara(const int property_type) const
           -> QVariant override;
       void testPrint() const override;

   private:
       void readFile();        //从file中导入heights

   private:
       std::shared_ptr<Grid> grid_;
       std::vector<std::vector<double>> heights_; // 从file中导入的，每个格子的高度
   }; 
}

#endif