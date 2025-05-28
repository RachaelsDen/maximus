cmake_minimum_required(VERSION 3.16)
project(maximus VERSION 3.2.0 LANGUAGES C)

# Use C++17 (or C++14/C11 if needed)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Detect endianess
include(TestBigEndian)
test_big_endian(IS_BIG_ENDIAN)

if(UNIX)
    add_definitions(-DUNIX)
endif()

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    add_definitions(-DLINUX)
endif()

# Set define flags for the template
if(IS_BIG_ENDIAN)
    set(BIG_ENDIAN 1)
else()
    set(LITTLE_ENDIAN 1)
endif()

# Configure the header
string(TIMESTAMP CURRENT_TIMESTAMP "%a %b %d %I:%M:%S %p %Z %Y")

# Output directory for binaries
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Include paths
include_directories(
    ${PROJECT_SOURCE_DIR}/src/slib
    ${PROJECT_SOURCE_DIR}/src/unix/include
)
configure_file(
    ${CMAKE_SOURCE_DIR}/cmake/version.h.in
    ${CMAKE_BINARY_DIR}/generated/version.h
    ${CMAKE_SOURCE_DIR}/cmake/compiler_details.h.in
    ${CMAKE_BINARY_DIR}/generated/compiler_details.h
    @ONLY
)
include_directories(${CMAKE_BINARY_DIR}/generated)

# Collect all source files (can refine later)
file(GLOB_RECURSE SRC_FILES
    src/*.cpp src/*.c
)

# Main executable (adjust as needed)
add_executable(maximus ${SRC_FILES})

# Link libraries (if/when needed)
target_link_libraries(maximus m)

# Platform-specific adjustments (e.g., Linux)
if(UNIX AND NOT APPLE)
    target_compile_definitions(maximus PRIVATE PLATFORM_LINUX)
endif()

# Installation setup (optional for now)
install(TARGETS maximus DESTINATION bin)
