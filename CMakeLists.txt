cmake_minimum_required(VERSION 3.10)
project(N64_Emu C CXX)

find_package(SDL2 REQUIRED)

include_directories(${PROJECT_NAME}
	${SDL2_INCLUDE_DIRS})

add_executable(${PROJECT_NAME}
	main.cpp
	global.cpp
	cpu.cpp
	mem.cpp
	rcp.cpp)

target_link_libraries(${PROJECT_NAME}
	${SDL2_LIBRARIES})
