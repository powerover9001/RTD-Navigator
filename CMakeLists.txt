cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)


project("RTD-Navigator" VERSION 0.1 LANGUAGES CXX)


message("CMake is running for windows version")
file(GLOB_RECURSE SRC_FILES src/*.cpp)

add_executable("${PROJECT_NAME}" ${SRC_FILES})

target_include_directories("${PROJECT_NAME}" PUBLIC
	"${CMAKE_SOURCE_DIR}/Dependencies/RTD-Navigator/include"
	"${CMAKE_SOURCE_DIR}/Dependencies/Windows-SDL2-2.0.22/include"
	"${CMAKE_SOURCE_DIR}/Dependencies/Windows-SDL2_image-2.0.5/include"
)

target_link_libraries("${PROJECT_NAME}"
	"${CMAKE_SOURCE_DIR}/Dependencies/Windows-SDL2-2.0.22/lib/x64/SDL2.lib"
	#"${CMAKE_SOURCE_DIR}/Dependencies/Windows-SDL2-2.0.22/lib/x64/SDL2main.lib"
	#"${CMAKE_SOURCE_DIR}/Dependencies/Windows-SDL2-2.0.22/lib/x64/SDL2test.lib"
	"${CMAKE_SOURCE_DIR}/Dependencies/Windows-SDL2_image-2.0.5/lib/x64/SDL2_image.lib"
)
