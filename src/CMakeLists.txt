set(TARGET QtCity)

set(INCLUDES 
	${CMAKE_CURRENT_SOURCE_DIR}/model/
	${CMAKE_CURRENT_SOURCE_DIR}/view/
	${CMAKE_CURRENT_SOURCE_DIR}/persistence/
)

file(GLOB INTERNAL_HEADERS
	${CMAKE_CURRENT_SOURCE_DIR}/model/*.h
	${CMAKE_CURRENT_SOURCE_DIR}/view/*.h
	${CMAKE_CURRENT_SOURCE_DIR}/persistence/*.h
)

file(GLOB_RECURSE UIS 
	${CMAKE_CURRENT_SOURCE_DIR}/*.ui
)

set(SOURCES
    main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/view/MainWindow.cpp
)

# qt6_wrap_ui(UI_HEADERS ${UIS})

add_executable(${PROJECT_NAME} ${SOURCES} ${INTERNAL_HEADERS} ${UI_HEADERS})

target_link_libraries(${PROJECT_NAME} Qt6::Widgets)
target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDES})

if(WIN32)
	add_custom_command(TARGET ${TARGET} POST_BUILD
    COMMAND ${QT_WINDEPLOY} $<TARGET_FILE:${TARGET}>
	)
endif()