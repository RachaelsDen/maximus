// SPDX-License-Identifier: GPL-2.0-or-later


#ifndef __STAMP_H_DEFINED
#define __STAMP_H_DEFINED

#include "compiler_align.h"
#include "compiler_details.h"
#include "typedefs.h"

#define STAMP_BITFIELD uint32
#define HALF_STAMP_BITFIELD uint16


union stamp_combo
{
    STAMP_BITFIELD ldate;
    union _stampu msg_st;
    struct _dos_st dos_st;
} PACKED;

typedef union stamp_combo SCOMBO;

