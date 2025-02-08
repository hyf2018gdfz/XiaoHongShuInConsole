cmake_minimum_required(VERSION 3.12)

set(PROJECT_NAME ChatBox) # 设置工程名 

project(${PROJECT_NAME})    # 工程名 CppTemplate

set(CMAKE_CXX_STANDARD 14) # C++标准
set(CMAKE_CXX_STANDARD_REQUIRED ON) # C++标准是必须的

set(CMAKE_BUILD_TYPE "Debug")  # Debug模式 选项: Release Debug MinSizeRel RelWithDebInfo
# 针对不同模式设置编译选项
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  add_compile_options(-O0 -Wall -g2 -fexec-charset=UTF-8 -finput-charset=UTF-8 -fdiagnostics-color=always)
else(CMAKE_BUILD_TYPE STREQUAL "Release")
  add_compile_options(-O2 -Wall)
endif()

# 这段代码可以区分操作系统
message("Identifying the OS...")
if(WIN32)
  message("This is Windows.")
  file(GLOB_RECURSE LIBRARY_FILES ${PROJECT_SOURCE_DIR}/lib/*.lib)
  if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    add_compile_options("/source-charset:utf-8")
    add_compile_options("/execution-charset:utf-8")
  else()
    add_compile_options("-finput-charset=utf-8")
    add_compile_options("-fexec-charset=utf-8")
  endif()
elseif(APPLE)
  message("This is MacOS.")
elseif(UNIX)
  file(GLOB_RECURSE LIBRARY_FILES ${PROJECT_SOURCE_DIR}/lib/*.a)
  message("This is Linux.")
endif()
# 这段代码可以区分操作系统

# 设置头文件路径
include_directories(${PROJECT_SOURCE_DIR}/include)

# 递归列出所有源文件
file(GLOB_RECURSE SOURCE_FILES ${PROJECT_SOURCE_DIR}/source/*.cpp)

# 设置可执行文件输出路径
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/out)

# 添加可执行目标
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

# 链接库（如果有需要）
target_link_libraries(${PROJECT_NAME} ${LIBRARY_FILES})