cmake_minimum_required(VERSION 3.10)
project(PerfDemo C)

set(CMAKE_C_STANDARD 99)

# Enable debug symbols (-g) and retain frame pointers (-fno-omit-frame-pointer)
# to allow accurate call stack walking with perf
add_compile_options(-g -O2 -fno-omit-frame-pointer)

find_package(Threads REQUIRED)

# Executable 1: User-Mode saturation demo
add_executable(perf_demo_user main_user.c)
target_link_libraries(perf_demo_user m)

# Executable 2: Kernel-Mode saturation demo
add_executable(perf_demo_sys main_sys.c)
target_link_libraries(perf_demo_sys m Threads::Threads)
