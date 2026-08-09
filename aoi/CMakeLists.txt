# 创建 AOI 库
add_library(aoi
    src/TowerAoi.cpp
)

# AOI 对外暴露的头文件目录
target_include_directories(aoi
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# AOI 编译配置
target_link_libraries(aoi
    PRIVATE
        zzh_options
)

# AOI 的代码依赖
target_link_libraries(aoi
    PUBLIC
        common
)

# 创建 AOI 测试程序
add_executable(aoi_test
    tests/AOITest.cpp
)

# 测试程序依赖 AOI
target_link_libraries(aoi_test
    PRIVATE
        aoi
)

set_target_properties(aoi_test PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY
        ${CMAKE_BINARY_DIR}/bin
)