# slib - Shared library for Maximus CBCS
# String handling, file I/O, platform abstraction

# Source files (converted from OBJS in Makefile)
set(SLIB_SOURCES
    hmalloc.c hmemmove.c hread.c
    areaapi.c userapi.c md5.c
    nopen.c fd2n.c isdevice.c
    brktrap.c ncheck.c timer.c 1stchar.c
    getword.c avatar.c fncystr.c months.c
    strftim.c fexist.c stristr.c putss.c
    zfree.c qksort.c memstr.c hprintf.c
    tolower.c toupper.c savedir.c xprintf.c
    xputs.c crep.c strstrx.c
    aname.c ffind.c fdate.c gedate.c
    priv.c getdisk.c setdisk.c weekday.c
    get_fdt.c set_fdt.c c2s.c makedir.c
    sfopen.c iqsort.c shfopen.c gwordq.c
    ffname.c sbs.c isleap.c tdelay.c
    dmalloc.c noise.c tune.c date2bin.c
    dosdate.c flush.c canon.c win.c
    cvtdate.c trail.c parsenn.c qslist.c
    lcopy.c fnsplit.c uniqren.c mktemp.c
    soundex.c address.c mktime.c cencode.c
    ieee2lng.c ieee2msb.c lng2ieee.c msb2ieee.c
    adj_user.c win_pick.c arc_def.c coreleft.c
    smalloc.c strocpy.c
    cshopen.c crc32.c crc16.c strrstr.c
    crit.c
    skiplist.c acomp.c arc_cmd.c
    arcmatch.c bfile.c bprintf.c _ctype.c
    setfsize.c cstrupr.c strnncpy.c zeller.c
    getmax.c prmapi.c strbuf.c
    unix_misc.c vio.c align.c
    os2file.c os2key.c
)

# Build libmax.so (main shared library)
add_library(maxlib SHARED ${SLIB_SOURCES})

target_include_directories(maxlib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}/slib  # For generated compiler_details.h
    ${CMAKE_SOURCE_DIR}/unix/include
    ${CMAKE_SOURCE_DIR}/max
    ${CMAKE_SOURCE_DIR}/msgapi
)

set_target_properties(maxlib PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 3
    OUTPUT_NAME "max"
)

# Build libsmserial.so (serial communications)
add_library(smserial SHARED smserial.c)

target_include_directories(smserial PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}/slib  # For generated compiler_details.h
    ${CMAKE_SOURCE_DIR}/unix/include
)

set_target_properties(smserial PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 3
    OUTPUT_NAME "smserial"
)

# Installation
install(TARGETS maxlib smserial
    LIBRARY DESTINATION ${MAXIMUS_LIB_DIR}
    ARCHIVE DESTINATION ${MAXIMUS_LIB_DIR}
    RUNTIME DESTINATION ${MAXIMUS_BIN_DIR}
)
