# 收集 fight 模块源文件
file(GLOB FIGHT_SOURCE_FILES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

# fight 模块
add_library(fight
    ${FIGHT_SOURCE_FILES}
)

# fight 头文件
target_include_directories(fight
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# fight 依赖
target_link_libraries(fight
    PUBLIC
        common
    PRIVATE
        zzh_options
)