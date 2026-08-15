# 收集 unit 模块源文件
file(GLOB UNIT_SOURCE_FILES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

# unit 模块
add_library(unit
    ${UNIT_SOURCE_FILES}
)

# unit 头文件
target_include_directories(unit
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# unit 依赖
target_link_libraries(unit
    PUBLIC
        common
    PRIVATE
        zzh_options
)