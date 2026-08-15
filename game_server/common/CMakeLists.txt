# 收集 common 模块源文件
file(GLOB COMMON_SOURCE_FILES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

# common 模块
add_library(common
    ${COMMON_SOURCE_FILES}
)

# common 头文件
target_include_directories(common
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# 编译选项
target_link_libraries(common
    PRIVATE
        zzh_options
)