cmake_minimum_required(VERSION 3.15)
project(Kabo
  VERSION 1.0
  LANGUAGES CXX
)

#----------------------------------------------------------------
# 现代 CMake 核心配置
#----------------------------------------------------------------
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()

#----------------------------------------------------------------
# 第三方库配置（保持不变）
#----------------------------------------------------------------
set(GLFW_BUILD_EXAMPLES OFF)
set(GLFW_BUILD_TESTS OFF)
set(GLFW_BUILD_DOCS OFF)
set(GLFW_INSTALL OFF)
add_subdirectory(3rdparty/glfw)

set(GLM_BUILD_TESTS OFF)
set(GLM_BUILD_INSTALL OFF)
set(GLM_ENABLE_CXX_20 ON)
add_subdirectory(3rdparty/glm)

set(SOIL2_BUILD_TESTS OFF)
add_subdirectory(3rdparty/SOIL2)

add_subdirectory(3rdparty/glew)

#----------------------------------------------------------------
# 公共配置（头文件/库依赖）
#----------------------------------------------------------------
# 公共头文件目录（所有子项目可访问）
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${INCLUDE_DIR})

# 公共库依赖（GLFW/GLM/SOIL2）
set(COMMON_LIBS glfw glm soil2 libglew_static)

#----------------------------------------------------------------
# 子目录配置（关键修改点）
#----------------------------------------------------------------
# 设置可执行文件输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

#复制着色器文件到bin目录
file(COPY ${CMAKE_SOURCE_DIR}/Shader DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

# 添加apps子目录（将生成所有可执行文件）
add_subdirectory(examples)