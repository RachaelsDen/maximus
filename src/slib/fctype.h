// SPDX-License-Identifier: GPL-2.0-or-later



#define f_islwr(c) (_to_lwr[c] == c)
#define f_isupr(c) (_to_upr[c] == c)

#define f_tolwr(c) (_to_lwr[c])
#define f_toupr(c) (_to_upr[c])

extern unsigned char _to_lwr[256];
extern unsigned char _to_upr[256];
