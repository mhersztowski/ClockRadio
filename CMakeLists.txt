cmake_minimum_required(VERSION 3.5)

project(ClockRadio VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Network Multimedia WebEngineWidgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Network Multimedia WebEngineWidgets )

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        QClock.h
        QClock.cpp
        QDigitClock.h
        QDigitClock.cpp
        QSoundSource.h
        QSoundSource.cpp
        logview.h
        logview.cpp
        resource.qrc
)

if(WIN32)
    link_directories(${CMAKE_SOURCE_DIR}/ext/ffmpeg/bin)
endif()


if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(ClockRadio
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET ClockRadio APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(ClockRadio SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(ClockRadio
            ${PROJECT_SOURCES}
        )
    endif()
endif()

if(WIN32)
    target_link_libraries(ClockRadio PRIVATE avcodec avformat avutil swresample)
    include_directories(${CMAKE_SOURCE_DIR}/ext/ffmpeg/include)
endif()

if(ANDROID)
    add_library(avcodec SHARED IMPORTED)
    set_target_properties(avcodec PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/ext/ffmpeg-android/arm64-v8a/lib/libavcodec.so)

    add_library(avformat SHARED IMPORTED)
    set_target_properties(avformat PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/ext/ffmpeg-android/arm64-v8a/lib/libavformat.so)

    add_library(avutil SHARED IMPORTED)
    set_target_properties(avutil PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/ext/ffmpeg-android/arm64-v8a/lib/libavutil.so)

    add_library(swresample SHARED IMPORTED)
    set_target_properties(swresample PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/ext/ffmpeg-android/arm64-v8a/lib/libswresample.so)

    include_directories(${CMAKE_SOURCE_DIR}/ext/ffmpeg-android/arm64-v8a/include)

    target_link_libraries(ClockRadio PRIVATE avcodec avformat avutil swresample)

    set(ANDROID_EXTRA_LIBS
            ${CMAKE_SOURCE_DIR}/ext/ffmpeg-android/arm64-v8a/lib/libavcodec.so
            ${CMAKE_SOURCE_DIR}/ext/ffmpeg-android/arm64-v8a/lib/libavformat.so
            ${CMAKE_SOURCE_DIR}/ext/ffmpeg-android/arm64-v8a/lib/libavutil.so
            ${CMAKE_SOURCE_DIR}/ext/ffmpeg-android/arm64-v8a/lib/libswresample.so
            CACHE INTERNAL "")

    set_target_properties(${PROJECT_NAME} PROPERTIES
        QT_ANDROID_EXTRA_LIBS "${ANDROID_EXTRA_LIBS}")
endif()

target_link_libraries(ClockRadio PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Network Qt${QT_VERSION_MAJOR}::Multimedia Qt${QT_VERSION_MAJOR}::WebEngineWidgets)

set_target_properties(ClockRadio PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS ClockRadio
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(ClockRadio)
endif()
