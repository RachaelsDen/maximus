// SPDX-License-Identifier: GPL-2.0-or-later


cpp_begin()

#ifdef __WATCOMC__
#define grow_handles(n) wc_grow_handles(n)
#else
#define grow_handles(n)                                                                            \
    do                                                                                             \
    {                                                                                              \
        ;                                                                                          \
    } while (0)
#endif

    int _fast wc_grow_handles(int n);

cpp_end()
