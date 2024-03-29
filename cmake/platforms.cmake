# Target OS settings
if(UNIX AND NOT APPLE)
    set(LINUX TRUE)
endif()

if(WIN32) 
    # To build project without Qt Creator with CMake
    # Make sure that you have the qt dependencie in <project's root'>/external/windows/qt path
    message(STATUS ">>>Windows")
    set(CMAKE_PREFIX_PATH ${PROJECT_SOURCE_DIR}/external/windows/qt/6.4.3/mingw_64)
    set(Qt6_DIR ${PROJECT_SOURCE_DIR}/external/windows/qt/6.4.3/mingw_64/)
    set(QT_WINDEPLOY ${PROJECT_SOURCE_DIR}/external/windows/qt/6.4.3/mingw_64/bin/windeployqt.exe)
elseif(LINUX)
    message(STATUS ">>>Linux")
elseif(APPLE)
    message(STATUS ">>>Apple")
    set(CMAKE_INSTALL_PREFIX "/usr/local")
    set(CMAKE_PREFIX_PATH "/Users/nemesviko/Qt/6.4.2/macos")
    set(MACDEPLOYQT_EXECUTABLE "/Users/nemesviko/Qt/6.4.2/macos/bin/macdeployqt")
    set_target_properties(${TARGET} PROPERTIES
        MACOSX_BUNDLE_GUI_IDENTIFIER my.qtcity.com
        MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
        MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
        MACOSX_BUNDLE TRUE
        WIN32_EXECUTABLE TRUE)
else()
    # 
endif()
