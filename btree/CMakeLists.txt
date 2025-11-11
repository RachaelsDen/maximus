# btree - B-tree C++ classes for indexed data in Maximus CBCS
# Provides database and tracker functionality

# B-tree library sources (C++)
set(BTREE_SOURCES
    btree.cc
    bt_open.cc
    bt_look.cc
    bt_ins.cc
    bt_rem.cc
    btnode.cc
    palist.cc
    btreec.cc
    blkio.cc
    bbuf.cc
    blkiobuf.cc
    dllc.c
)

# Tracker/database library sources (C++)
set(TRACK_SOURCES
    dbase.cc
    dbasec.cc
    track.cc
    trackc.cc
    dllc.c
)

# Build libmaxbt.so (B-tree library)
add_library(maxbt SHARED ${BTREE_SOURCES})

target_include_directories(maxbt PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}/slib  # For generated compiler_details.h
    ${CMAKE_SOURCE_DIR}/slib
    ${CMAKE_SOURCE_DIR}/unix/include
)

# Use -nostartfiles to avoid conflict with dllc.c's _init function
target_link_options(maxbt PRIVATE -nostartfiles)

set_target_properties(maxbt PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 3
    OUTPUT_NAME "maxbt"
)

# Build libmaxdb.so (database/tracker library)
add_library(maxdb SHARED ${TRACK_SOURCES})

target_include_directories(maxdb PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}/slib  # For generated compiler_details.h
    ${CMAKE_SOURCE_DIR}/slib
    ${CMAKE_SOURCE_DIR}/unix/include
)

# Use -nostartfiles to avoid conflict with dllc.c's _init function
target_link_options(maxdb PRIVATE -nostartfiles)

set_target_properties(maxdb PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 3
    OUTPUT_NAME "maxdb"
)

# Build utility programs (optional)
# Note: C++ programs already have main() and don't need cppmain.cc wrapper
add_executable(trackexp trackexp.cc)
target_link_libraries(trackexp maxdb maxbt msgapi maxlib compat ${CURSES_LIBRARIES})

add_executable(trackimp trackimp.cc)
target_link_libraries(trackimp maxdb maxbt msgapi maxlib compat ${CURSES_LIBRARIES})

add_executable(bttest bttest.cc)
target_link_libraries(bttest maxdb maxbt msgapi maxlib compat ${CURSES_LIBRARIES})

# audit is commented out in original Makefile - has compilation errors, not built by default
# add_executable(audit audit.c cppmain.cc)
# target_link_libraries(audit maxdb maxbt msgapi maxlib compat ${CURSES_LIBRARIES})

# Installation
install(TARGETS maxbt maxdb
    LIBRARY DESTINATION ${MAXIMUS_LIB_DIR}
    ARCHIVE DESTINATION ${MAXIMUS_LIB_DIR}
)

install(TARGETS trackexp trackimp bttest
    RUNTIME DESTINATION ${MAXIMUS_BIN_DIR}
)
