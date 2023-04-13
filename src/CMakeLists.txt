set(TARGET QtCity)

set(INCLUDES 
        ${CMAKE_CURRENT_SOURCE_DIR}/common/
	${CMAKE_CURRENT_SOURCE_DIR}/model/
	${CMAKE_CURRENT_SOURCE_DIR}/view/
	${CMAKE_CURRENT_SOURCE_DIR}/persistence/
)

set(LIBS
	Qt6::Widgets
)

file(GLOB INTERNAL_HEADERS
        ${CMAKE_CURRENT_SOURCE_DIR}/common/*.h
	${CMAKE_CURRENT_SOURCE_DIR}/model/*.h
	${CMAKE_CURRENT_SOURCE_DIR}/view/*.h
	${CMAKE_CURRENT_SOURCE_DIR}/persistence/*.h
)

file(GLOB PUBLIC_HEADERS
	${CMAKE_CURRENT_SOURCE_DIR}/model/include/*.h
	${CMAKE_CURRENT_SOURCE_DIR}/view/include/*.h
	${CMAKE_CURRENT_SOURCE_DIR}/persistence/include/*.h
)

file(GLOB_RECURSE UIS 
	${CMAKE_CURRENT_SOURCE_DIR}/*.ui
)

set(SOURCES
    main.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/model/building/base/BuildingBase.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/model/building/base/WorkplaceBase.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/model/building/ResidentialBuilding.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/model/GameBoard.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/model/GameModel.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/persistence/FileIOService.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/view/GamePage.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/view/MainWindow.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/view/MenuPage.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES} ${INTERNAL_HEADERS} ${UI_HEADERS})

target_link_libraries(${TARGET} ${LIBS})
target_include_directories(${TARGET} PRIVATE ${INCLUDES})

if(WIN32)
	add_custom_command(TARGET ${TARGET} POST_BUILD
    COMMAND ${QT_WINDEPLOY} $<TARGET_FILE:${TARGET}>
	)
endif()
