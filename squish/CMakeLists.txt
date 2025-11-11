# squish - Squish FidoNet message tosser/scanner and utilities

# Main squish program sources
set(SQUISH_SOURCES
    squish.c
    s_abbs.c
    s_config.c
    s_scan.c
    s_toss.c
    s_pack.c
    s_squash.c
    s_match.c
    s_log.c
    s_misc.c
    s_hole.c
    s_link.c
    s_busy.c
    s_stat.c
    s_sflo.c
    s_thunk.c
    s_dupe.c
    bld.c
)

# Build squish executable
add_executable(squish ${SQUISH_SOURCES})

target_include_directories(squish PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/slib
    ${CMAKE_SOURCE_DIR}/unix/include
    ${CMAKE_SOURCE_DIR}/msgapi
)

target_link_libraries(squish
    -Wl,--start-group
    msgapi
    maxlib
    -Wl,--end-group
    compat
    ${CURSES_LIBRARIES}
)

# Build utility programs
add_executable(sqfix sqfix.c)
target_link_libraries(sqfix -Wl,--start-group msgapi maxlib -Wl,--end-group compat ${CURSES_LIBRARIES})

add_executable(sqpack sqpack.c)
target_link_libraries(sqpack -Wl,--start-group msgapi maxlib -Wl,--end-group compat ${CURSES_LIBRARIES})

add_executable(sqconv sqconv.c)
target_link_libraries(sqconv -Wl,--start-group msgapi maxlib -Wl,--end-group compat ${CURSES_LIBRARIES})

add_executable(sqinfo sqinfo.c)
target_link_libraries(sqinfo -Wl,--start-group msgapi maxlib -Wl,--end-group compat ${CURSES_LIBRARIES})

add_executable(sqset sqset.c)
target_link_libraries(sqset -Wl,--start-group msgapi maxlib -Wl,--end-group compat ${CURSES_LIBRARIES})

add_executable(sstat sstat.c)
target_link_libraries(sstat -Wl,--start-group msgapi maxlib -Wl,--end-group compat ${CURSES_LIBRARIES})

add_executable(sqreidx sqreidx.c)
target_link_libraries(sqreidx -Wl,--start-group msgapi maxlib -Wl,--end-group compat ${CURSES_LIBRARIES})

# Build shared libraries
add_library(killrcat SHARED killrcat.c)
target_include_directories(killrcat PRIVATE
    ${CMAKE_SOURCE_DIR}/slib
    ${CMAKE_SOURCE_DIR}/unix/include
    ${CMAKE_SOURCE_DIR}/msgapi
)
set_target_properties(killrcat PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 3
    OUTPUT_NAME "killrcat"
)

add_library(msgtrack SHARED msgtrack.c)
target_include_directories(msgtrack PRIVATE
    ${CMAKE_SOURCE_DIR}/slib
    ${CMAKE_SOURCE_DIR}/unix/include
    ${CMAKE_SOURCE_DIR}/msgapi
)
set_target_properties(msgtrack PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 3
    OUTPUT_NAME "msgtrack"
)

# Installation
install(TARGETS squish sqfix sqpack sqconv sqinfo sqset sstat sqreidx
    RUNTIME DESTINATION ${MAXIMUS_BIN_DIR}
)

install(TARGETS killrcat msgtrack
    LIBRARY DESTINATION ${MAXIMUS_LIB_DIR}
)
