cmake_minimum_required(VERSION 3.16)
project(stb_image)

file(GLOB STB_IMAGE_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/stb_image.cpp)
add_library(stb_image STATIC ${STB_IMAGE_SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
