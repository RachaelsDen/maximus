// SPDX-License-Identifier: GPL-2.0-or-later



#include "alc.h"
#include "prog.h"
#include "rep.h"
#include <stdio.h>
#include <string.h>

int _fast Compile_REP(char *exp, struct _rep *rep)
{
    char found, neg, start, end;

    int ch, x;

    for (ch = 0; *exp && ch < MAX_REP; ch++)
    {
        rep->table[ch] = NULL;
        rep->type[ch] = 0;

        switch (*exp)
        {
        case '^':
            rep->type[ch] |= CHAR_SOL;
            break;

        case '$':
            rep->type[ch] |= CHAR_EOL;
            break;

        case '.':
            rep->type[ch] |= CHAR_ANY;
            break;

        case '*':
            if (ch)
            {
                if (rep->type[ch - 1] & (CHAR_ZMORE | CHAR_1MORE))
                    return CERR_2R;

                rep->type[ch - 1] |= CHAR_ZMORE;
            }
            else
                return CERR_NOREPEAT;

            ch--;
            break;

        case '+':
            if (ch)
            {
                if (rep->type[ch - 1] & (CHAR_ZMORE | CHAR_1MORE))
                    return CERR_2R;

                rep->type[ch - 1] |= CHAR_1MORE;
            }
            else
                return CERR_NOREPEAT;

            ch--;
            break;

            if ((rep->table[ch] = (char *)malloc(TABLE_LEN)) == NULL)
                return CERR_NOMEM;

            memset(rep->table[ch], '\x00', TABLE_LEN);

            if (*++exp == '^')
            {
                neg = TRUE;
                exp++;
            }
            else
                neg = FALSE;

            if (*exp == ']')
                return CERR_EMPTYSET;

            found = FALSE;

            while (*exp)
            {
                if (*exp == ']' && ((*(exp - 1) != QUOTE) || (*(exp - 2) == QUOTE)))
                {
                    found = TRUE;
                    break;
                }

                switch (*exp)
                {
                case '^':
                    rep->type[ch] |= CHAR_SOL;
                    break;

                case '$':
                    rep->type[ch] |= CHAR_EOL;
                    break;

                case QUOTE:

                default:
                    if (*(exp + 1) == '-')
                    {
                        start = *exp;
                        end = *(exp += 2);

                        if (start < end)
                        {
                            for (x = start; x <= end; x++)
                                rep->table[ch][x] = TRUE;
                        }
                        else
                        {
                            for (x = end; x >= start; x--)
                                rep->table[ch][x] = TRUE;
                        }
                    }
                    else
                        rep->table[ch][*exp] = TRUE;
                    break;
                }

                exp++;
            }

            if (!found)
                return CERR_NOTERM;

            if (neg)
                for (x = 0; x < TABLE_LEN; x++)
                    rep->table[ch][x] = (char)((rep->table[ch][x] == FALSE) ? TRUE : FALSE);
            break;

        case QUOTE:

        default:
            rep->type[ch] |= CHAR_NORM;
            rep->c[ch] = *exp;
            break;
        }

        exp++;
    }

    rep->max_ch = ch;

    if (ch == MAX_REP)
        return -1;
    else
        return 0;
}
