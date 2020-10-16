cmake_minimum_required(VERSION 3.5)

project(HEPDesigner LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check http://doc.qt.io/qt-5/deployment-android.html for more information.
# They need to be set before the find_package(Qt5 ...) call.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets PrintSupport REQUIRED)
add_executable(HEPDesigner
    src/main.cpp
    src/mainwindow.cpp
    src/mainwindow.h
    src/mainwindow.ui
    src/exercise.cpp
    src/exercise.h
    src/exercise_layout.cpp
    src/exercise_layout.h
    src/routine_layout.cpp
    src/routine_layout.h
    src/tooltip.h
    src/tooltip.cpp
    src/preview_window.cpp
    src/preview_window.h
    src/previewwindow.ui
    src/exercise_card.cpp
    src/exercise_card.h
    src/exercisecard.ui
    src/print_card.cpp
    src/print_card.h
    src/printcard.ui
    src/save_routine_window.cpp
    src/save_routine_window.h
    src/saveroutinewindow.ui
    src/load_routine_window.cpp
    src/load_routine_window.h
    src/loadroutinewindow.ui
    src/add_exercise_window.cpp
    src/add_exercise_window.h
    src/addexercisewindow.ui
    src/add_tags_window.cpp
    src/add_tags_window.h
    src/addtagswindow.ui
    src/tag_search_area.cpp
    src/tag_search_area.h
)


target_link_libraries(HEPDesigner PRIVATE Qt${QT_VERSION_MAJOR}::Widgets
    Qt5::PrintSupport
    )
