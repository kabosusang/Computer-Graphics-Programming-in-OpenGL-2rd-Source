# 定义当前应用的源文件
set(APP5_SOURCES
    main.cpp
    # 其他.cpp文件...
)

# 创建可执行目标
add_executable(Program5 ${APP5_SOURCES})
# 链接公共库和头文件
target_link_libraries(Program5 PRIVATE ${COMMON_LIBS})