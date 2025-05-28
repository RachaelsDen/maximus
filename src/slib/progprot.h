// SPDX-License-Identifier: GPL-2.0-or-later


cpp_begin()

int _fast fexist(char *filename);
long _fast fsize(char *filename);
int _fast lcopy(char *fromfile, char *tofile);
int _stdc hprintf(int handle, char *format, ...);
long _stdc zfree(char *drive);
int _fast getword(char *strng, char *dest, char *delim, int findword);
int _fast getwordq(char *strng, char *dest, char *delim, char quote, int findword);
byte *_fast avt2ansi(sword nw, sword old, char *ansi);
char *_stdc fancy_str(char *value);
char *_fast soundex(char *string);
int _fast any2dec(char *str, unsigned int radix);
char *_fast dec2any(unsigned int number, unsigned int radix);
int _fast isleap(int year);
char *_fast strrcat(char *string1, char *string2);
char *_fast make_fullfname(char *path);
char *_fast firstchar(char *strng, char *delim, int findword);
int _stdc xprintf(char *format, ...);
void _stdc xputs(char *s);
void _stdc xputch(char ch);
void pascal xputchr(char ch);
void _stdc putss(char *string);
char *_fast stristr(char *string, char *search);
int _fast stristrm(char *string, char *search[], int stopbit);
int _fast stricmpm(char *string, char *search[], int stopbit);
long _fast stristrml(char *string, char *search[], long stopbit);
int _fast nullptr(void);
long _stdc timerset(unsigned int duration);
int _stdc timeup(long timer);
int _fast sbsearch(char *key, char *base[], unsigned int num);
char *_fast memstr(char *string, char *search, unsigned lenstring, unsigned strlen_search);
void _fast ddos_timer(unsigned int duration);
void _fast ddos_priority(int value);
void _fast ddos_switch(void);
void _fast ddos_suspend(void);
void _fast ddos_resume(void);
void _fast ddos_kill(void);
void _fast ddos_clear_vkb(void);
void _fast ddos_send(char ch);
void _fast ddos_addkey(char ch);
void _fast ddos_key_disable(void);
void _fast ddos_key_enable(void);
int _fast ddos_herestat(void);
int _fast ddos_flipstat(void);
void _fast ddos_funcs_enable(void);
void _fast ddos_funcs_disable(void);
#if !(defined(OS_2) && defined(__FLAT__))
void _fast brktrap(void);
#endif
void _fast brktrapos2(void *err, int fDoTrap);
unsigned _fast is_device(int fd);
unsigned _fast is_devicename(char *filename);
void _stdc Vidfcur(void);
void _fast h_memmove(void huge *to, void huge *from, long size);
void pascal far f_memmove(void huge *from, void huge *to, unsigned short size);
int far pascal f_read(int handle, char far *buf, unsigned int len);
int far pascal f_write(int handle, char far *buf, unsigned int len);

void huge *_fast h_malloc(long size);
void _fast h_free(void huge *p);
long _fast h_read(int fd, char huge *buf, long size);
long _fast h_write(int fd, char huge *buf, long size);
void huge *_fast h_realloc(void huge *p, long newsize);
unsigned long cdecl thunk16to32(unsigned long addr16);
unsigned long cdecl thunk32to16(unsigned long addr32);
char *GetMaximus(int argc, char **argv, int iBadErrorlevel);

#ifdef __MSDOS__
sword far pascal shareloaded(void);
#else
#define shareloaded() TRUE
#endif

