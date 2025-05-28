// SPDX-License-Identifier: GPL-2.0-or-later


#undef malloc
#undef realloc
#undef calloc
#undef free
#undef strdup

#define DBEXTRA (sizeof(int) * 4)
#define DB_SIZE (sizeof(int) * 2)

#ifdef __FLAT__
#define MAX_PTR 8192
#define KEY1 0x53440101
#define KEY2 0x21210202

#define PTR_TEXT "%08x"
#define POINTER(x) (long)(x)
#define PTR_SIZE "%08lx"
#define SPC_TEXT "%08lx"
#else
#define MAX_PTR 1024
#define KEY1 0x5344
#define KEY2 0x2121

#define PTR_TEXT "%04x:%04x"
#define POINTER(x) FP_SEG(x), FP_OFF(x)
#define PTR_SIZE "%04lx"
#define SPC_TEXT "%6ld"
#endif

struct _ptab
{
    void *p;

#if defined(__NEARCODE__) || defined(__FLAT__)
    void near *aat;
#else
    void far *aat;
#endif

    int delta;
    int size;
};

#ifdef __NEARCODE__
#define MODTYPE near
#else
#define MODTYPE far
#endif

#ifdef __WATCOMC__

#ifdef __386__
unsigned _get_sp(void);

    value[ax];

