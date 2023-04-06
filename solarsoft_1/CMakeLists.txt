cmake_minimum_required(VERSION 3.14)

project(solarsoft_1 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory("third_party/vectorclass2")

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Quick)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Quick)

if(QT_VERSION_MAJOR EQUAL 6)
    find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core5Compat)
endif()

if(MSVC)
    option(GENERATE_DEBUG_INFO "Create debug info, useful for debugging" ON)

    if(GENERATE_DEBUG_INFO)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Z7")
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /DEBUG /OPT:REF /OPT:ICF")
        set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} /DEBUG /OPT:REF /OPT:ICF")
        set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} /DEBUG /OPT:REF /OPT:ICF")
    endif(GENERATE_DEBUG_INFO)
endif(MSVC)

set(PROJECT_SOURCES
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

        #WorldPara.h
        #WorldPara.cpp
        include/SunShape.h
        src/SunShape.cpp

        #TopoPara.h
        #TopoPara.cpp

        include/Scene.h
        src/Scene.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(solarsoft_1
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET solarsoft_1 APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(solarsoft_1 SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(solarsoft_1
          ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(solarsoft_1
  PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick)

if(QT_VERSION_MAJOR EQUAL 6)
    target_link_libraries(solarsoft_1
        PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Core5Compat)
endif()

if (MSVC)
    target_compile_options(solarsoft_1 PRIVATE "/arch:AVX2")
else()
    target_compile_options(solarsoft_1 PRIVATE "-mavx2" "-mfma")
endif()
target_link_libraries(solarsoft_1 PRIVATE VectorClass2)
target_include_directories(solarsoft_1 PRIVATE "include")

set_target_properties(solarsoft_1 PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS solarsoft_1
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_import_qml_plugins(solarsoft_1)
    qt_finalize_executable(solarsoft_1)
endif()
