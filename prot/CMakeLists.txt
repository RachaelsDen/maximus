# prot - File transfer protocols for Maximus CBCS
# Zmodem, Xmodem, Ymodem implementations

# Protocol library sources
set(PROT_SOURCES
    frecv.c
    fsend.c
    pdata.c
    rbsb.c
    rz.c
    sz.c
    zm.c
)

# Build libxfer.so
add_library(xfer SHARED ${PROT_SOURCES})

target_include_directories(xfer PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}/slib  # For generated compiler_details.h
    ${CMAKE_SOURCE_DIR}/slib
    ${CMAKE_SOURCE_DIR}/unix/include
    ${CMAKE_SOURCE_DIR}/lang
)

target_link_libraries(xfer
    PUBLIC
        maxlib
)

set_target_properties(xfer PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 3
    OUTPUT_NAME "xfer"
)

# Installation
install(TARGETS xfer
    LIBRARY DESTINATION ${MAXIMUS_LIB_DIR}
    ARCHIVE DESTINATION ${MAXIMUS_LIB_DIR}
)
