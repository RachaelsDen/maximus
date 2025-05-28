// SPDX-License-Identifier: GPL-2.0-or-later


#if defined(__POSIX__) && !defined(UNIX)
int stricmp(const char *s1, const char *s2);
int strnicmp(const char *s1, const char *s2, const int n);
char *strlwr(const char *s);
char *strupr(const char *s);
#endif
