// SPDX-License-Identifier: GPL-2.0-or-later



#ifdef FP_SEG
#undef FP_SEG
#endif

#ifdef FP_OFF
#undef FP_OFF
#endif

#define FP_SEG(p) ((unsigned short)((unsigned long)((char far *)p) >> 16))
#define FP_OFF(p) (unsigned short)((unsigned long)p & 0xffffu)
