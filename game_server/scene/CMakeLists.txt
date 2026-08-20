# 收集 scene 模块源文件
file(GLOB SCENE_SOURCE_FILES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

# scene 模块
add_library(scene
    ${SCENE_SOURCE_FILES}
)

# scene 头文件
target_include_directories(scene
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# scene 依赖
target_link_libraries(scene
    PUBLIC
        common
    PRIVATE
        zzh_options
)