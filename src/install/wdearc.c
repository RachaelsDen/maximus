// SPDX-License-Identifier: GPL-2.0-or-later


#include "ar.h"
#include "arc.h"
#include "install.h"
#include "prog.h"
#include "tui.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static uchar buffer[DICSIZ];
static void near err_read(char *name);

VWIN *arcwin = NULL;

extern FILE *ilog;

static void near err_open(char *name)
{
    WinErr("Fatal error opening `%s'", name);
    WinExit(1);
}

static void near err_read(char *name)
{
    WinErr("Fatal error reading from `%s'", name);
    WinExit(1);
}

void ArcWinOpen(void)
{
    if ((arcwin = WinOpen(0, 0, 15, 60, BORDER_DOUBLE, col(CWHITE | _BLUE), col(CYELLOW | _BLUE),
                          WIN_CENTRE)) == NULL)
    {
        NoMem();
    }

    make_crctable();
}

void ArcWinClose(void)
{
    WinClose(arcwin);
    arcwin = NULL;
}

void dearcit(char *arcname, char *path, word (*dupefile)(char *, char *, char *),
             word(near *doit)(char *fn))
{
    struct _fizhdr fh;
    char fname[120], orig[120];
    word j, n;
    word skip;

    if (ilog)
        fprintf(ilog, "Decompressing %s\n", arcname);

    WinPrintf(arcwin, " Decompressing %s\r\n", arcname);
    WinSync(arcwin, TRUE);

    if ((arcfile = fopen(arcname, "rb")) == NULL)
        err_open(arcname);

    while (fread((char *)&fh, sizeof(fh), 1, arcfile) == 1)
    {
        origsize = compsize = unpackable = 0;

        if (fread(orig, fh.fnlen, 1, arcfile) != 1)
            err_read(arcname);

        orig[fh.fnlen] = '\0';
        strcpy(fname, orig);


        skip = FALSE;

        if (fexist(fname))
            skip = dupefile ? (*dupefile)(fname, path, orig) : TRUE;

        if (doit && !skip)
            skip = !(*doit)(orig);

            char *p, *e;

            for (p=buffer, e=p+n; p < e; p++)
              *p=~*p;
          }
#endif
                }

                fwrite_crc(buffer, n, outfile);

                origsize -= n;

                if (origsize)
                {
                    for (j = 10; j; j--)
                        WinPutc(arcwin,
                                (byte)(fh.origsize * (long)j >= origsize * 10L ? 'Û' : '°'));

                    for (j = 10; j; j--)
                        WinPutc(arcwin, '\b');

                    WinSync(arcwin, TRUE);
                }
            }

            if (crc != fh.crc)
                WinErr("CRC error");

            flush_handle(outfile);
            set_fdt(fileno(outfile), &fh.date);

            fclose(outfile);
        }

        WinPuts(arcwin, "Done.     \r\n");
        WinSync(arcwin, TRUE);
    }

    fclose(arcfile);
}

