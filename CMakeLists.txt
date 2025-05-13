cmake_minimum_required(VERSION 3.15)
project(Kabo
  VERSION 1.0
  LANGUAGES CXX
)

#----------------------------------------------------------------
# 现代 CMake 核心配置
#----------------------------------------------------------------
set(CMAKE_CXX_STANDARD 20)                # 强制使用 C++20 标准
set(CMAKE_CXX_STANDARD_REQUIRED ON)       # 必须支持该标准
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)     # 生成 compile_commands.json

# 默认构建类型为 Debug（如果未指定）
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()

#----------------------------------------------------------------
# 项目目录结构
#----------------------------------------------------------------
# 源文件目录
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
# 头文件目录
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

#----------------------------------------------------------------
# 自动收集源文件（推荐显式列出，此处演示自动收集）
#----------------------------------------------------------------
file(GLOB_RECURSE SOURCES 
  "${SOURCE_DIR}/*.cpp"
)

# 更安全的做法是显式列出源文件：
# set(SOURCES
#   src/main.cpp
#   src/foo.cpp
#   src/bar.cpp
# )

#----------------------------------------------------------------
# 第三方库
#----------------------------------------------------------------
# GLFW
set(GLFW_BUILD_EXAMPLES OFF)
set(GLFW_BUILD_TESTS OFF)
set(GLFW_BUILD_DOCS OFF)
set(GLFW_INSTALL OFF)
add_subdirectory(3rdparty/glfw)

#GLM
set(GLM_BUILD_TESTS OFF)
set(GLM_BUILD_INSTALL OFF)
set(GLM_ENABLE_CXX_20 ON)
add_subdirectory(3rdparty/glm)

#SOIL2
set(SOIL2_BUILD_TESTS OFF)
add_subdirectory(3rdparty/SOIL2)

#----------------------------------------------------------------
# 可执行目标
#----------------------------------------------------------------
add_executable(${PROJECT_NAME} ${SOURCES})

# 现代头文件包含方式
target_include_directories(${PROJECT_NAME} PUBLIC
  $<BUILD_INTERFACE:${INCLUDE_DIR}>  # 构建时包含
  # $<INSTALL_INTERFACE:include>       # 安装后包含（可选）
)

#----------------------------------------------------------------
# 依赖管理示例（假设需要第三方库）
#----------------------------------------------------------------
# find_package(OpenCV REQUIRED)
# target_link_libraries(${PROJECT_NAME} PRIVATE OpenCV::OpenCV)
target_link_libraries(${PROJECT_NAME}
 PRIVATE glfw glm soil2)

#----------------------------------------------------------------
# 安装规则（可选）
#----------------------------------------------------------------
install(TARGETS ${PROJECT_NAME}
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
)

install(DIRECTORY ${INCLUDE_DIR}/ DESTINATION include)