

cmake_minimum_required(VERSION 3.16)

project(solar_2 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTORCC ON)                           #这一句如果不加的话，使用不了qrc下的相对路径
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--stack,999999")

add_subdirectory("third_party/vectorclass2")

#set(CMAKE_MODULE_PATH /home/liu/Qt/6.4.3)
list(APPEND CMAKE_PREFIX_PATH /home/liu/Qt/6.4.3/gcc_64/lib/cmake)
#手动把qt6.4.3的目录添加进去
message("cmake_module_path: " ${CMAKE_MODULE_PATH})
find_package(Qt6 6.4 REQUIRED COMPONENTS Quick)

qt_standard_project_setup()

qt_add_executable(appsolar_2

    qml.qrc

    src/main.cpp

    include/Vec3.h src/Vec3.cpp
    include/Vec2.h src/Vec2.cpp

    include/Utils.h

    include/Para.h src/Para.cpp
    include/TopoTreeNode.h src/TopoTreeNode.cpp
    include/TopoTreeModel.h src/TopoTreeModel.cpp
    include/TopoTreeViewController.h src/TopoTreeViewController.cpp

    include/ParaTreeNode.h src/ParaTreeNode.cpp
    include/ParaTreeModel.h src/ParaTreeModel.cpp
    include/ParaTreeViewController.h src/ParaTreeViewController.cpp

    include/Scene.h src/Scene.cpp


    include/Grid.h src/Grid.cpp

    include/SunShape.h  src/SunShape.cpp
    include/SunPosition.h   src/SunPosition.cpp
    include/Attenuation.h   src/Attenuation.cpp
    include/Rotation.h  src/Rotation.cpp
    include/Geometry.h   src/Geometry.cpp
    include/Profile.h src/Profile.cpp
    include/Material.h  src/Material.cpp
    #include/MaterialRT.h    src/MaterialRT.cpp

    #include/Ray.h src/Ray.cpp
    include/SlopeError.h src/SlopeError.cpp

    include/Armature.h src/Armature.cpp
    include/Target.h src/Target.cpp
    #include/HeatTubePlane.h src/HeatTubePlane.cpp
    include/HeatTubePaneReceiver.h src/HeatTubePaneReceiver.cpp
)

qt_add_qml_module(appsolar_2
    URI solar_2
    VERSION 1.0
    QML_FILES Main.qml
    QML_FILES MyRect_World.qml
    QML_FILES MyRect_Topology.qml
    QML_FILES TopoTreeView.qml
    QML_FILES ParaTreeView.qml
    QML_FILES RayTracingWindow.qml
    QML_FILES AnalyticFunctionWindow.qml
    QML_FILES DataVisualizationWindow.qml
)

set_target_properties(appsolar_2 PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appsolar_2 PRIVATE VectorClass2)
target_include_directories(appsolar_2 PRIVATE "include")

target_link_libraries(appsolar_2
    PRIVATE Qt6::Quick
)


install(TARGETS appsolar_2
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
