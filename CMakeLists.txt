cmake_minimum_required(VERSION 3.10)

project(MATMUL C CXX)


find_package(Threads REQUIRED)

set(CMAKE_EXPORT_COMPILE_COMMANDS True)
#set(CMAKE_C_FLAGS "-O2 -march=native -mno-avx512f -fopenmp")
#set(CMAKE_C_FLAGS "-O2 -march=native -mno-avx512f")
set(CMAKE_C_FLAGS "-march=native -mavx2 -mfma -mno-avx512f")
set(CMAKE_CXX_FLAGS "-std=c++11 -O2 -march=native -mavx2 -mfma -mno-avx512f")

add_executable(benchmark benchmark.c)
add_subdirectory(src)
target_link_libraries(benchmark PUBLIC matmul Threads::Threads)
target_include_directories(benchmark PUBLIC "${PROJECT_BINARY_DIR}"
"${PROJECT_SOURCE_DIR}/src")
