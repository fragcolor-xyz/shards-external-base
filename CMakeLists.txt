project("shards-example")
cmake_minimum_required(VERSION 3.14)
set(CMAKE_CXX_STANDARD 17)
add_compile_options(-Wall)

# Define source files
set(
  MY_PROJECT_SOURCE_FILES
  ${MY_PROJECT_SOURCE_FILES}
  ${CMAKE_CURRENT_LIST_DIR}/calculator.cpp
)

if(NOT EXISTS "${SHARDS_DIR}/include/shards/shards.hpp")
  message(FATAL_ERROR "SHARDS_DIR(${SHARDS_DIR}) is not set correctly, please set it to the shards root directory")
endif()

# Header paths for your shard
set(
  MY_PROJECT_HEADER_PATHS
  ${MY_PROJECT_HEADER_PATHS}
  -I${SHARDS_DIR}/include
  -I${SHARDS_DIR}/deps/entt/src
)

# Optional: Setup code formatting
find_program(
  CLANG_FORMAT_EXE
  NAMES "clang-format"
  DOC "Path to clang-format executable"
)
if(NOT CLANG_FORMAT_EXE)
  message(STATUS "clang-format not found.")
else()
  message(STATUS "clang-format found: ${CLANG_FORMAT_EXE}")
  add_custom_target(
    format
    COMMAND ${CLANG_FORMAT_EXE} -i -style=LLVM ${MY_PROJECT_SOURCE_FILES}
  )
endif()

# Platform-specific settings
if(UNIX AND NOT APPLE)
  set(LINUX TRUE)
endif()

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

if(APPLE)
  include_directories(/usr/local/include)
  link_directories(/usr/local/lib)
endif()

# Include Shards headers
include_directories(
  ${SHARDS_DIR}/include
  ${SHARDS_DIR}/deps/stb
  ${SHARDS_DIR}/deps/cpp-taskflow
  ${SHARDS_DIR}/deps/nameof/include
  ${SHARDS_DIR}/deps/magic_enum/include
  ${SHARDS_DIR}/deps/spdlog/include
  ${SHARDS_DIR}/deps/entt/src
)

# Create the shared library
add_library(
  cbcalculator SHARED
  ${CMAKE_CURRENT_LIST_DIR}/calculator.cpp
)

# Platform-specific definitions
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
  # 64 bits
elseif(CMAKE_SIZEOF_VOID_P EQUAL 4)
  # 32 bits
  add_compile_definitions(I386_BUILD)
endif()

# Set library properties
set_target_properties(cbcalculator PROPERTIES PREFIX "")
set_target_properties(cbcalculator PROPERTIES OUTPUT_NAME "calculator")