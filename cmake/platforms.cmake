# Target OS settings
if(UNIX AND NOT APPLE)
    set(LINUX TRUE)
endif()

if(WIN32) 
    # To build project without Qt Creator with CMake
    message(STATUS ">>>Windows")
    # Use these on local PC, CI uses command line arguments
    # set(CMAKE_PREFIX_PATH "C:/Qt/6.4.3/mingw_64")
    # set(QT_WINDEPLOY "C:/Qt/6.4.3/mingw_64/bin/windeployqt.exe")
    # set(Qt6_DIR "C:/Qt/6.4.3/mingw_64/lib/cmake/qt6") # CACHE PATH "Initial cache" FORCE
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
