cmake_minimum_required(VERSION 3.10)
project(N64_Emu C CXX)

find_package(SDL2 REQUIRED)

string(REGEX REPLACE "-fexceptions" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-exceptions")

string(REGEX REPLACE "-frtti" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti")

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
