# mex - MEX scripting VM and compiler for Maximus CBCS
# Maximus Extension Language (MEX) runtime and compiler

# MEX VM library sources
set(MEXVM_SOURCES
    vm_run.c
    vm_heap.c
    vm_symt.c
    vm_read.c
    vm_opcvt.c
    vm_opflo.c
    vm_opfun.c
    vm_opmth.c
    vm_opstk.c
    vm_opstr.c
)

# MEX compiler sources
set(MEXC_SOURCES
    mex_main.c
    mex_lex.c
    mex_symt.c
    mex_misc.c
    mex_err.c
    # Semantic analysis
    sem_decl.c
    sem_func.c
    sem_scop.c
    sem_expr.c
    sem_flow.c
    sem_goto.c
    sem_gen.c
    sem_vm.c
)

# Build libmexvm.so (MEX virtual machine)
add_library(mexvm SHARED ${MEXVM_SOURCES})

target_include_directories(mexvm PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/slib
    ${CMAKE_SOURCE_DIR}/unix/include
    ${CMAKE_SOURCE_DIR}/msgapi
    ${CMAKE_SOURCE_DIR}/max
    ${CMAKE_SOURCE_DIR}/btree
    ${CMAKE_SOURCE_DIR}/prot
)

target_compile_definitions(mexvm PRIVATE
    HEAP_SIGNATURE
    DEBUGVM
)

set_target_properties(mexvm PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 3
    OUTPUT_NAME "mexvm"
)

# Use pre-generated parser files from source tree
# NOTE: mex_tab.c and mex_tab.h are checked into version control as they contain
# manual fixes for GCC 14.2 compatibility (see CLAUDE.md - MEX VM Compiler Fix).
# Do NOT regenerate these files unless you modify mex_tab.y and understand the fixes.
# The pre-generated files are used directly from the source directory.

# MEX compiler executable (uses pre-generated parser files from source tree)
add_executable(mex ${MEXC_SOURCES} ${CMAKE_CURRENT_SOURCE_DIR}/mex_tab.c)

target_include_directories(mex PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}  # For mex_tab.h and other MEX headers
    ${CMAKE_SOURCE_DIR}/slib
    ${CMAKE_SOURCE_DIR}/unix/include
    ${CMAKE_SOURCE_DIR}/msgapi
    ${CMAKE_SOURCE_DIR}/max
    ${CMAKE_SOURCE_DIR}/btree
    ${CMAKE_SOURCE_DIR}/prot
)

target_compile_definitions(mex PRIVATE
    UNIX
    # NOTE: MEX_PARSER is defined in mex_tab.c's prologue, not here
)

target_link_libraries(mex
    -Wl,--start-group
    msgapi
    maxlib
    -Wl,--end-group
    compat
    ${CURSES_LIBRARIES}
)

# Installation
install(TARGETS mexvm
    LIBRARY DESTINATION ${MAXIMUS_LIB_DIR}
    ARCHIVE DESTINATION ${MAXIMUS_LIB_DIR}
)

install(TARGETS mex
    RUNTIME DESTINATION ${MAXIMUS_BIN_DIR}
)
