#ifndef WINSTR_H_INCLUDED
#define WINSTR_H_INCLUDED

#ifdef __cplusplus
extern "C"
{
#endif

    int stricmp(const char *a, const char *b);
    int strnicmp(const char *a, const char *b, size_t n);
    char *strupr(char *s);
    char *strlwr(char *s);
    char *itoa(int value, char *buffer, int radix);
    int memicmp(const void *p, const void *q, size_t length);

#ifdef __cplusplus
}
#endif

#endif /* WINSTR_H_INCLUDED */
