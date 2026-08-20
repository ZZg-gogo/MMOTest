# 收集当前目录下所有测试源文件
file(GLOB TEST_SOURCE_FILES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cxx"
)

# 排序
list(SORT TEST_SOURCE_FILES)

# 多线程库
find_package(Threads REQUIRED)

# 测试程序输出目录
set(TEST_OUTPUT_DIRECTORY
    "${PROJECT_SOURCE_DIR}/bin/tests"
)

# 遍历所有测试源文件
foreach(TEST_SOURCE IN LISTS TEST_SOURCE_FILES)

    # 获取测试文件名
    get_filename_component(TEST_NAME
        "${TEST_SOURCE}"
        NAME_WE
    )

    message(STATUS "Add test: ${TEST_NAME}")

    # 防止 Target 重名
    if(TARGET ${TEST_NAME})
        message(FATAL_ERROR
            "Target ${TEST_NAME} already exists."
        )
    endif()

    # 创建测试可执行文件
    add_executable(${TEST_NAME}
        "${TEST_SOURCE}"
    )

    # 链接需要测试的模块
    target_link_libraries(${TEST_NAME}
        PRIVATE
            common
            aoi
            scene
            Threads::Threads
    )

    # 输出目录
    set_target_properties(${TEST_NAME}
        PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY
                "${TEST_OUTPUT_DIRECTORY}"
    )

    # 多配置生成器
    foreach(CONFIG IN LISTS CMAKE_CONFIGURATION_TYPES)

        string(TOUPPER "${CONFIG}" CONFIG_UPPER)

        set_target_properties(${TEST_NAME}
            PROPERTIES
                RUNTIME_OUTPUT_DIRECTORY_${CONFIG_UPPER}
                    "${TEST_OUTPUT_DIRECTORY}"
        )

    endforeach()

    # 注册 CTest
    add_test(
        NAME ${TEST_NAME}
        COMMAND ${TEST_NAME}
    )

endforeach()