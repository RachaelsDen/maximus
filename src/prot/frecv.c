// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: frecv.c,v 1.2 2003/06/05 01:16:01 wesgarland Exp $";
#pragma on(unreferenced)

#define PROT_LOG
#define MAX_LANG_protocols
#define MAX_INCL_COMMS

#include "f_up.h"
#include "keys.h"
#include "mm.h"
#include "pdata.h"
#include "prog.h"
#include "win.h"
#include "xmodem.h"
#include <fcntl.h>
#include <io.h>
#include <share.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>

#if defined(PROT_LOG) && defined(DEBUGX)
#define mdm_fpputcw(ch) mdm_pputcw(ch), logit("@sent char %02x ('%c')", ch, ch)
#else
#define mdm_fpputcw(ch) mdm_pputcw(ch)
#endif

static unsigned near XmRxStop(struct _xmrx *px)
{
    if (!loc_kbhit())
        return FALSE;

    if (loc_getch() != K_ESC)
        return FALSE;

    px->n_can = NUM_CAN;
    px->n_err = 10;

    return TRUE;
}


static void near XmRxSendPacketACK(unsigned do_complement, int ch, long block)
{
    byte temp[5];
    char *p, *e;
    int got;


    temp[0] = (byte)ch;
    temp[1] = (byte)(block & 0xff);
    temp[2] = (byte) ~(block & 0xff);

    p = temp;
    e = p + 3;


static void near XmRxSendACK(struct _xmrx *px, long block)
{
    px->n_nak = 0;

    dlogit(("@XmRxSendACK - sent ack %d", block));

        case 0:
            mdm_fpputcw(XM_G);

        if (block != -1)
            XmStatusRx(px, XS_RECV);

        XmRxSendPacketACK(px->protocol == PROTOCOL_SEALINK, XM_ACK,
                          block == -1 ? px->block : block);
    }
}


    if ((++px->n_nak % 5) == 0 && !px->crc_set && px->protocol != PROTOCOL_YMODEM &&
        px->protocol != PROTOCOL_YMODEMG && px->protocol != PROTOCOL_SEALINK)
    {
        px->do_crc = !px->do_crc;
        dlogit(("@XmRxSendNAK: switching to %s", px->do_crc ? "crc" : "checksum"));
    }


    XmRxSendPacketACK(px->protocol == PROTOCOL_SEALINK && px->block != 0, chNAK,
                      block == -1 ? px->block : block);


static unsigned near XmRxGetBlockComplement(byte *pbn)
{
    int bn, bc;


    if ((byte)bn != (byte) ~(byte)bc)
    {
        dlogit(("@XmRxGetBlockComplement - garbled block number"));
        return FALSE;
    }

    *pbn = (byte)bn;

    return TRUE;
}


    for (p = buf, e = buf + block_size; p < e; p++)
        crc = updcrc(*p, crc);


    return crc;
}


static void near XmRxShowName(struct _xmrx *px, char *filename)
{
    char temp[PATHLEN];

    if (filename && *filename)
    {
        strcpy(temp, px->path);
        strcat(temp, px->filename);
    }
    else
        strcpy(temp, xmodem_unknown_filename);

    XferWinNewFile(temp, px->size);
}


    if (px->protocol == PROTOCOL_XMODEM || px->protocol == PROTOCOL_XMODEM1K)
        return TRUE;

            *px->pusEOB = TRUE;
        }
    }
        }



                tim = atoi(p);
                ptm = localtime(&tim);
                TmDate_to_DosDate(ptm, &px->date);
            }
        }
    }


        strocpy(px->filename + 1, px->filename);
        *px->filename = '*';
        return FALSE;
    }

    if (px->size != -1L && px->size > (zfree(px->path) - (long)prm.k_free * 1000L))
    {
        logit(log_no_space_to_rec, px->filename);
        return FALSE;
    }


static unsigned near XmRxValidateBlock(struct _xmrx *px, unsigned block_size)
{
    byte sum, hdr_sum;
    word crc, hdr_crc;

    if (px->do_crc)
    {
        crc = XmRxCalcCRC(px->xm_buffer, block_size);

        hdr_crc = (word)((word)px->xm_buffer[block_size] << 8 |
                         (word)(byte)px->xm_buffer[block_size + 1]);

}

    long t2 = t1;
    byte bn;
    byte *p, *e;

    {
        dlogit(("@XmRxGetBlockData - block num out of sync. Current=%ld (%d), got=%d", px->block,
                (byte)px->block, bn));


    real_block_size = block_size;

    if (px->do_crc)
        block_size += 2;
    else
        block_size++;


    if (px->protocol == PROTOCOL_SEALINK && bn != (byte)px->block)

    if (!XmRxValidateBlock(px, real_block_size))
        return FALSE;


    if (px->block == 0)
    {

            Delay(150);

            XmSendCAN();
            px->n_can = NUM_CAN;
            return FALSE;
        }
    }
    else
    {
        dlogit(("@XmRxGetBlockData - got block %d", px->block));


static unsigned XmRxGetBlock(struct _xmrx *px)
{
    int rc;
    int fDoTelixKludge;

        case XM_STX:
            px->tSendNAK = timerset(1000);

            if (!px->crc_set)
            {
                px->start = time(NULL);
                ThruStart();
            }

            dlogit(("@XmRxGetBlock - got %s", px->ch == XM_SOH ? "SOH" : "STX"));


            if ((rc = XmRxGetBlockData(px, px->ch == XM_SOH ? 128 : 1024)) == 42)
            {
            {
                if (px->block == 0)
                {

                    if (*px->filename && px->block == 0)
                        XmRxSendNAK(px, 0);

                    px->block++;
                }
                else
                {
                    XmRxSendACK(px, px->block++);


                    if (px->protocol == PROTOCOL_YMODEM && px->block == 1 && *px->filename)
                    {
                        XmRxSendNAK(px, 0);
                    }
                }

                px->crc_set = TRUE;
            }
            else if (px->n_can < NUM_CAN)
            {
                px->crc_set = TRUE;

                if (px->protocol != PROTOCOL_YMODEMG)
                    XmRxSendNAK(px, px->block);


#if 0
          long lTimeWait;
          int ch;


          if (px->size != -1L && px->block < px->size/128L)
          {
              dlogit(("@XmRxGetBlock - EOT at bad posn; cur=%ld end=%ld",
                     (long)px->block, (long)px->size));

              XmRxSendNAK(px, px->block);
              px->ch=XM_NAK;
              break;
          }
#else
                if (px->block && px->fGotEOT < 2)
                {
                    px->fGotEOT++;
                    dlogit(("@XmRxGetBlock - got 1st eot, send nak"));

                    XmRxSendNAK(px, px->block);
                    mdm_dump(DUMP_INPUT);

                    if ((px->ch = mdm_getct(500)) != XM_EOT)
                    {
                        dlogit(("@XmRxGetBlock - didn't get 2nd eot; got %#02x", px->ch));
                        fDoTelixKludge = TRUE;
                        break;
                    }
                }

#endif

            if (px->protocol == PROTOCOL_XMODEM || px->protocol == PROTOCOL_XMODEM1K ||
                px->size == -1 || px->received >= px->size)
            {
                if (px->protocol == PROTOCOL_SEALINK)
                {
                    Delay(50);
                    mdm_fflush();
                }


                if (px->block == 0 && !*px->pusEOB &&
                    (px->protocol == PROTOCOL_YMODEM || px->protocol == PROTOCOL_YMODEMG))
                {
                    XmSendCAN();
                    px->n_can = NUM_CAN;
                    return FALSE;
                }

                dlogit(("@sending plain ACK"));
                XmRxSendACK(px, -1);

                if (px->fGotEOT == 2 && px->protocol == PROTOCOL_SEALINK)
                {
                    int ch;

                    Delay(100);
                    mdm_fpputcw('C');
                    Delay(250);

                    if ((ch = mdm_getct(500)) == XM_EOT)
                    {
                        dlogit(("@got 500 eot"));
                        XmRxSendACK(px, -1);
                        Delay(300);
                    }
                    else
                    {
                        dlogit(("@got 500 '%c'", ch));
                    }

                    mdm_dump(DUMP_INPUT);
                }

                if (px->protocol == PROTOCOL_SEALINK && *px->pusEOB)
                {
                    int ch;


                    Delay(100);
                    mdm_fpputcw('C');

                    if ((ch = mdm_getct(300)) == XM_SOH)
                    {
                        px->ch = ch;
                        *px->pusEOB = FALSE;
                        fDoTelixKludge = TRUE;
                        break;
                    }

                    mdm_fpputcw('\b');
                    mdm_fpputcw(' ');
                    mdm_fpputcw('\b');
                }
            }

            XmStatusRx(px, XS_GOTEOT);
            dlogit(("@XmRxGetBlock - eot sequence done"));

            dlogit(("@XmRxGetBlock - got junk %#02x", px->ch));
        }
    } while (fDoTelixKludge && carrier());

    return TRUE;
}


    do
    {
        if (timeup(px->tSendNAK))
        {
            dlogit(("@XmRxBlocks - timeout, sending NAK"));
            XmRxSendNAK(px, px->block);
            px->tSendNAK = timerset(px->crc_set ? 1000 : 300);
        }

        if ((px->ch = mdm_getct(100)) != -1)
        {
            XmRxGetBlock(px);
            px->last_ch = px->ch;
        }
    } while (carrier() && px->n_nak < NUM_NAK && px->n_can < NUM_CAN && px->ch != XM_EOT &&
             !XmRxStop(px));

    dlogit(("@XmRxBlocks: n_nak=%d, n_can=%d", px->n_nak, px->n_can));

    if (px->n_nak >= NUM_NAK || px->n_can >= NUM_CAN || !carrier())
    {
        XmSendCAN();
        return FALSE;
    }

    return TRUE;
}

    px->crc_set = FALSE;
    px->ackless = FALSE;
    px->n_err = px->n_can = 0;
    *px->pusEOB = FALSE;
    Get_Dos_Date(&px->date);

    switch (px->protocol)
    {
    case PROTOCOL_XMODEM:
    case PROTOCOL_XMODEM1K:

static unsigned near XmRxFile(struct _xmrx *px)
{
    if (!XmRxInit(px))
        return FALSE;

    if (!XmRxBlocks(px))
        return FALSE;

    return TRUE;
}


    if ((buf = malloc(MAX_XMODEM_BUF)) == NULL)
    {
        logit(mem_none);
        return FALSE;
    }


    (void)memset(&x, 0, sizeof x);

    x.protocol = (sword)protocol;
    x.path = path;

    strcpy(x.filename, filename ? filename : (byte *)"");

    x.fd = fd;
    x.size = -1L;
    x.xm_buffer = buf;
    x.pusEOB = pusEOB;

    dlogit(("@XmRxFile(%s)", filename ? filename : "-* null *-"));



    if (path)
    {

    return ret;
}
