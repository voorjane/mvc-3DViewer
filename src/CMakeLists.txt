cmake_minimum_required(VERSION 3.5)
project(3DViewer VERSION 2.0 LANGUAGES CXX C)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets OpenGLWidgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets OpenGLWidgets)

set(PROJECT_SOURCES
        Controller/controller.cc
        Controller/controller.h
        Model/QtGifImage/gifimage/qgifglobal.h
        Model/QtGifImage/gifimage/qgifimage.cc
        Model/QtGifImage/gifimage/qgifimage.h
        Model/QtGifImage/gifimage/qgifimage_p.h
        Model/QtGifImage/giflib/dgif_lib.c
        Model/QtGifImage/giflib/egif_lib.c
        Model/QtGifImage/giflib/gif_err.c
        Model/QtGifImage/giflib/gif_font.c
        Model/QtGifImage/giflib/gif_hash.c
        Model/QtGifImage/giflib/gif_hash.h
        Model/QtGifImage/giflib/gif_lib.h
        Model/QtGifImage/giflib/gif_lib_private.h
        Model/QtGifImage/giflib/gifalloc.c
        Model/QtGifImage/giflib/quantize.c
        Model/myglwidget.cc
        Model/myglwidget.h
        Model/objparser.cc
        Model/objparser.h
        Model/settings.cc
        Model/settings.h
        Model/transformation.cc
        Model/transformation.h
        View/mainwindow.cc
        View/mainwindow.h
        View/mainwindow.ui
        View/main.cc

)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(3DViewer
            MANUAL_FINALIZATION
            ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(3DViewer SHARED
                ${PROJECT_SOURCES}
        )
    else()
        add_executable(3DViewer
                ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(3DViewer PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(3DViewer PRIVATE Qt${QT_VERSION_MAJOR}::OpenGLWidgets)

set_target_properties(3DViewer PROPERTIES
        MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
        MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
        MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
        MACOSX_BUNDLE TRUE
        WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(3DViewer)
endif()
