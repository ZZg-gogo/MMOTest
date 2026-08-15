cmake_minimum_required(VERSION 3.25)

project(MMOTest
    VERSION 0.1.0
    LANGUAGES CXX C
)

# C++ 标准
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 默认 Debug
if(NOT CMAKE_CONFIGURATION_TYPES AND NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build." FORCE)
endif()

set_property(
    CACHE CMAKE_BUILD_TYPE
    PROPERTY STRINGS
        Debug
        Release
        RelWithDebInfo
        MinSizeRel
)

message(STATUS "Build Type: ${CMAKE_BUILD_TYPE}")

# 项目构建选项
include(cmake/zzhOptions.cmake)

# 项目模块 进入这些目录找对应的cmake文件
add_subdirectory(game_server/common)
add_subdirectory(game_server/aoi)
#add_subdirectory(game_server/fight)
add_subdirectory(game_server/unit)
add_subdirectory(tests)