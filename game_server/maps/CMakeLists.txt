# 收集 MAPS 模块源文件
file(GLOB MAPS_SOURCE_FILES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

# MAPS 模块
add_library(maps
    ${MAPS_SOURCE_FILES}
)

# MAPS 头文件
target_include_directories(maps
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# 编译选项
target_link_libraries(maps
    PRIVATE
        zzh_options
)