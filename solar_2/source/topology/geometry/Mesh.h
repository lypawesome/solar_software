#include "topology/geometry/Geometry.h"

namespace solar
{
     /*
     * 自定义
     * 读入mesh(.obj)文件，这个文件记录了定日镜上各个点的位置、法向信息
    */
    class Mesh : public Geometry
    {
    public:
        Mesh() : file_(""), type_(kGeometryMesh) { }

        void setPara(const int property_type, const QVariant& value) override;
        auto getPara(const int property_type) const -> QVariant override ;
        GeometryType getType() override { return type_;   }
        void readFile();    //读取文件

    private:
        std::string file_;
        GeometryType type_;

        std::vector<std::vector<Vec3>> points_;
        std::vector<std::vector<Vec3>> normals_;
    };
}