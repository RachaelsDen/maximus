// SPDX-License-Identifier: GPL-2.0-or-later



#define PRODUCTION
#define INSENSITIVE

#include "prog.h"
#include "rep.h"
#include <ctype.h>
#include <stdio.h>


                case '\x0a':
                case '\x0d':
                case '\x8d':
                    match = TRUE;

                    while (*string == '\x0a' || *string == '\x0d' || *string == '\x8d')
                        string++;

                    string--;

                    break;

                default:
                    if (string == orig_str)
                    {
                        match = TRUE;
                        string--;
                    }
                    else
                        match = FALSE;
                    break;
                }
            }

            switch (rtlf & (CHAR_NORM | CHAR_TABLE | CHAR_ANY))
            {
            case CHAR_NORM:
                if ((tolower(*string)) == rep->c[last_found])
                    match = TRUE;
                break;

            case CHAR_TABLE:
                if (rep->table[last_found][tolower(*string)])
                    match = TRUE;
                break;

            case CHAR_ANY:
                match = TRUE;
                break;

#ifndef PRODUCTION
            default:
                lputs("Bizarre error parsing compiled regular expression!");
                exit(ERROR_BIZARRE);
                break;
#endif
            }

            if (rtlf & CHAR_ZMORE)
            {
                if (!match)
                {
                    match = TRUE;

                    if (last_found)
                        string--;

                    break;
                }

                string++;
            }
            else if (rtlf & CHAR_1MORE)
            {
                if (madeone)
                {
                    if (!match)
                    {
                        match = TRUE;

                        if (last_found)
                            string--;

                        break;
                    }

                    string++;
                }
                else
                {
                    if (!match)
                    {
                        match = FALSE;
                        break;
                    }

                    string++;
                    madeone = TRUE;
                }
            }
            else
                break;
        }

        if (match)
            last_found++;
        else
        {
            if (last_found)
            {
                last_found = 0;
                continue;
            }
        }

        string++;

        if (last_found == rep->max_ch)
            return (string - last_found);
    }

