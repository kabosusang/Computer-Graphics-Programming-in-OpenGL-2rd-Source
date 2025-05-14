# 定义当前应用的源文件
set(APP4_SOURCES
    main.cpp
    # 其他.cpp文件...
)

# 创建可执行目标
add_executable(Program4 ${APP4_SOURCES})
# 链接公共库和头文件
target_link_libraries(Program4 PRIVATE ${COMMON_LIBS})