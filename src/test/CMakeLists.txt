project(test_QtCity LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS
        Test
        Core
)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

message(INCLUDES="${INCLUDES}")

enable_testing(true)

set(TEST_LIBRARIES
    Qt6::Core
    Qt6::Test
    Qt6::Widgets
)

set(TEST_INCLUDES
    ${CMAKE_CURRENT_SOURCE_DIR}/../
    ${CMAKE_CURRENT_SOURCE_DIR}/../model
    ${CMAKE_CURRENT_SOURCE_DIR}/../model/export
    ${CMAKE_CURRENT_SOURCE_DIR}/../model/building
    ${CMAKE_CURRENT_SOURCE_DIR}/../model/building/base
    ${CMAKE_CURRENT_SOURCE_DIR}/../persistence
    ${CMAKE_CURRENT_SOURCE_DIR}/../persistence/export
)

set(TEST_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/QtCityTestMain.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/QtCityGameModelTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/QtCityPersistenceTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/QtCityModelBaseTest.cpp
)

file(GLOB TEST_INTERNAL_HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/*.h
)

string(REPLACE "main.cpp" "" CPPFILES "${SOURCES}")
message(CPPFILES="${CPPFILES}")

add_executable(test_QtCity ${TEST_SOURCES} ${CPPFILES} ${TEST_INTERNAL_HEADERS} ${INTERNAL_HEADERS} ${PUBLIC_HEADERS} ${UIS} ${RECOURSES})
add_test(NAME test_QtCity COMMAND test_QtCity)

target_include_directories(test_QtCity PRIVATE ${TEST_INCLUDES} ${INCLUDES})
target_link_libraries(test_QtCity PRIVATE ${TEST_LIBRARIES})

if(WIN32)
    add_custom_command(TARGET test_QtCity POST_BUILD
        COMMAND ${QT_WINDEPLOY} $<TARGET_FILE:test_QtCity>
        COMMENT "Deploying Qt..."
    )
endif()


