cmake_minimum_required(VERSION 3.16)
project(maximus VERSION 3.2.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Output directory for binaries
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Detect endianness
include(TestBigEndian)
test_big_endian(IS_BIG_ENDIAN)

# Platform-specific defines
if(UNIX)
    add_definitions(-DUNIX)
endif()

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    add_definitions(-DLINUX)
endif()

# Set template flags for configure_file()
if(IS_BIG_ENDIAN)
    set(BIG_ENDIAN 1)
else()
    set(LITTLE_ENDIAN 1)
endif()

# Generate current timestamp for version header
string(TIMESTAMP CURRENT_TIMESTAMP "%a %b %d %I:%M:%S %p %Z %Y")

# Configure generated headers
configure_file(
    ${CMAKE_SOURCE_DIR}/cmake/version.h.in
    ${CMAKE_BINARY_DIR}/generated/version.h
    @ONLY
)

configure_file(
    ${CMAKE_SOURCE_DIR}/cmake/compiler_details.h.in
    ${CMAKE_BINARY_DIR}/generated/compiler_details.h
    @ONLY
)

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE
    ${PROJECT_SOURCE_DIR}/src/slib
    ${PROJECT_SOURCE_DIR}/src/unix/include
    ${CMAKE_BINARY_DIR}/generated
)

# Collect source files
file(GLOB_RECURSE SRC_FILES
    src/*.c
    src/*.cpp
)

# Build executable
add_executable(${PROJECT_NAME} ${SRC_FILES})

# Link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE m)

# Platform-specific definitions
if(UNIX AND NOT APPLE)
    target_compile_definitions(${PROJECT_NAME} PRIVATE PLATFORM_LINUX)
endif()

# Installation
install(TARGETS ${PROJECT_NAME} DESTINATION bin)