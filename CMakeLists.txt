cmake_minimum_required(VERSION 3.7...3.26)

# Allow IDE Source Tree Visualization
if(${CMAKE_VERSION} VERSION_LESS 3.26)
	set_property(GLOBAL PROPERTY USE_FOLDERS ON)
else()
	cmake_policy(SET CMP0143 NEW)
endif()

project(Connect-4)

set(SRCS
    "src/utils/static_vec.h"
    
    "src/bitboard.h"
    "src/board.cpp"
    "src/board.h"
    "src/defs.h"
    "src/evaluate.h"
    "src/main.cpp"
    "src/move_picker.cpp"
    "src/move_picker.h"
    "src/movegen.cpp"
    "src/movegen.h"
    "src/search.cpp"
    "src/search.h"
    "src/tt.cpp"
    "src/tt.h")

add_executable(connect4 ${SRCS})

target_compile_features(connect4 PRIVATE cxx_std_20)

# for Visual Studio/MSVC
set_target_properties(connect4 PROPERTIES MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SRCS})
