# 定义当前应用的源文件
set(APP2_SOURCES
    main.cpp
    # 其他.cpp文件...
)

# 创建可执行目标
add_executable(Program2 ${APP2_SOURCES})
# 链接公共库和头文件
target_link_libraries(Program2 PRIVATE ${COMMON_LIBS})