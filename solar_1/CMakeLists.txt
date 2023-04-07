cmake_minimum_required(VERSION 3.16)

project(solar_1 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory("third_party/vectorclass2")

find_package(Qt6 6.4 REQUIRED COMPONENTS Quick)

qt_standard_project_setup()

qt_add_executable(appsolar_1

    src/main.cpp
    qml.qrc

    include/Utils.h
    include/Vec3.h
    src/Vec3.cpp

    include/TreeNode.h
    src/TreeNode.cpp
    include/TreeModel.h
    src/TreeModel.cpp
    include/ParaTreeViewController.h
    src/ParaTreeViewController.cpp
    include/TopoTreeViewController.h
    src/TopoTreeViewController.cpp

    include/Para.h
    src/Para.cpp

    include/SunShape.h
    src/SunShape.cpp

    include/Scene.h
    src/Scene.cpp


    resource.qrc
)

qt_add_qml_module(appsolar_1
    URI solar_1
    VERSION 1.0

    QML_FILES Main.qml

    QML_FILES MyRect_World.qml
    QML_FILES MyRect_Topology.qml

    QML_FILES TopoTreeView.qml
    QML_FILES ParaTreeView.qml
)



set_target_properties(appsolar_1 PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appsolar_1 PRIVATE VectorClass2)
target_include_directories(appsolar_1 PRIVATE "include")

target_link_libraries(appsolar_1
    PRIVATE Qt6::Quick
)

install(TARGETS appsolar_1
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
