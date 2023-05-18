#include "topology/geometry/Geometry.h"
#include <utils/Vec3.h>

#include <boost/describe.hpp>

namespace solar
{
    /*
     * 自定义
     * 读入mesh(.obj)文件，这个文件记录了定日镜上各个点的位置、法向信息
     */
    class Mesh : public Geometry
    {
        public:
            Mesh() = default;

            void setPara(const std::string& property_type, const QVariant& value) override;
            auto getPara(const std::string& property_type) -> QVariant override;
            [[nodiscard]] auto getType() const -> GeometryType override { return type_; }
            void readFile(); // 读取文件
#include <utils/class_name.inc>

        private:
            std::string file_;
            GeometryType type_ = kGeometryMesh;

            std::vector<std::vector<Vec3>> points_;
            std::vector<std::vector<Vec3>> normals_;
            BOOST_DESCRIBE_CLASS(Mesh, (Geometry), (), (), (file_, type_, points_, normals_))
    };
} // namespace solar