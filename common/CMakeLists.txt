add_library(common
    src/Vec2.cpp
)


target_include_directories(common
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(common PRIVATE zzh_options)