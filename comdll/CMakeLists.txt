# comdll - Communications drivers for Maximus CBCS
# Telnet and IP communication support

# Option for telnet vs raw IP
option(USE_TELNET "Use telnet protocol (vs raw IP)" ON)

# Build libcomm.so
if(USE_TELNET)
    add_library(comm SHARED telnetcomm.c)
    target_compile_definitions(comm PRIVATE TELNET)
else()
    add_library(comm SHARED ipcomm.c)
endif()

target_include_directories(comm PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/slib
    ${CMAKE_SOURCE_DIR}/unix/include
)

set_target_properties(comm PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 3
    OUTPUT_NAME "comm"
)

# Custom target to build telnetcomm.c from ipcomm.c
add_custom_command(
    OUTPUT telnetcomm.c
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/ipcomm.c telnetcomm.c
    DEPENDS ipcomm.c
    COMMENT "Copying ipcomm.c to telnetcomm.c"
)

# Installation
install(TARGETS comm
    LIBRARY DESTINATION ${MAXIMUS_LIB_DIR}
    ARCHIVE DESTINATION ${MAXIMUS_LIB_DIR}
)
