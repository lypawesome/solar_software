

cmake_minimum_required(VERSION 3.16)

project(solar_2 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTORCC ON) # 这一句如果不加的话，使用不了qrc下的相对路径
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--stack,999999")
string(TOUPPER "${CMAKE_BUILD_TYPE}" CMAKE_BUILD_TYPE_UPPER)
set(CMAKE_CXX_FLAGS_BUILD_TYPE "CMAKE_CXX_FLAGS_${CMAKE_BUILD_TYPE_UPPER}")
set(TRY_COMPILE_STD_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${${CMAKE_CXX_FLAGS_BUILD_TYPE}}")

try_compile(
    HAVE_MSVC_STL
    "${CMAKE_SOURCE_DIR}/cmake"
    "${CMAKE_SOURCE_DIR}/cmake/try_compile_msvc_stl.cpp"
    COMPILE_DEFINITIONS "${TRY_COMPILE_STD_CXX_FLAGS}"
    OUTPUT_VARIABLE TRY_COMPILE_OUTPUT
)

try_compile(
    HAVE_LIBCXX
    "${CMAKE_SOURCE_DIR}/cmake"
    "${CMAKE_SOURCE_DIR}/cmake/try_compile_libcxx.cpp"
    COMPILE_DEFINITIONS "${TRY_COMPILE_STD_CXX_FLAGS}"
    OUTPUT_VARIABLE TRY_COMPILE_OUTPUT
)

try_compile(
    HAVE_LIBSTDCXX
    "${CMAKE_SOURCE_DIR}/cmake"
    "${CMAKE_SOURCE_DIR}/cmake/try_compile_libstdc++.cpp"
    COMPILE_DEFINITIONS "${TRY_COMPILE_STD_CXX_FLAGS}"
    OUTPUT_VARIABLE TRY_COMPILE_OUTPUT
)

set(STD_FORMAT_EXTRA_FLAGS "")

if(HAVE_MSVC_STL)
    message(STATUS "Using MSVC STL")
endif()
if(HAVE_LIBCXX)
    message(STATUS "Using LLVM libc++")
    set(STD_FORMAT_EXTRA_FLAGS "-D_LIBCPP_ENABLE_EXPERIMENTAL")
endif()
if(HAVE_LIBSTDCXX)
    message(STATUS "Using GNU libstdc++")
endif()
if(NOT (HAVE_MSVC_STL OR HAVE_LIBCXX OR HAVE_LIBSTDCXX))
    message(WARNING "Unknown Standard C++ Library")
endif()

# libc++ (Clang's C++ Library 需要-D_LIBCPP_ENABLE_EXPERIMENTAL来启用std::format)
# MSVC 无需额外设置
# GCC/G++的libstdc++没测试过，不知道是否需要额外的宏定义，可补充
set(TRY_COMPILE_STD_FORMAT_CXX_FLAGS "${TRY_COMPILE_STD_CXX_FLAGS} ${STD_FORMAT_EXTRA_FLAGS}")

try_compile(
    HAVE_STD_FORMAT
    "${CMAKE_SOURCE_DIR}/cmake"
    "${CMAKE_SOURCE_DIR}/cmake/try_compile_std_format.cpp"
    COMPILE_DEFINITIONS "${TRY_COMPILE_STD_FORMAT_CXX_FLAGS}"
    OUTPUT_VARIABLE TRY_COMPILE_OUTPUT
)

message(STATUS "HAVE_STD_FORMAT: ${HAVE_STD_FORMAT}")

add_subdirectory("third_party/vectorclass2")

# set(CMAKE_MODULE_PATH /home/liu/Qt/6.4.3)
list(APPEND CMAKE_PREFIX_PATH /home/liu/Qt/6.4.3/gcc_64/lib/cmake)

# 手动把qt6.4.3的目录添加进去
message("cmake_module_path: " ${CMAKE_MODULE_PATH})
find_package(Qt6 6.4 REQUIRED COMPONENTS Quick)
find_package(Boost REQUIRED)

string(REGEX REPLACE "/include.*$" "" Boost_ROOT ${Boost_INCLUDE_DIRS})
set(Boost_LIBRARY_DIR "${Boost_ROOT}/lib" CACHE PATH "${Boost_ROOT}/lib")

# add_subdirectory(source)
qt_standard_project_setup()

# file(GLOB_RECURSE native_srcs source/*.cpp source/*.h)
file(GLOB_RECURSE native_srcs source/*.cpp source/*.h)
qt_add_executable(appsolar_2

    qml.qrc

    src/main.cpp

    ${native_srcs}

    # source/utils/Vec3.h
    # source/utils/Vec3.cpp
    # source/utils/Vec2.h
    # source/utils/Vec2.cpp
    # source/utils/Utils.h

    # include/Para.h src/Para.cpp
    # include/TopoTreeNode.h src/TopoTreeNode.cpp
    # include/TopoTreeModel.h src/TopoTreeModel.cpp
    # include/TopoTreeViewController.h src/TopoTreeViewController.cpp

    # include/ParaTreeNode.h src/ParaTreeNode.cpp
    # include/ParaTreeModel.h src/ParaTreeModel.cpp
    # include/ParaTreeViewController.h src/ParaTreeViewController.cpp

    # include/Scene.h src/Scene.cpp

    # include/Grid.h src/Grid.cpp

    # include/SunShape.h  src/SunShape.cpp
    # include/SunPosition.h   src/SunPosition.cpp
    # include/Attenuation.h   src/Attenuation.cpp
    # include/Rotation.h  src/Rotation.cpp
    # include/Geometry.h   src/Geometry.cpp
    # include/Profile.h src/Profile.cpp
    # include/Material.h  src/Material.cpp
    # #include/MaterialRT.h    src/MaterialRT.cpp

    # #include/Ray.h src/Ray.cpp
    # include/SlopeError.h src/SlopeError.cpp

    # source/topology/tracker/Armature.h
    # source/topology/tracker/Armature.cpp
    # source/topology/tracker/OneAxisArmature.h
    # source/topology/tracker/OneAxisArmature.cpp
    # source/topology/tracker/TwoAxisArmature.h
    # source/topology/tracker/TwoAxisArmature.cpp
    # source/topology/tracker/TwoAxisWithDrivesArmature.h
    # source/topology/tracker/TwoAxisWithDrivesArmature.cpp

    # include/Target.h src/Target.cpp
    # #include/HeatTubePlane.h src/HeatTubePlane.cpp
    # include/HeatTubePaneReceiver.h src/HeatTubePaneReceiver.cpp

    # include/Tracker.h  src/Tracker.cpp
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

# file(GLOB_RECURSE native_includes source/topology/*.h)
# add_library(DIR_INCLUDE SHARED ${native_includes})
# target_link_libraries(
# appsolar_2 PRIVATE DIR_INCLUDE
# )

# file(GLOB_RECURSE native_srcs source/*.cpp source/*.h)
# add_library(DIR_SRC_ SHARED ${native_srcs})
# target_link_libraries(
# appsolar_2 PRIVATE DIR_SRC
# )
target_link_libraries(appsolar_2 PRIVATE VectorClass2)
target_include_directories(appsolar_2 PRIVATE "include")
target_include_directories(appsolar_2 PRIVATE "source")
target_include_directories(appsolar_2 PUBLIC ${Boost_INCLUDE_DIRS})
target_link_directories(appsolar_2 PRIVATE ${Boost_LIBRARY_DIR})

if(HAVE_STD_FORMAT)
    target_compile_definitions(appsolar_2 PRIVATE "HAVE_STD_FORMAT")
    target_compile_options(appsolar_2 PRIVATE "${STD_FORMAT_EXTRA_FLAGS}")
else()
    find_package(fmt REQUIRED)
    target_link_libraries(appsolar_2 PRIVATE fmt::fmt)
endif()

target_link_libraries(appsolar_2
    PRIVATE Qt6::Quick
)

install(TARGETS appsolar_2
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
