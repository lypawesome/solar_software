#ifndef CLOUD_H
#define CLOUD_H

#include "utils/Para.h"
#include "utils/Grid.h"
#include "utils/Utils.h"

namespace solar{
   class Cloud : public Para
   {
   public:
       virtual ~Cloud() = default;
       // Cloud(){};
       Cloud()
       {
           grid_ = std::make_shared<Grid>();
       }

       void setPara(const int property_type, const QVariant& value) override;
       [[nodiscard]] auto getPara(const int property_type) const
           -> QVariant override;
       void testPrint() const override;

   private:
       void readFile();
   private:
       std::shared_ptr<Grid> grid_;
       std::vector<std::vector<double>> k_; // 衰减因子k的数组，从文件中读取获得当光线经过云层时，DNI变为k*DNI

   };
    
}

#endif