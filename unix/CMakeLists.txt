# unix - UNIX compatibility layer for Maximus CBCS
# Emulates OS/2 DosXXX() and Windows NT calls using POSIX/curses

# Source files
set(COMPAT_SOURCES
    dosio.c
    winstr.c
    xpunix.c
    conio.c
    viocurses.c
    dosproc.c
    wincomm.c
    dossem.c
    process.c
)

# Build libcompat.so
add_library(compat SHARED ${COMPAT_SOURCES})

target_include_directories(compat PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/slib
)

target_link_libraries(compat
    PUBLIC
        ${CURSES_LIBRARIES}
)

set_target_properties(compat PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 3
    OUTPUT_NAME "compat"
)

# Installation
install(TARGETS compat
    LIBRARY DESTINATION ${MAXIMUS_LIB_DIR}
    ARCHIVE DESTINATION ${MAXIMUS_LIB_DIR}
    RUNTIME DESTINATION ${MAXIMUS_BIN_DIR}
)
