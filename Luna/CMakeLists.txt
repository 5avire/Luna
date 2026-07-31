cmake_minimum_required(VERSION 3.16)
project(Luna)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/$<CONFIG>-${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_PROCESSOR}/${PROJECT_NAME})

file(GLOB_RECURSE SOURCE_FILES "src/*.cpp")

# SPDLOG
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/vendor/spdlog)

# GLFW Builds
set(GLFW_BUILD_DOCS     OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS    OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/vendor/GLFW)

# GLAD
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/vendor/glad)

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} PRIVATE glfw glad spdlog)

target_compile_definitions(${PROJECT_NAME} PUBLIC
    $<$<CONFIG:Debug>:LUNA_DEBUG;LUNA_ENABLE_ASSERTS>
    $<$<CONFIG:Release>:LUNA_RELEASE;LUNA_ENABLE_ASSERTS>
    $<$<CONFIG:Dist>:LUNA_DIST>
)

target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/spdlog/include
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/GLFW/include
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/GLAD/include
)
