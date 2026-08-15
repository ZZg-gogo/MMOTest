# 收集 AOI 模块源文件
file(GLOB AOI_SOURCE_FILES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

# AOI 模块
add_library(aoi
    ${AOI_SOURCE_FILES}
)

# AOI 头文件
target_include_directories(aoi
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# AOI 依赖
target_link_libraries(aoi
    PUBLIC
        common
    PRIVATE
        zzh_options
)