cmake_minimum_required(VERSION 3.13)
project(N64_Emu C CXX)

find_package(SDL2 REQUIRED)
include_directories(N64_Emu ${SDL2_INCLUDE_DIRS})

add_executable(N64_Emu
	main.cpp
	global.cpp
	cpu.cpp
	mem.cpp
	rcp.cpp)

target_link_libraries(N64_Emu ${SDL2_LIBRARIES})
