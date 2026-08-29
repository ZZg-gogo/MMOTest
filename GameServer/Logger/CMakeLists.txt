# 收集 Logger 目录下所有 cpp 文件
file(GLOB_RECURSE Logger_SOURCE_FILES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cc"
)

# Logger 模块
add_library(Logger
    ${Logger_SOURCE_FILES}
)

# 头文件搜索路径
target_include_directories(Logger
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

# 编译选项
target_link_libraries(Logger
    PRIVATE
        zzh_options
        spdlog::spdlog
)