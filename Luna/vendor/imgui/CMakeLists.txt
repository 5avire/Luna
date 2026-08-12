cmake_minimum_required(VERSION 3.16)
project(imgui)

file(GLOB IMGUI_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/imgui/*.cpp)
add_library(imgui STATIC ${IMGUI_SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/imgui ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)
