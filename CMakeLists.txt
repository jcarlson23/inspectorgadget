cmake_minimum_required(VERSION 3.4.3)

if (DEFINED ENV{LLVM_DIR})

   set(CMAKE_CXX_STANDARD 11)

   find_package(LLVM REQUIRED CONFIG)
   list(APPEND CMAKE_MODULE_PATH "${LLVM_CMAKE_DIR}")
   include(AddLLVM)

   add_definitions(${LLVM_DEFINITIONS})
   include_directories(${LLVM_INCLUDE_DIRS})
else()
   message(FATAL_ERROR "\
   WARNING: The LLVM_DIR var was not set (required for an out-of-source build)!\n\
   Please set this to environment variable to point to the LLVM build directory\
   (e.g. on linux: export LLVM_DIR=/path/to/llvm/build/dir)")
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include
	            ${CMAKE_CURRENT_BINARY_DIR}/include
		    /usr/local/Cellar/nlohmann_json/3.1.2/include
		    )

add_subdirectory(lib)
add_subdirectory(tools)

