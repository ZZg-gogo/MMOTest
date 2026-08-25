# 收集 Common 目录下所有 cpp 文件
file(GLOB_RECURSE COMMON_SOURCE_FILES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cc"
)

# Common 模块
add_library(Common
    ${COMMON_SOURCE_FILES}
)

# 头文件搜索路径
target_include_directories(Common
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

# 编译选项
target_link_libraries(Common
    PRIVATE
        zzh_options
)