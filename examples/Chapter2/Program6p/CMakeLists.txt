
# 创建可执行目标
add_executable(Program6p main.cpp)
# 链接公共库和头文件
target_link_libraries(Program6p PRIVATE common_lib ${COMMON_LIBS})