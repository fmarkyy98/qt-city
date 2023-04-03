# Target OS settings
if(UNIX AND NOT APPLE)
    set(LINUX TRUE)
endif()

if(WIN32) 
    set(CMAKE_CXX_COMPILER ${PROJECT_SOURCE_DIR}/external/windows/mingw/bin/g++.exe)
    set(CMAKE_PREFIX_PATH ${PROJECT_SOURCE_DIR}/external/windows/qt/6.4.3/mingw_64)
    set(Qt6_DIR ${PROJECT_SOURCE_DIR}/external/windows/qt/6.4.3/mingw_64/lib/cmake/Qt6)
    set(QT_WINDEPLOY ${PROJECT_SOURCE_DIR}/external/windows/qt/6.4.3/mingw_64/bin/windeployqt.exe)
elseif(LINUX)
    message(STATUS ">>>Linux")
elseif(APPLE)
    #
else()
    # 
endif()