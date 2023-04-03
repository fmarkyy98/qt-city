# Target OS settings
if(UNIX AND NOT APPLE)
    set(LINUX TRUE)
endif()

if(WIN32) 
    set(CMAKE_PREFIX_PATH ${PROJECT_SOURCE_DIR}/external/windows/qt/6.4.3/mingw_64)
    set(Qt6_DIR ${PROJECT_SOURCE_DIR}/external/windows/qt/6.4.3/mingw_64/)
    set(QT_WINDEPLOY ${PROJECT_SOURCE_DIR}/external/windows/qt/6.4.3/mingw_64/bin/windeployqt.exe)
elseif(LINUX)
    message(STATUS ">>>Linux")
elseif(APPLE)
    message(STATUS ">>>Apple")
else()
    # 
endif()