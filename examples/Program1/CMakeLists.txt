# 定义当前应用的源文件
set(APP1_SOURCES
    main.cpp
    # 其他.cpp文件...
)

# 创建可执行目标
add_executable(Program1 ${APP1_SOURCES})
# 链接公共库和头文件
target_link_libraries(Program1 PRIVATE ${COMMON_LIBS})