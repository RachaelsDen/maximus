# util - Utility programs for Maximus CBCS
# MAID, MECCA, SILT, and other configuration tools

# Generate mecca_vb.h from mecca_vb.h.in
add_custom_command(
    OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/mecca_vb.h
    COMMAND sort < ${CMAKE_CURRENT_SOURCE_DIR}/mecca_vb.h.in > ${CMAKE_CURRENT_SOURCE_DIR}/mecca_vb.h
    DEPENDS mecca_vb.h.in
    COMMENT "Generating mecca_vb.h"
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

# Create symlinks for shared sources from max directory
add_custom_command(
    OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/l_attach.c
    COMMAND ${CMAKE_COMMAND} -E create_symlink ../max/l_attach.c ${CMAKE_CURRENT_SOURCE_DIR}/l_attach.c
    DEPENDS ${CMAKE_SOURCE_DIR}/max/l_attach.c
    COMMENT "Creating symlink for l_attach.c"
)

add_custom_command(
    OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/max2priv.c
    COMMAND ${CMAKE_COMMAND} -E create_symlink ../max/max2priv.c ${CMAKE_CURRENT_SOURCE_DIR}/max2priv.c
    DEPENDS ${CMAKE_SOURCE_DIR}/max/max2priv.c
    COMMENT "Creating symlink for max2priv.c"
)

# MAID - Language file compiler
add_executable(maid maid.c)
target_link_libraries(maid maxlib compat ${CURSES_LIBRARIES})

# MECCA - Menu compiler
add_executable(mecca mecca.c init.c mecca_vb.h)
target_link_libraries(mecca -Wl,--start-group msgapi maxlib -Wl,--end-group compat ${CURSES_LIBRARIES})

# ACCEM - Reverse MECCA compiler
add_executable(accem accem.c init.c mecca_vb.h)
target_link_libraries(accem -Wl,--start-group msgapi maxlib -Wl,--end-group compat ${CURSES_LIBRARIES})

# ANSI2BBS - ANSI to BBS format converter
add_executable(ansi2bbs ansi2bbs.c)
target_compile_definitions(ansi2bbs PRIVATE ANSI2BBS)
target_link_libraries(ansi2bbs -Wl,--start-group msgapi maxlib -Wl,--end-group compat ${CURSES_LIBRARIES})

# ANSI2MEC - ANSI to MECCA format converter
add_executable(ansi2mec ansi2bbs.c)
target_compile_definitions(ansi2mec PRIVATE ANSI2MEC)
target_link_libraries(ansi2mec -Wl,--start-group msgapi maxlib -Wl,--end-group compat ${CURSES_LIBRARIES})
set_target_properties(ansi2mec PROPERTIES OUTPUT_NAME ansi2mec)

# SCANBLD - Message scan builder
add_executable(scanbld scanbld.c cppmain.cc)
target_link_libraries(scanbld -Wl,--start-group msgapi maxlib -Wl,--end-group compat ${CURSES_LIBRARIES})

# CVTUSR - User file converter
add_executable(cvtusr cvtusr.c cppmain.cc cvt_misc.c)
target_link_libraries(cvtusr -Wl,--start-group msgapi maxlib -Wl,--end-group compat ${CURSES_LIBRARIES})

# EDITCALL - Call log editor
add_executable(editcall editcall.c)
target_link_libraries(editcall -Wl,--start-group msgapi maxlib -Wl,--end-group compat ${CURSES_LIBRARIES})

# MR - Message reader utility
add_executable(mr mr.c)
target_link_libraries(mr -Wl,--start-group msgapi maxlib -Wl,--end-group compat ${CURSES_LIBRARIES})

# FIXLR - Fix lastread pointers
add_executable(fixlr fixlr.c)
target_link_libraries(fixlr -Wl,--start-group msgapi maxlib -Wl,--end-group compat ${CURSES_LIBRARIES})

# SETLR - Set lastread pointers
add_executable(setlr setlr.c)
target_link_libraries(setlr -Wl,--start-group msgapi maxlib -Wl,--end-group compat ${CURSES_LIBRARIES})

# FB - File base utility
add_executable(fb fb.c)
target_link_libraries(fb -Wl,--start-group msgapi maxlib -Wl,--end-group compat ${CURSES_LIBRARIES})

# SILT - Control file compiler (max.ctl -> max.prm)
set(SILT_SOURCES
    silt.c
    cppmain.cc
    s_equip.c
    s_matrix.c
    s_menu.c
    s_misc.c
    s_parse.c
    s_sessio.c
    s_system.c
    s_reader.c
    s_lang.c
    s_colour.c
    s_proto.c
    s_marea.c
    s_farea.c
    s_heap.c
    s_area.c
    s_access.c
    l_attach.c
    max2priv.c
)

add_executable(silt ${SILT_SOURCES})
target_include_directories(silt PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/max
    ${CMAKE_SOURCE_DIR}/lang
)
target_link_libraries(silt maxdb maxbt -Wl,--start-group msgapi maxlib -Wl,--end-group compat ${CURSES_LIBRARIES})

# Special source file properties for files needing language includes
set_source_files_properties(
    max2priv.c l_attach.c
    PROPERTIES
    COMPILE_FLAGS "-I${CMAKE_SOURCE_DIR}/lang"
)

# Installation - only install essential utilities by default
install(TARGETS maid mecca accem silt fb ansi2bbs
    RUNTIME DESTINATION ${MAXIMUS_BIN_DIR}
)

# Optional installation of all utilities
install(TARGETS ansi2mec scanbld cvtusr editcall mr fixlr setlr
    RUNTIME DESTINATION ${MAXIMUS_BIN_DIR}
    OPTIONAL
)
