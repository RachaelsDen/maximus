# CMakeLists.txt - Maximus CBCS Build System
# Converted from Make-based build system to CMake 3.20+
# Original authors: Scott Dudley, Peter Fitzsimmions, David Nugent
# UNIX port: Wes Garland
# CMake conversion: 2025

cmake_minimum_required(VERSION 3.20)

project(MaximusCBCS
    VERSION 3.03
    DESCRIPTION "Maximus Computerized Bulletin Board System"
    LANGUAGES C CXX
)

# Build options
option(BUILD_MAXIMUS "Build Maximus BBS" ON)
option(BUILD_SQUISH "Build Squish message tosser" ON)
option(BUILD_UTILITIES "Build utility programs" ON)
option(BUILD_SHARED_LIBS "Build shared libraries" ON)

# Installation paths (mimics ./configure --prefix behavior)
# CMAKE_INSTALL_PREFIX defaults to /usr/local (standard CMake behavior)
# Override with: cmake -DCMAKE_INSTALL_PREFIX=/var/max
set(MAXIMUS_BIN_DIR "${CMAKE_INSTALL_PREFIX}/bin" CACHE PATH "Binary installation directory")
set(MAXIMUS_LIB_DIR "${CMAKE_INSTALL_PREFIX}/lib" CACHE PATH "Library installation directory")
set(MAXIMUS_ETC_DIR "${CMAKE_INSTALL_PREFIX}/etc" CACHE PATH "Configuration installation directory")
set(MAXIMUS_LIBEXEC_DIR "${CMAKE_INSTALL_PREFIX}/libexec" CACHE PATH "Library executables directory")

# Build type configuration
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING
        "Choose the type of build: Debug Release RelWithDebInfo MinSizeRel Profile"
        FORCE)
endif()

# Profile build type (custom)
if(CMAKE_BUILD_TYPE STREQUAL "Profile")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pg")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pg")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pg")
endif()

# Platform detection
string(TOLOWER "${CMAKE_SYSTEM_NAME}" PLATFORM)
message(STATUS "Platform: ${PLATFORM}")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "Install prefix: ${CMAKE_INSTALL_PREFIX}")

# Compiler requirements
if(NOT CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    message(WARNING "This project is designed for GCC/Clang. Your compiler may not work.")
endif()

# Find required tools
find_program(BISON_EXECUTABLE NAMES bison REQUIRED)
message(STATUS "Found bison: ${BISON_EXECUTABLE}")

# Detect endianness
include(TestBigEndian)
test_big_endian(IS_BIG_ENDIAN)
if(IS_BIG_ENDIAN)
    set(ENDIAN_DEF "MAXIMUS_BIG_ENDIAN")
    message(STATUS "Endianness: Big endian")
else()
    set(ENDIAN_DEF "MAXIMUS_LITTLE_ENDIAN")
    message(STATUS "Endianness: Little endian")
endif()

# Generate compiler_details.h
configure_file(
    "${CMAKE_SOURCE_DIR}/cmake/compiler_details.h.in"
    "${CMAKE_SOURCE_DIR}/slib/compiler_details.h"
    @ONLY
)

# Common include directories
set(MAXIMUS_INCLUDE_DIRS
    ${CMAKE_SOURCE_DIR}/unix/include
    ${CMAKE_SOURCE_DIR}/slib
    ${CMAKE_SOURCE_DIR}/msgapi
    ${CMAKE_SOURCE_DIR}/btree
    ${CMAKE_SOURCE_DIR}/max
    ${CMAKE_SOURCE_DIR}/prot
    ${CMAKE_SOURCE_DIR}/mex
    ${CMAKE_SOURCE_DIR}/lang
)

# Common compiler flags
add_compile_definitions(UNIX)
set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 98)
set(CMAKE_POSITION_INDEPENDENT_CODE ON CACHE BOOL "Enable PIC" FORCE)

# GCC-specific flags (preserving original build flags)
if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_C_COMPILER_ID MATCHES "Clang")
    add_compile_options(
        -Wall
        -funsigned-char
        -fno-strict-aliasing
    )

    # Platform-specific defines
    if(PLATFORM MATCHES "linux")
        add_compile_definitions(LINUX)
    elseif(PLATFORM MATCHES "freebsd|netbsd|openbsd")
        add_compile_definitions(BSD)
    elseif(PLATFORM MATCHES "sunos")
        if(CMAKE_SYSTEM_VERSION VERSION_LESS "5.0")
            add_compile_definitions(BSD)
        else()
            add_compile_definitions(SYSV)
        endif()
    endif()
endif()

# Find required libraries
find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIRS})

# Add subdirectories for libraries
# Order matters - dependencies must be built first
add_subdirectory(slib)
add_subdirectory(unix)
add_subdirectory(msgapi)
add_subdirectory(btree)
add_subdirectory(prot)
add_subdirectory(mex)
add_subdirectory(comdll)

# Add subdirectories for programs
if(BUILD_UTILITIES)
    add_subdirectory(util)
endif()

if(BUILD_SQUISH)
    add_subdirectory(squish)
endif()

if(BUILD_MAXIMUS)
    add_subdirectory(max)
endif()

# Installation of configuration files
install(DIRECTORY install_tree/
    DESTINATION ${CMAKE_INSTALL_PREFIX}
    USE_SOURCE_PERMISSIONS
    PATTERN "*.ctl"
    PATTERN "*.mec"
    PATTERN "*.mad"
    PATTERN "*.mex"
)

# Custom targets for convenience
add_custom_target(all_squish
    DEPENDS squish sqfix sqpack sqconv sqinfo sqset sstat sqreidx
    COMMENT "Building all Squish components"
)

add_custom_target(all_maximus
    DEPENDS max
    COMMENT "Building all Maximus components"
)

# Configuration recompilation target
configure_file(
    ${CMAKE_SOURCE_DIR}/cmake/Reconfig.cmake.in
    ${CMAKE_BINARY_DIR}/Reconfig.cmake
    @ONLY
)

configure_file(
    ${CMAKE_SOURCE_DIR}/cmake/CreateUserDB.cmake.in
    ${CMAKE_BINARY_DIR}/CreateUserDB.cmake
    @ONLY
)

add_custom_target(reconfig
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_BINARY_DIR}/Reconfig.cmake
    COMMENT "Recompiling configuration files"
    VERBATIM
)

# Installation and configuration compilation target
# Note: Commands execute sequentially and stop on first failure
add_custom_target(config_install
    COMMAND ${CMAKE_COMMAND} -E echo "Step 1: Installing files..."
    COMMAND ${CMAKE_COMMAND} --install ${CMAKE_BINARY_DIR}
    COMMAND ${CMAKE_COMMAND} -E echo "Step 2: Compiling configuration files..."
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target reconfig
    COMMAND ${CMAKE_COMMAND} -E echo "Configuration installation complete."
    COMMENT "Installing and compiling configuration files"
    VERBATIM
)

# Create user database if needed (run after config_install)
# Uses portable CMake script instead of shell-specific syntax
add_custom_target(create_userdb
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_BINARY_DIR}/CreateUserDB.cmake
    COMMENT "Creating user.bbs database if needed"
    VERBATIM
)

# Display configuration summary
message(STATUS "")
message(STATUS "Maximus CBCS Configuration Summary:")
message(STATUS "  Version: ${PROJECT_VERSION}")
message(STATUS "  Build Maximus: ${BUILD_MAXIMUS}")
message(STATUS "  Build Squish: ${BUILD_SQUISH}")
message(STATUS "  Build Utilities: ${BUILD_UTILITIES}")
message(STATUS "  Install prefix: ${CMAKE_INSTALL_PREFIX}")
message(STATUS "  Binary directory: ${MAXIMUS_BIN_DIR}")
message(STATUS "  Library directory: ${MAXIMUS_LIB_DIR}")
message(STATUS "  Configuration directory: ${MAXIMUS_ETC_DIR}")
message(STATUS "")
message(STATUS "Build commands:")
message(STATUS "  cmake -B build")
message(STATUS "  cmake --build build")
message(STATUS "  cmake --install build")
message(STATUS "")
message(STATUS "Component-specific builds:")
message(STATUS "  cmake --build build --target all_squish")
message(STATUS "  cmake --build build --target all_maximus")
message(STATUS "")
message(STATUS "Configuration targets:")
message(STATUS "  cmake --build build --target config_install  # Install + compile configs")
message(STATUS "  cmake --build build --target reconfig        # Recompile configs only")
message(STATUS "  cmake --build build --target create_userdb   # Create user database")
message(STATUS "")
