# msgapi - FidoNet message API for Maximus CBCS
# Used by both Maximus and Squish for message base access

# Source files (from APIOBJS in Makefile)
set(MSGAPI_SOURCES
    msgapi.c
    sq_area.c
    sq_msg.c
    sq_read.c
    sq_write.c
    sq_kill.c
    sq_uid.c
    sq_lock.c
    sq_misc.c
    sq_help.c
    sq_idx.c
    api_sdm.c
    bld.c
    structrw.c
)

# Build libmsgapi.so
add_library(msgapi SHARED ${MSGAPI_SOURCES})

target_include_directories(msgapi PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/slib
    ${CMAKE_SOURCE_DIR}/unix/include
)

target_link_libraries(msgapi
    PUBLIC
        maxlib
)

set_target_properties(msgapi PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 3
    OUTPUT_NAME "msgapi"
)

# Installation
install(TARGETS msgapi
    LIBRARY DESTINATION ${MAXIMUS_LIB_DIR}
    ARCHIVE DESTINATION ${MAXIMUS_LIB_DIR}
    RUNTIME DESTINATION ${MAXIMUS_BIN_DIR}
)
