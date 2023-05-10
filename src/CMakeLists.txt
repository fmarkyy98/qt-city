set(TARGET QtCity)

set(INCLUDES 
	${CMAKE_CURRENT_SOURCE_DIR}/model/export/
	${CMAKE_CURRENT_SOURCE_DIR}/view/export/
	${CMAKE_CURRENT_SOURCE_DIR}/persistence/export/
)

set(LIBRARIES
	Qt6::Widgets
	Qt6::Core
)

file(GLOB INTERNAL_HEADERS_BASIC
	${CMAKE_CURRENT_SOURCE_DIR}/model/*.h
	${CMAKE_CURRENT_SOURCE_DIR}/view/*.h
	${CMAKE_CURRENT_SOURCE_DIR}/persistence/*.h
)

file(GLOB_RECURSE INTERNAL_NESTED_HEADERS
	${CMAKE_CURRENT_SOURCE_DIR}/model/building/*.h
)

list(APPEND INTERNAL_HEADERS ${INTERNAL_HEADERS_BASIC} ${INTERNAL_NESTED_HEADERS})

file(GLOB_RECURSE PUBLIC_HEADERS
	${CMAKE_CURRENT_SOURCE_DIR}/model/export/*.h
	${CMAKE_CURRENT_SOURCE_DIR}/view/export/*.h
	${CMAKE_CURRENT_SOURCE_DIR}/persistence/export/*.h
)

file(GLOB_RECURSE UIS 
	${CMAKE_CURRENT_SOURCE_DIR}/*.ui
)

set(SOURCES
    main.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/model/building/base/BuildingBase.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/model/building/base/StructureBase.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/model/building/base/WorkplaceBase.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/model/building/Factory.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/model/building/Forest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/model/building/Police.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/model/building/ResidentialBuilding.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/model/building/Road.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/model/building/Stadium.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/model/building/Store.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/model/GameBoard.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/model/GameModel.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/model/GameModelFactory.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/persistence/FileIOService.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/persistence/FileIOServiceFactory.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/view/GamePage.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/view/MainWindow.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/view/MenuPage.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/view/ViewFactory.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES} ${INTERNAL_HEADERS} ${PUBLIC_HEADERS} ${UIS} ${RECOURSES})

target_link_libraries(${TARGET} ${LIBRARIES})
target_include_directories(${TARGET} PRIVATE ${INCLUDES})

if(WIN32)
	add_custom_command(TARGET ${TARGET} POST_BUILD
    COMMAND ${QT_WINDEPLOY} $<TARGET_FILE:${TARGET}>
	)
endif()

if(USE_TEST)
        add_subdirectory(test)
endif()