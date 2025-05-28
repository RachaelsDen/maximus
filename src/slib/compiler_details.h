/* Automatically generated or static configuration header */

#ifndef _COMPILER_DETAILS_H
#define _COMPILER_DETAILS_H

/* Determine endianness using compiler macros */
#if defined(__BYTE_ORDER__) && __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
    #define PROJECT_LITTLE_ENDIAN 1
#elif defined(__BYTE_ORDER__) && __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
    #define PROJECT_BIG_ENDIAN 1
#else
    #error "Unable to determine system endianness"
#endif

/* Sanity check to make sure both aren’t defined */
#if defined(PROJECT_LITTLE_ENDIAN) && defined(PROJECT_BIG_ENDIAN)
    #error "Both PROJECT_LITTLE_ENDIAN and PROJECT_BIG_ENDIAN are defined! This is invalid."
#endif

#endif /* _COMPILER_DETAILS_H */
