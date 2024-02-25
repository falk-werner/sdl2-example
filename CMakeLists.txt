cmake_minimum_required(VERSION 3.22)
project(sdl2-example VERSION 1.0.0)

set(CMAKE_C_STANDARD 99)

find_package(SDL2 REQUIRED)
#find_package(PkgConfig REQUIRED)
#pkg_check_modules(SDL2 REQUIRED sdl2)

if (WIN32)
    set(SUBSYSTEM_OPTIONS "-mwindows")
else()
    set(SUBSYSTEM_OPTIONS "")
endif()

add_executable(sdl2-hello src/main.c)
target_include_directories(sdl2-hello PRIVATE ${SDL2_INCLUDE_DIRS})
target_link_libraries(sdl2-hello PRIVATE ${SDL2_LIBRARIES})
target_link_options(sdl2-hello PRIVATE ${SDL2_LDFLAGS} ${SUBSYSTEM_OPTIONS})
target_link_directories(sdl2-hello PRIVATE ${SDL2_LIBRARY_DIRS})
target_compile_options(sdl2-hello PRIVATE ${SDL2_CFLAGS})
