# 收集 Entities 目录下所有 cpp 文件
file(GLOB_RECURSE ENTITY_SOURCE_FILES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cc"
)

# Entities 模块
add_library(Entities
    ${ENTITY_SOURCE_FILES}
)

# 头文件搜索路径
target_include_directories(Entities
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

# 编译选项
target_link_libraries(Entities
    PRIVATE
        zzh_options
        Logger
)