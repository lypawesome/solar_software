
#include "tree/ParaTreeModel.h"

#include <utils/ParaUtils.h>
#include <world/sun/sun_position/SunPosition.h>
#include <world/sun/sunshape/SunShape.h>

#include "world/air/VacuumAttenuation.h"
#include "world/air/Attenuation.h"
#include "world/air/CustomAttenuation.h"
#include "world/air/ExponentialAttenuation.h"
#include "utils/Grid.h"


namespace solar
{

    ParaTreeModel::ParaTreeModel(TreeModelType _model_type, QSharedPointer<Para> _para,
                                 QObject* parent)
        : QAbstractItemModel(parent), model_type(_model_type), para(_para)
    {

        this->role_names_ = QHash<int, QByteArray>(QAbstractItemModel::roleNames());
        this->role_names_[NAME] = "name";
        this->role_names_[PARA] = "para";

        root_node = createNode(nullptr, "root",
                               ""); // 建立根节点,这个节点在视图中不显示,因此其他参数部分采用默认值
        
        qDebug() <<"++++1";
        switch (model_type)
        {

        case LOCATION:
        {
            buildLocationTreeModel(para.dynamicCast<Location>());
            setLabelTxt("location");
            break;
        }
        case SUN:
        {
            buildSunTreeModel(para.dynamicCast<Sun>());
            setLabelTxt("sun");
            break;
        }
        case AIR:
        {
            buildAirTreeModel(para.dynamicCast<Air>());
            setLabelTxt("air");
            break;
        }
        case TERRAIN:
        {
            buildTerrainTreeModel(para.dynamicCast<Terrain>());
            setLabelTxt("terrain");
            break;
        }
        case CAMERA:
        {
            buildCameraTreeModel(para.dynamicCast<Camera>());
            setLabelTxt("camera");
            break;
        }
        case CLOUD:
        {
            buildCloudTreeModel(para.dynamicCast<Cloud>());
            setLabelTxt("cloud");
            break;
        }
        case NODE:
        {
            buildNodeTreeModel(para.dynamicCast<Node>());
            setLabelTxt("node");
            break;
        }
        case HELIOSTAT:
        {
            qDebug() <<"++++2";
            buildHeliostatTreeModel(para.dynamicCast<Heliostat>());
            qDebug() <<"++++3";
            setLabelTxt("heliostat");
            break;
        }
        case RECEIVER:
        {
            buildReceiverTreeModel(para.dynamicCast<Receiver>());
            setLabelTxt("receiver");
            break;
        }
        case ORDINARY:
        {
            buildOrdinaryTreeModel(para.dynamicCast<Ordinary>());
            setLabelTxt("ordinary");
            break;
        }
        }
    }
    ParaTreeModel::~ParaTreeModel() {}

    /*
    ---------------------------------------------------------------------------
    建立模型相关的函数
    ！！！！！！！！！！！！！！！！！！！！！！！！
    问题：：：在这里设置参数的初始值然后传到para里 or 直接在Para的子类中初始化参数值这里只获取 ？
            目前是，在Para子类中初始化，这里获取参数值
*/

    // state是当前节点的state
    auto ParaTreeModel::createNode(const QSharedPointer<ParaTreeNode>& parent,
                                   const QVariant& data1, const QVariant& data2,
                                   ParaState state,
                                   bool is_current_option_child, const QString& parent_option)
        -> QSharedPointer<ParaTreeNode>
    {
        QList<QVariant> list;
        list.append(data1);
        list.append(data2);
        QSharedPointer<ParaTreeNode> child_node =
            QSharedPointer<ParaTreeNode>(new ParaTreeNode(list, parent));

        child_node->setState(state);

        if (parent == nullptr)
        {
            return child_node;
        }

        ParaState parent_state = parent->getState();
        if (parent_state == OPTIONAL)
        {
            parent->addOptionChild(parent_option, child_node);
            if (is_current_option_child)
            {
                parent->appendChild(child_node);
                if (parent->data(1).toString() != parent_option)    //都已经选中了这一option，父节点的data(1)存的应该就是option
                {
                    parent->setData(parent_option, 1);              //这里的if语句貌似不会执行
                }
            }
        }
        else
        {
            parent->appendChild(child_node);
        }

        return child_node;
    }

    void ParaTreeModel::buildSunTreeModel(const QSharedPointer<Sun>& sun)
    {
        // position
        auto position_node =
            createNode(root_node, "position", ""); // 这个节点不可更改，只是用来放子节点的父节点

        auto sun_position_ptr =
            sun->getPara(toMemberName("sun_position")).value<std::shared_ptr<SunPosition>>();

        // position-azimuth
        QVariant azimuth = sun_position_ptr->getPara(toMemberName("azimuth"));
        createNode(position_node, "azimuth", azimuth, EDITABLE);

        // position-elevation
        QVariant elevation = sun_position_ptr->getPara(toMemberName("elevation"));
        createNode(position_node, "elevation", elevation, EDITABLE);

        // position-irradiance
        QVariant irradiance = sun_position_ptr->getPara(toMemberName("irradiance"));
        createNode(position_node, "irradiance", irradiance, EDITABLE);

        // position-trackable
        QVariant trackable = sun_position_ptr->getPara(toMemberName("trackable"));
        createNode(position_node, "trackable", trackable, EDITABLE);

        // sunshape
        auto sun_shape_ptr =
            sun->getPara(toMemberName("sunshape")).value<std::shared_ptr<SunShape>>();
        SunShapeType current_sunshape_type = sun_shape_ptr->getType();
        QString current_option;
        switch (current_sunshape_type)
        {
            case kSunShapeBuie: current_option = "Buie"; break;
            case kSunShapeGaussian: current_option = "Gaussian"; break;
            case kSunShapePillbox: current_option = "Pillbox"; break;
        }

        auto sunshape_node = createNode(root_node, "sunshape", current_option, OPTIONAL);
        QList<QString> options;
        options.append("Buie");
        options.append("Gaussian");
        options.append("Pillbox");
        sunshape_node->initOptions(options);

        // ！！！这里添加option_child时，一定要格外留意是否选中当前的选项

        // sunshape-csr
        if (current_sunshape_type == kSunShapeBuie)
        {
            QVariant csr = sun_shape_ptr->getPara();
            createNode(sunshape_node, "csr", csr, EDITABLE, true, "Buie");
        }
        else
        {
            QVariant csr = 0.02;
            createNode(sunshape_node, "csr", csr, EDITABLE, false, "Buie");
        }

        // sunshape-theta_max
        if (current_sunshape_type == kSunShapePillbox)
        {
            QVariant theta_max = sun_shape_ptr->getPara();
            createNode(sunshape_node, "theta_max", theta_max, EDITABLE, true, "Pillbox");
        }
        else
        {
            QVariant theta_max = 0.00465;
            createNode(sunshape_node, "theta_max", theta_max, EDITABLE, false,
                       "Pillbox");
        }

        // sunshape-gaussian
        if (current_sunshape_type == kSunShapeGaussian)
        {
            QVariant sigma = sun_shape_ptr->getPara();
            createNode(sunshape_node, "sigma", sigma, EDITABLE, true, "Gaussian");
        }
        else
        {
            QVariant sigma = 0.00251;
            createNode(sunshape_node, "sigma", sigma, EDITABLE, false, "Gaussian");
        }
    }

    void ParaTreeModel::buildLocationTreeModel(const QSharedPointer<Location>& location)
    {
        // site_name
        QVariant site = QString(location->getPara(toMemberName("site_name")).value<std::string>().c_str());
        createNode(root_node, "site_name", site, EDITABLE);
        qDebug() << "-----------Location site_name="<<site;

        // longitude
        QVariant longitude = location->getPara(toMemberName("longitude"));
        createNode(root_node, "longitude", longitude, EDITABLE);

        // latitude
        QVariant latitude = location->getPara(toMemberName("latitude"));
        createNode(root_node, "latitude", latitude, EDITABLE);
    }
    void ParaTreeModel::buildAirTreeModel(QSharedPointer<Air> air)
    {
        auto attenuation_ptr = air->getPara(toMemberName("attenuation")).value<std::shared_ptr<Attenuation>>();
        
        AttenuationType currrent_attenuation_type = attenuation_ptr->getType();
        QString current_option;
        switch(currrent_attenuation_type)
        {
            case kAttenuationVacuum: current_option = "vacuum attenuation"; break;
            case kAttenuationCustom: current_option = "custom attenuation"; break;
            case kAttenuationExponential: current_option = "exponential attenuation";   break;
        }

        auto attenuation_node = createNode(root_node, "attenuation",current_option,OPTIONAL);
        QList<QString> options;
        options.append("vacuum attenuation");
        options.append("custom attenuation");
        options.append("exponential attenuation");
        attenuation_node->initOptions(options);

        // 添加三个option_child
        // 由于暂时 vacuum、custom没有孩子节点，因此暂时只添加exponential的孩子节点
        if(currrent_attenuation_type == kAttenuationExponential)
        {
            QVariant beta = attenuation_ptr->getPara();
            createNode(attenuation_node, "beta", beta, EDITABLE, true, "exponential attenuation");
        }
        else{
            QVariant beta = 0.11 ;
            createNode(attenuation_node, "beta", beta, EDITABLE, false, "exponential attenuation");
        }

    }
    void ParaTreeModel::buildTerrainTreeModel(QSharedPointer<Terrain> terrain)
    {
        // dem_file_
        QVariant dem_file = QString(terrain->getPara(toMemberName("dem_file")).value<std::string>().c_str());
        createNode(root_node,"dem_file",dem_file,EDITABLE);
         qDebug() << "-----------Terrain dem_file="<<dem_file;
    }
    void ParaTreeModel::buildCameraTreeModel(QSharedPointer<Camera> camera)
    {
        // position
        QVariant position = camera->getPara(toMemberName("position"));
        createNode(root_node, "position", QString::fromStdString(position.value<Vec3>().vec32String()), EDITABLE);
        qDebug() << "-----------Camera position="<<position;

        // rotation
        QVariant rotation = camera->getPara(toMemberName("rotation"));
        // QVariant axis = rotation.getPara(toMemberName("axis"));
        // QVariant angle = rotation.getPara(toMemberName("angle"));       // Vec3的如何设置？？？？
        createNode(root_node,"rotation",QString::fromStdString(rotation.value<Rotation>().rotation2String()), EDITABLE);

        // perspective
        QVariant perspective = camera->getPara(toMemberName("perspective"));
        createNode(root_node, "perspective", perspective,EDITABLE);

    }
    void ParaTreeModel::buildCloudTreeModel(QSharedPointer<Cloud> cloud)
    {
        auto grid_ptr = cloud->getPara(toMemberName("grid")).value<std::shared_ptr<Grid>>();
        auto grid_node = createNode(root_node, "grid", "");

        // grid_
        QVariant grid = grid_ptr->getPara(toMemberName("grid"));
        createNode(grid_node, "grid",grid, EDITABLE);

        // fill
        QVariant fill = grid_ptr->getPara(toMemberName("fill"));
        createNode(grid_node, "fill",fill, EDITABLE);

        // steps
        QVariant steps = grid_ptr->getPara(toMemberName("steps"));
        createNode(grid_node, "steps",QString::fromStdString(steps.value<Vec3>().vec32String()), EDITABLE);
        
        // divisions
        QVariant divisions = grid_ptr->getPara(toMemberName("divisions"));
        createNode(grid_node, "divisions",QString::fromStdString(divisions.value<Vec3>().vec32String()), EDITABLE);
        
        // min
        QVariant min = grid_ptr->getPara(toMemberName("min"));
        createNode(grid_node, "min",QString::fromStdString(min.value<Vec3>().vec32String()), EDITABLE);
        
        // max
        QVariant max = grid_ptr->getPara(toMemberName("max"));
        createNode(grid_node, "max",QString::fromStdString(max.value<Vec3>().vec32String()), EDITABLE);
        
        // file
        QVariant file = QString(grid_ptr->getPara(toMemberName("file")).value<std::string>().c_str());
        createNode(grid_node, "file",file, EDITABLE);
         qDebug() << "-----------Cloud file="<<file;

    }
    void ParaTreeModel::buildNodeTreeModel(QSharedPointer<Node> node)
    {
        // translation
        QVariant translation = node->getPara(toMemberName("translation"));
        createNode(root_node, "translation",QString::fromStdString(translation.value<Vec3>().vec32String()), EDITABLE);

        // rotation
        QVariant rotation = node->getPara(toMemberName("rotation"));
        createNode(root_node, "rotation",QString::fromStdString(rotation.value<Rotation>().rotation2String()), EDITABLE);

        //scale
        QVariant scale = node->getPara(toMemberName("scale"));
        createNode(root_node, "scale",QString::fromStdString(scale.value<Vec3>().vec32String()), EDITABLE);

    }

    /**
     * 问题： 每增加一种geometry类型，这里就需要增加一列option_child的添加，过于臃肿
     * 是否可以把添加option chaild node的过程写到每个geometry的具体类里
     * 类似的，前面的optional节点的孩子也可以用同样方法添加
     * 
     * 先写着,写其中一两种简单的geometry
    */
    void ParaTreeModel::buildHeliostatTreeModel(QSharedPointer<Heliostat> heliostat)
    {
        // id
        //Heliostat::heilostat_cnt_ ++ ;
        auto id = heliostat->getPara(toMemberName("id"));
        createNode(root_node,"id",id);

        // geometry
        auto geometry_ptr = heliostat->getPara(toMemberName("geometry")).value<std::shared_ptr<Geometry>>();
        GeometryType current_geometry_type = geometry_ptr->getType();
        QString current_geometry_option = "";
        switch(current_geometry_type)
        {
            case kGeometryRectangle: current_geometry_option="Rectangle"; break;
            case kGeometryParabolic: current_geometry_option="Parabolic"; break;
            case kGeometryBSpline: current_geometry_option="BSpline"; break;
            case kGeometryMesh: current_geometry_option="Mesh"; break;
        }
        auto geometry_node = createNode(root_node,"geometry",current_geometry_option,OPTIONAL);
        QList<QString> geometry_options;
        geometry_options.append("Rectangle");
        geometry_options.append("Parabolic");
        geometry_options.append("BSpline");
        geometry_options.append("Mesh");
        geometry_node->initOptions(geometry_options);

        // option--Rectangle
        if(current_geometry_type == kGeometryRectangle)
        {
            QVariant size = geometry_ptr->getPara(toMemberName("size"));
            createNode(geometry_node,"size", QString::fromStdString(size.value<Vec2>().vec2ToString()),EDITABLE,true,"Rectangle");
        }
        else{
            Vec2 size(1,1);
            createNode(geometry_node,"size", QString::fromStdString(size.vec2ToString()),EDITABLE,false,"Rectangle");
        }

        // option--Parabolic
        if(current_geometry_type == kGeometryParabolic)
        {
            double a = geometry_ptr->getPara(toMemberName("a")).value<double>();
            createNode(geometry_node,"a", QString::fromStdString(std::to_string(a)),EDITABLE,true,"Parabolic");
            double b = geometry_ptr->getPara(toMemberName("b")).value<double>();
            createNode(geometry_node,"b", QString::fromStdString(std::to_string(b)),EDITABLE,true,"Parabolic");

            Vec2 size = geometry_ptr->getPara(toMemberName("size")).value<Vec2>();
            createNode(geometry_node,"size", QString::fromStdString(size.vec2ToString()),EDITABLE,true,"Parabolic");
        }
        else{
            double a = 1;
            createNode(geometry_node,"a", QString::fromStdString(std::to_string(a)),EDITABLE,false,"Parabolic");
            double b = 1;
            createNode(geometry_node,"b", QString::fromStdString(std::to_string(b)),EDITABLE,false,"Parabolic");

            Vec2 size(1,1);
            createNode(geometry_node,"size", QString::fromStdString(size.vec2ToString()),EDITABLE,false,"Parabolic");
        }

        // option--BSpline
        if(current_geometry_type == kGeometryBSpline)
        {
            QVariant file = geometry_ptr->getPara(toMemberName("file"));
            createNode(geometry_node,"file", file,EDITABLE,true,"BSpline");
        }
        else{
            QString file = "";
            createNode(geometry_node,"file", file,EDITABLE,false,"BSpline");
        }

        // option--Mesh
        if(current_geometry_type == kGeometryMesh)
        {
            QVariant file = geometry_ptr->getPara(toMemberName("file"));
            createNode(geometry_node,"file", file,EDITABLE,true,"Mesh");
        }
        else{
            QString file = "";
            createNode(geometry_node,"file", file,EDITABLE,false,"Mesh");
        }

        // heliostat没有absorb这一选项
        // material
        auto material_ptr = heliostat->getPara(toMemberName("material")).value<std::shared_ptr<Material>>();
        MaterialType current_material_type = material_ptr->getType();
        QString current_material_option = "";
        switch(current_material_type)
        {
            case kMaterialReflect:  current_material_option="Reflect";   break;
            case kMaterialRefract:  current_material_option="Refract";   break;
        }

        auto material_node = createNode(root_node, "material",current_material_option,OPTIONAL);
        QList<QString> material_options;
        material_options.append("Reflect");
        material_options.append("Refract");
        material_node->initOptions(material_options);

        // option-reflect
        if(current_material_type == kMaterialReflect)
        {
            QVariant reflectivity = material_ptr->getPara(toMemberName("reflectivity"));
            createNode(material_node,"reflectivity",reflectivity,EDITABLE,true,"Reflect");
            int slope_error_type = material_ptr->getPara(toMemberName("slope_error_type")).toInt();
            QString slope_error_type_string = slope_error_type==kGaussianSlopeError ? 
                                                "Gaussian" : "Pillbox" ;
            auto slope_error_type_node = 
                    createNode(material_node,"slope_error_type",slope_error_type_string,OPTIONAL,true,"Reflect");
            QList<QString> slopeerror_options;
            slopeerror_options.append("Gaussian");
            slopeerror_options.append("Pillbox");
            slope_error_type_node->initOptions(slopeerror_options);

            QVariant slope = material_ptr->getPara(toMemberName("slope"));
            createNode(material_node,"slope",slope,EDITABLE,true,"Reflect");
        }
        else{
            QVariant reflectivity = 0.88;
            createNode(material_node,"reflectivity",reflectivity,EDITABLE,false,"Reflect");
            int slope_error_type = kGaussianSlopeError;
            QString slope_error_type_string = slope_error_type==kGaussianSlopeError ? 
                                                "Gaussian" : "Pillbox" ;
            auto slope_error_type_node = 
                    createNode(material_node,"slope_error_type",slope_error_type_string,OPTIONAL,false,"Reflect");
            QList<QString> slopeerror_options;
            slopeerror_options.append("Gaussian");
            slopeerror_options.append("Pillbox");
            slope_error_type_node->initOptions(slopeerror_options);

            QVariant slope = 0.02;
            createNode(material_node,"slope",slope,EDITABLE,false,"Reflect");
        }

        // option-refract
        if(current_material_type == kMaterialRefract)
        {
            // QVariant reflectivity = material_ptr->getPara(toMemberName("reflectivity"));
            // createNode(material_node,"reflectivity",reflectivity,EDITABLE,true,"Refract");
            QVariant transmissivity = material_ptr->getPara(toMemberName("transmissivity"));
            createNode(material_node,"transmissivity",transmissivity,EDITABLE,true,"Refract");
            QVariant air_refractive_index = material_ptr->getPara(toMemberName("air_refractive_index"));
            createNode(material_node,"air_refractive_index",air_refractive_index,EDITABLE,true,"Refract");
            QVariant glass_refractive_index = material_ptr->getPara(toMemberName("glass_refractive_index"));
            createNode(material_node,"glass_refractive_index",glass_refractive_index,EDITABLE,true,"Refract");
            QVariant glass_thickness = material_ptr->getPara(toMemberName("glass_thickness"));
            createNode(material_node,"glass_thickness",glass_thickness,EDITABLE,true,"Refract");
            
            int slope_error_type = material_ptr->getPara(toMemberName("slope_error_type")).toInt();
            QString slope_error_type_string = slope_error_type==kGaussianSlopeError ? 
                                                "Gaussian" : "Pillbox" ;
            auto slope_error_type_node = 
                    createNode(material_node,"slope_error_type",slope_error_type_string,OPTIONAL,true,"Refract");
            QList<QString> slopeerror_options;
            slopeerror_options.append("Gaussian");
            slopeerror_options.append("Pillbox");
            slope_error_type_node->initOptions(slopeerror_options);

            QVariant slope = material_ptr->getPara(toMemberName("slope"));
            createNode(material_node,"slope",slope,EDITABLE,true,"Refract");
        }
        else{
            // QVariant reflectivity = 0.88;
            // createNode(material_node,"reflectivity",reflectivity,EDITABLE,false,"Refract");
            QVariant transmissivity = 0.1;
            createNode(material_node,"transmissivity",transmissivity,EDITABLE,false,"Refract");
            QVariant air_refractive_index = 1.0;
            createNode(material_node,"air_refractive_index",air_refractive_index,EDITABLE,false,"Refract");
            QVariant glass_refractive_index = 1.5;
            createNode(material_node,"glass_refractive_index",glass_refractive_index,EDITABLE,false,"Refract");
            QVariant glass_thickness = 0.5;
            createNode(material_node,"glass_thickness",glass_thickness,EDITABLE,false,"Refract");
            

            int slope_error_type = kGaussianSlopeError;
            QString slope_error_type_string = slope_error_type==kGaussianSlopeError ? 
                                                "Gaussian" : "Pillbox" ;
            auto slope_error_type_node = 
                    createNode(material_node,"slope_error_type",slope_error_type_string,OPTIONAL,false,"Refract");
            QList<QString> slopeerror_options;
            slopeerror_options.append("Gaussian");
            slopeerror_options.append("Pillbox");
            slope_error_type_node->initOptions(slopeerror_options);

            QVariant slope = 0.02;
            createNode(material_node,"slope",slope,EDITABLE,false,"Refract");
        }


        QVariant thickness = heliostat->getPara(toMemberName("thickness"));
        createNode(root_node,"thickness", thickness,EDITABLE);

        QVariant has_brace = heliostat->getPara(toMemberName("has_brace"));
        createNode(root_node,"has_brace", has_brace, EDITABLE);


        /*
            ！！！！！力学参数这里写得有问题，以后再改吧
        */
        // 力学参数
        // auto mechanical_para_ptr = heliostat->getPara(toMemberName("mechanical_para")).value<std::shared_ptr<MechanicalPara>>();
        // auto mechanical_para_node = createNode(root_node,"mechanical_para","");
        // QVariant density = mechanical_para_ptr->getPara(toMemberName("density"));
        // createNode(mechanical_para_node,"density",density,EDITABLE);
        // QVariant elastic_modulus = mechanical_para_ptr->getPara(toMemberName("elastic_modulus"));
        // createNode(mechanical_para_node,"elastic_modulus",elastic_modulus,EDITABLE);

    }

    /**
     * material固定为absorb
    */
    void ParaTreeModel::buildReceiverTreeModel(QSharedPointer<Receiver> receiver)
    {
        // id
        auto id = receiver->getPara(toMemberName("id"));
        createNode(root_node,"id",id);

        //geometry
        auto geometry_ptr = receiver->getPara(toMemberName("geometry")).value<std::shared_ptr<Geometry>>();
        GeometryType current_geometry_type = geometry_ptr->getType();
        QString current_geometry_option = "";
        switch(current_geometry_type)
        {
            case kGeometryRectangle: current_geometry_option="Rectangle"; break;
            case kGeometryCylinder: current_geometry_option="Cylinder"; break;
            case kGeometryMultiPanelComprisedOfHeatTube: 
                current_geometry_option="MultiPanelComprisedOfHeatTube"; break;
        }
        auto geometry_node = createNode(root_node,"geometry",current_geometry_option,OPTIONAL);
        QList<QString> geometry_options;
        geometry_options.append("Rectangle");
        geometry_options.append("Cylinder");
        geometry_options.append("MultiPanelComprisedOfHeatTube");
        geometry_node->initOptions(geometry_options);

        // option--Rectangle
        if(current_geometry_type == kGeometryRectangle)
        {
            QVariant size = geometry_ptr->getPara(toMemberName("size"));
            createNode(geometry_node,"size", QString::fromStdString(size.value<Vec2>().vec2ToString()),EDITABLE,true,"Rectangle");
        }
        else{
            Vec2 size(1,1);
            createNode(geometry_node,"size", QString::fromStdString(size.vec2ToString()),EDITABLE,false,"Rectangle");
        }

        // option--Cylinder
        if(current_geometry_type == kGeometryCylinder)
        {
            QVariant height = geometry_ptr->getPara(toMemberName("height"));
            createNode(geometry_node,"height", height,EDITABLE,true,"Cylinder");
            QVariant radius = geometry_ptr->getPara(toMemberName("radius"));
            createNode(geometry_node,"radius", radius,EDITABLE,true,"Cylinder");
        }
        else{
            QVariant height = 1 ;
            createNode(geometry_node,"height", height,EDITABLE,false,"Cylinder");
            QVariant radius = 1 ;
            createNode(geometry_node,"radius", radius,EDITABLE,false,"Cylinder");
        }

        // option--MultiPanelComprisedOfHeatTube
        if(current_geometry_type == kGeometryCylinder)
        {
            QVariant height = geometry_ptr->getPara(toMemberName("height"));
            createNode(geometry_node,"height", height,EDITABLE,true,"Cylinder");
            QVariant radius = geometry_ptr->getPara(toMemberName("radius"));
            createNode(geometry_node,"radius", radius,EDITABLE,true,"Cylinder");
        }
        else{
            QVariant height = 1 ;
            createNode(geometry_node,"height", height,EDITABLE,false,"Cylinder");
            QVariant radius = 1 ;
            createNode(geometry_node,"radius", radius,EDITABLE,false,"Cylinder");
        }

        auto material_ptr = receiver->getPara(toMemberName("material")).value<std::shared_ptr<Material>>();
        // MaterialType current_material_type = material_ptr->getType();
        QString current_material_option = "Absorb";
        auto material_node = createNode(root_node,"material",current_material_option);  //!!!因为只有一个选项，因此设置为不可选也不可编辑
        QVariant absorptivity = material_ptr->getPara(toMemberName("absorptivity"));
        createNode(material_node, "absorptivity",absorptivity,EDITABLE);

    }


    void ParaTreeModel::buildOrdinaryTreeModel(QSharedPointer<Ordinary> ordinary)
    {
        auto geometry_ptr = ordinary->getPara(toMemberName("geometry")).value<std::shared_ptr<Geometry>>();
        GeometryType current_geometry_type = geometry_ptr->getType();
        QString current_geometry_option = "";
        switch(current_geometry_type)
        {
            case kGeometryCylinder: current_geometry_option="Cylinder"; break;
        }
        auto geometry_node = createNode(root_node,"geometry",current_geometry_option,OPTIONAL); 
        QList<QString> geometry_options;
        geometry_options.append("Cylinder");
        geometry_node->initOptions(geometry_options);

        // option--Cylinder
        if(current_geometry_type == kGeometryCylinder)
        {
            QVariant height = geometry_ptr->getPara(toMemberName("height"));
            createNode(geometry_node,"height", height,EDITABLE,true,"Cylinder");
            QVariant radius = geometry_ptr->getPara(toMemberName("radius"));
            createNode(geometry_node,"radius", radius,EDITABLE,true,"Cylinder");
        }
        else{
            QVariant height = 1 ;
            createNode(geometry_node,"height", height,EDITABLE,false,"Cylinder");
            QVariant radius = 1 ;
            createNode(geometry_node,"radius", radius,EDITABLE,false,"Cylinder");
        }

    }

    /*
------------------------------------------------------------------------------
*/

    auto ParaTreeModel::columnCount(const QModelIndex& parent) const -> int // 返回列数
    {
        return 2;
    }
    auto ParaTreeModel::rowCount(const QModelIndex& parent) const -> int // 返回孩子节点的个数
    {
        int ret = 0;
        // QModelIndex代表的是一个Item，不是一个Row
        if (parent.column() >
            0) // 这里是因为所有的孩子节点都是放在column=0上面的，当column>0时，默认是没有节点的
        {
            //qDebug() << "1111 " << parent.column();
            return 0;
        }

        if (!parent.isValid())
        {
            //qDebug() << "2222";
            ret = root_node->childCount();
        }
        else
        {
            //qDebug() << "3333";
            // 这里使用普通指针
            auto* parent_node = static_cast<ParaTreeNode*>(parent.internalPointer());
            ret = parent_node->childCount();
        }

        return ret;
    }
    auto ParaTreeModel::roleNames() const -> QHash<int, QByteArray> { return this->role_names_; }
    auto ParaTreeModel::data(const QModelIndex& index, int role) const -> QVariant
    {
        if (!index.isValid())
        {
            return {};
        }

        switch (role)
        {
        case NAME:
        {
            return static_cast<ParaTreeNode*>(index.internalPointer())->data(0);
        }
        case PARA:
        {
            return static_cast<ParaTreeNode*>(index.internalPointer())->data(1);
        }
        
        }
        return {};
    }
    auto ParaTreeModel::flags(const QModelIndex& index) const -> Qt::ItemFlags
    {
        if (!index.isValid())
        {
            return Qt::NoItemFlags;
        }

        return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
    }
    auto ParaTreeModel::index(int row, int column, const QModelIndex& parent) const -> QModelIndex
    {
        if (!hasIndex(row, column, parent))
        {
            return {};
        }

        ParaTreeNode* parent_node = nullptr;
        if (!parent.isValid())
        {
            parent_node = root_node.get();
        }
        else
        {
            parent_node = static_cast<ParaTreeNode*>(parent.internalPointer());
        }

        ParaTreeNode* child_node = (parent_node->child(row)).get();
        if (child_node != nullptr)
        {
            return createIndex(row, column, child_node);
        }

        return {};
    }
    auto ParaTreeModel::parent(const QModelIndex& index) const -> QModelIndex
    {
        if (!index.isValid())
        {
            return {};
        }

        auto* child_node = static_cast<ParaTreeNode*>(index.internalPointer());
        auto parent_node = child_node->parent();

        if (parent_node == root_node)
        {
            return {};
        }
        // !!!!!注意一下，这里的row()是否能返回正确的值
        return createIndex(parent_node->row(), 0, parent_node.get());
    }
/**
 * ===========================set Node Para============================================
*/

    // ！！！！！！！！注意：不要忘记更新para中的内容！！！！！
    // ！！！！！！！问题：：para中记录的属性如何更新？？？如果是editable，直接setPara即可，如果是optional，如何做？？？
    /**
     * ！！！！！！！需要修改
    */
    void ParaTreeModel::setNodePara(QModelIndex index,
                                    QVariant value) // 设置index这一节点的属性数据为value
    {
        if (!index.isValid())
        {
            return;
        }
        // 隐约记得，这里如果用的是智能指针，不能往下传到其他的函数，试一下
        auto* click_node = static_cast<ParaTreeNode*>(index.internalPointer());
        // QString para_name = click_node->data(0).toString();
        qDebug()<<"*******click_node = "<<click_node->data(0)<<", "<<click_node->data(1);
        /**
         * 先switch state
        */
       int click_node_state = click_node->getState();
        qDebug()<<"*******click_node_state = "<< click_node_state;


       switch(click_node_state)
       {

        case OPTIONAL:
        {
            qDebug() <<"---------print info of the option node-----------";
             printIndexInfo(index);
            click_node->printAllOptionChild();
            qDebug() << "click OPTIONAL 选中的选项为：" << value.toString();

            makeChoice(index, value.toString()); // !!!!在该函数中进行选择和发送信号

            printIndexInfo(index);
            click_node->printAllOptionChild();
            break;
        }

        case EDITABLE:
        {
            qDebug() <<"---------print info of the editable node-----------";
            printIndexInfo(index);
            
            //先更新para指针中的内容
            // std::string name = click_node->data(0).toString().toStdString();
            // para->setPara(name,value);          //---不能直接这样设置，
            updatePara(index,value);
            // 再处理树状视图的节点中对应的数据
            click_node->setData(value,1);    
            printIndexInfo(index);

            break;
        }
       }

        // // 进行编辑
        // // 若该节点是可编辑的，只更改这一个节点的para，并发送信号
        // if (click_node->getState() == EDITABLE)
        // {
        //     click_node->setData(value, 1);
        //     auto para_property_type = click_node->data(0).toString().toStdString();

        //     /**
        //      * 这样写真的很奇怪！！！！
        //      * 
        //     */
        //     if (this->model_type == SUN)
        //     {
        //         if (this->sun_position_keys.contains(para_property_type))    //!!!是否包含这部分，可以放在sun里实现吗？？？
        //         {
        //             auto sun_position_ptr = para->getPara(toMemberName("sun_position"))
        //                                         .value<std::shared_ptr<SunPosition>>();
        //             sun_position_ptr->setPara(toMemberName(para_property_type), value);
        //         }
        //         else
        //         {
        //             auto sun_shape_ptr =
        //                 para->getPara(toMemberName("sunshape")).value<std::shared_ptr<SunShape>>();
        //             sun_shape_ptr->setPara(value.toDouble());
        //         }
        //     }
        //     else
        //     {
        //         para->setPara(toMemberName(para_property_type), value);
        //     }

        //     // qDebug() << "\t para的参数是否更改？新的参数为:"
        //     //          << para->getPara(toMemberName(para_property_type));
        //     // para->setPara(para_name.toStdString(),value);   // !!!!这里有问题
        //     emit dataChanged(index, index);
        // }

        // // 进行选择
        // //  !!!!注意进行makechoice时，要看value是否在选项内
        // if (click_node->getState() ==
        //     OPTIONAL) // 该节点是可选择的，需要做出选择，并发送信号！！！！！发送信号的地方好像有bug
        // {
        //     qDebug() << "click OPTIONAL 选中的选项为：" << value.toString();
        //     makeChoice(index, value.toString()); // 在该函数中进行选择和发送信号
        //     // para->setPara(para_name.toStdString(), value);
        // }
    }

    /**
     * 这里单独设置一系列函数去改para是因为，有些存的是指针，不能直接para->setPara
     * 需要先获得指针指向的对象，再对这个对象进行setpara
    */
    void ParaTreeModel::updatePara(QModelIndex index, QVariant value)
    {
        switch(this->model_type)
        {
            case SUN:       updataSunPara(index,value);    break;
            case LOCATION:  updataLocationPara(index,value);    break;
            case AIR:       updataAirPara(index,value);    break;
            case CAMERA:    updataCameraPara(index,value);    break;
            case TERRAIN:   updataTerrainPara(index,value);    break;
            case CLOUD:     updataCloudPara(index,value);    break;
            case NODE:      updataNodePara(index,value);    break;
            case HELIOSTAT: updataHeliostatPara(index,value);    break;
            case RECEIVER:  updataReceiverPara(index,value);    break;
            case ORDINARY:  updataOrdinaryPara(index,value);    break;
            
        }
    }
    void ParaTreeModel::updataSunPara(QModelIndex index, QVariant value)
    {
        auto* click_node = static_cast<ParaTreeNode*>(index.internalPointer());
        std::string name = click_node->data(0).toString().toStdString();
        auto sun = para.dynamicCast<Sun>();
        if(name == "csr" || name == "sigma" || name == "theta_max")
        {
            auto sun_position_ptr =
            sun->getPara(toMemberName("sun_position")).value<std::shared_ptr<SunPosition>>();
            sun_position_ptr->setPara(toMemberName(name),value);
        }
        else{
            auto sun_shape_ptr =
            sun->getPara(toMemberName("sun_shape")).value<std::shared_ptr<SunShape>>();
            sun_shape_ptr->setPara(value.toDouble());
        }
        
    }
    void ParaTreeModel::updataLocationPara(QModelIndex index, QVariant value)
    {
        auto* click_node = static_cast<ParaTreeNode*>(index.internalPointer());
        std::string name = click_node->data(0).toString().toStdString();
        para->setPara(toMemberName(name),value);
    }
    void ParaTreeModel::updataAirPara(QModelIndex index, QVariant value)
    {
        auto* click_node = static_cast<ParaTreeNode*>(index.internalPointer());
        std::string name = click_node->data(0).toString().toStdString();
        auto air = para.dynamicCast<Air>();
        if(name == "beta")
        {
            auto attenuation_ptr = air->getPara(toMemberName("attenuation")).value<std::shared_ptr<Attenuation>>();
            attenuation_ptr->setPara(value.toDouble());
        }
    }
    void ParaTreeModel::updataCameraPara(QModelIndex index, QVariant value)
    {
        auto* click_node = static_cast<ParaTreeNode*>(index.internalPointer());
        std::string name = click_node->data(0).toString().toStdString();
        auto camera = para.dynamicCast<Camera>();
        para->setPara(toMemberName(name),value);
        // if(name == "position" || name =="perspective")
        // {
        //     para->setPara(name,value);
        // }
        // else{
        //     auto rotation = para.dynamicCast<Camera>()->getPara(toMemberName("rotation")).value<Rotation>();
        //     rotation.setPara(toMemberName(name),value);
        // }
        auto property = para->getPara(toMemberName(name)).value<Rotation>();
        qDebug()<<"==============alter camera rotation====";
        qDebug()<<"value = "<<value <<"  name = "<< QString::fromStdString(name);
        qDebug() <<"camera = ";     camera->testPrint();
        
        property.testPrint();
        // property.testprint();
    }
    void ParaTreeModel::updataTerrainPara(QModelIndex index, QVariant value)
    {
        auto* click_node = static_cast<ParaTreeNode*>(index.internalPointer());
        std::string name = click_node->data(0).toString().toStdString();
        para->setPara(name,value);
    }
    void ParaTreeModel::updataCloudPara(QModelIndex index, QVariant value)
    {
        auto* click_node = static_cast<ParaTreeNode*>(index.internalPointer());
        std::string name = click_node->data(0).toString().toStdString();
        para->setPara(name,value);
    }
    void ParaTreeModel::updataNodePara(QModelIndex index, QVariant value)
    {
        auto* click_node = static_cast<ParaTreeNode*>(index.internalPointer());
        std::string name = click_node->data(0).toString().toStdString();
        para->setPara(toMemberName(name),value);
    }
    void ParaTreeModel::updataHeliostatPara(QModelIndex index, QVariant value)
    {
        auto* click_node = static_cast<ParaTreeNode*>(index.internalPointer());
        std::string name = click_node->data(0).toString().toStdString();
        para->setPara(name,value);
    }
    void ParaTreeModel::updataReceiverPara(QModelIndex index, QVariant value)
    {
        auto* click_node = static_cast<ParaTreeNode*>(index.internalPointer());
        std::string name = click_node->data(0).toString().toStdString();
        para->setPara(name,value);
    }
    void ParaTreeModel::updataOrdinaryPara(QModelIndex index, QVariant value)
    {
        auto* click_node = static_cast<ParaTreeNode*>(index.internalPointer());
        std::string name = click_node->data(0).toString().toStdString();
        para->setPara(name,value);
    }

/**
 * ------------------------------------------------------------
*/
    auto ParaTreeModel::getNodePara(const QModelIndex& index)
        -> QString // 获取index这一节点的para数据
    {
        if (!index.isValid())
        {
            return "";
        }
        auto* current_node = static_cast<ParaTreeNode*>(index.internalPointer());
        QVariant para_data = current_node->data(1);
        return para_data.toString();
    }

    auto ParaTreeModel::isNodeEditable(const QModelIndex& index) -> bool
    {
        if (!index.isValid())
        {
            return false;
        }
        auto* current_node = static_cast<ParaTreeNode*>(index.internalPointer());
        ParaState para_state = current_node->getState();
        return para_state == EDITABLE;
    }
    auto ParaTreeModel::isNodeOptional(const QModelIndex& index) -> bool
    {
        if (!index.isValid())
        {
            return false;
        }
        auto* current_node = static_cast<ParaTreeNode*>(index.internalPointer());
        ParaState para_state = current_node->getState();
        return para_state == OPTIONAL;
    }

    auto ParaTreeModel::getNodeOptionList(const QModelIndex& index) -> QList<QString>
    {
        if (!index.isValid())
        {
            return {};
        }
        auto* current_node = static_cast<ParaTreeNode*>(index.internalPointer());
        return current_node->getOptions();
    }
    void ParaTreeModel::makeChoice(const QModelIndex& index, const QString& option) // 做出选择
    {
        if (!index.isValid())
        {
            return;
        }
        auto* click_node = static_cast<ParaTreeNode*>(index.internalPointer());

        // 首先，改变该节点的选项
        click_node->setData(option, 1);
        emit dataChanged(index, index);

        //测试输出click_node所有选项以及所有选项孩子


        
        int parent_row = index.row();
        if (click_node->childCount() != 0)
        {
            //qDebug() << "click_node->childCount(): " << click_node->childCount();
            
            int first_row = parent_row + 1;
            int count = click_node->childCount();
            removeRows(0,count,index);
            //int last_row = parent_row + 1 + click_node->childCount() - 1;
            //qDebug() << "parent_row: " << parent_row;
            //qDebug() << "first_row: " << first_row << " last_row: " << last_row << " "
             //        << rowCount(index);

            // ？？？？？并没有发出信号
            // QList<QPersistentModelIndex> temp_list;
            // temp_list.append(index);
            // beginRemoveRows(index, first_row, last_row);
            
            // click_node->deleteAllChild();
            // //removeRow(first_row,index);
            // // emit layoutChanged(temp_list);
            // //emit rowsAboutToBeRemoved(index,first_row,last_row);
            // endRemoveRows();


            //        click_node->deleteAllChild();
            //        bool ret = removeRows(index.row(),click_node->childCount(),index);
            //        //要重写这个函数才能用 qDebug()<<ret;
        }
        

        // if (click_node->childCount() != 0)
        // { // 先删除所有子节点
        //     beginRemoveRows(index, 0, click_node->childCount() - 1);
        //     click_node->deleteAllChild();
        //     endRemoveRows();
        // }

        // 把选项的孩子列表添加到节点的孩子列表中
        auto current_option_childnodes = click_node->getOptionChilds(option);
        int count = current_option_childnodes.size();
        int first_row = parent_row + 1;
        int last_row = parent_row + 1 + count-1;
        qDebug() <<"----count = "<<count;
        //insertRows(0,count,index);
           //beginInsertRows(index,click_node->childCount(), click_node->childCount() + count-1);
        // beginInsertRows(index,first_row, last_row);

        // for(int i=0;i<count;i++)
        // {
        //     click_node->appendChild(current_option_childnodes[i]);
        // }
        // endInsertRows();
    }

    bool ParaTreeModel::removeRows(int row, int count, const QModelIndex &parent )
    {
        auto* click_node = static_cast<ParaTreeNode*>(parent.internalPointer());
        /*
            注意：文档里说begin和end这一对函数会发送rowsAbouttoRemoved的信号，然后会自动更新界面
                但是实际上，需要进行一次收缩、展开节点才会更新界面-----似乎是qml的问题
            解决：选中选项后，自动进行界面更新
                在ParaTreeView.qml文件内，选中选项后，用命令进行节点的收缩和展开
            （insertRows中也是一样的情况）
        */
        beginRemoveRows(parent,row,row+count-1);    
        click_node->deleteAllChild();
        endRemoveRows();
        return true;
    }
    bool ParaTreeModel::insertRows(int row, int count, const QModelIndex &parent )
    {
        auto* click_node = static_cast<ParaTreeNode*>(parent.internalPointer());
        QString option = click_node->data(1).toString();
        auto current_option_childnodes = click_node->getOptionChilds(option);

        //beginInsertRows(parent,row,row+count-1);
        beginInsertRows(parent,0,0);

        for(int i=0;i<count;i++)
        {
            click_node->appendChild(current_option_childnodes[i]);
        }
        endInsertRows();
        return true;
    }

    auto ParaTreeModel::getCurrentOptionId(const QModelIndex& index) -> int
    {
        if (!index.isValid())
        {
            return -1;
        }
        auto* click_node = static_cast<ParaTreeNode*>(index.internalPointer());
        return click_node->getCurrentOptionId();
    }


    void ParaTreeModel::setLabelTxt(QString label_txt)
    {
        this->label_txt = label_txt;
    }
    QString ParaTreeModel::getLabelTxt()
    {
        qDebug() << "HINT::ParaTreeModel::getLabelTxt::label_txt = "<<label_txt;
        return label_txt;
    }


    void ParaTreeModel::printIndexInfo(QModelIndex index)
    {
        auto* click_node = static_cast<ParaTreeNode*>(index.internalPointer());
        qDebug() <<"------index: row = "<<index.row();
        click_node->printInfo();
    }

} // namespace solar
