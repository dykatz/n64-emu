cmake_minimum_required(VERSION 3.14)
project(N64_Emu C CXX)

find_package(SDL2 REQUIRED)
find_package(bgfx REQUIRED)
find_package(cubeb REQUIRED)
find_package(SQLite3 REQUIRED)

string(REGEX REPLACE "-fexceptions" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-exceptions")

string(REGEX REPLACE "-frtti" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti")

include_directories(${PROJECT_NAME} ${SDL2_INCLUDE_DIRS})
include_directories(${PROJECT_NAME} ${BGFX_INCLUDE_DIRS})
include_directories(${PROJECT_NAME} ${CUBEB_INCLUDE_DIRS})
include_directories(${PROJECT_NAME} ${SQLITE3_INCLUDE_DIRS})

add_executable(${PROJECT_NAME}
	main.cpp
	global.cpp
	cpu.cpp
	mem.cpp
	rcp.cpp)

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${BGFX_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${CUBEB_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${SQLITE3_LIBRARIES})
