// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: fsend.c,v 1.1.1.1 2002/10/01 17:54:38 sdudley Exp $";
#pragma on(unreferenced)


static void near XmStatusTx(struct _xmstuff *px, unsigned flag)
{
    if (!px->filename)
        return;

    XmStatus(flag, px->do_crc,
             (px->protocol == PROTOCOL_YMODEMG ? px->block : px->last_ack) * (long)px->blocksize,
             px->start, px->protocol, px->size, px->last_ack, px->n_err, px->block);
}


static void near XmTxBlock(struct _xmstuff *px, long block_num, unsigned blocksize,
                           unsigned do_clear)
{
    word crc;
    byte *data = px->xm_buffer;
    byte *p, *e;
    byte sum;
    int got;



    while (p < e && carrier())
    {

        if (got > 0)
            p += (size_t)got;
        else
            Giveaway_Slice();
    }

    if (px->do_crc)
    {

        mdm_pputcw((byte)(crc >> 8));
        mdm_pputcw((byte)crc);

        dlogit(("@XmTxBlock; block=%ld, crc=%04x", px->block, crc));
    }
    else
    {

        mdm_pputcw(sum);

        dlogit(("@XmTxBlock; block=%ld, sum=%d", px->block, sum));
    }

    if (brk_trapped)
    {
        brk_trapped = 0;
        data[blocksize]++;
    }


        mdm_dump(DUMP_INPUT);
        XmTxClear();
    }
}


    offset = (px->block - 1L) * (long)px->blocksize;

    if (Btell(px->bf) != offset)
        Bseek(px->bf, offset, SEEK_SET);


    iGot = Bread(px->bf, px->xm_buffer, px->blocksize);

    if (iGot > 0)
    {

static void near XmPrepareBlock0(struct _xmstuff *px)
{
    struct stat st;
    struct _sealink *sh;
    char *p, *s;


    s = px->filename ? No_Path(px->filename) : "";

        st.st_mtime -= timezone + (daylight ? 60 : 0);
#endif
    }

    {

static unsigned near XmGetACK(struct _xmstuff *px)
{
    int bn, cb;

    if (px->protocol != PROTOCOL_SEALINK || px->block == 1)
    {
        px->last_ack = px->block - 1;
        return TRUE;
    }

    if ((bn = mdm_getct(100)) == -1)
    {
        dlogit(("@short ack 1"));
        return FALSE;
    }

    if ((cb = mdm_getct(100)) == -1)
    {
        dlogit(("@short ack 2"));
        return FALSE;
    }

    if ((byte)cb != (byte) ~(byte)bn)
    {
        dlogit(
            ("@ack err; %02x != ~%02x (%02x, %02x)", (int)cb, (int)bn, (byte)cb, (byte) ~(byte)bn));
        return FALSE;
    }


    px->last_ack = px->block - (long)(byte)(px->block - (long)bn);

    dlogit(("@Got A/N %ld (current: %ld)", px->last_ack, px->block));
    return TRUE;
}

        px->n_blocks++;

    px->do_crc = FALSE;
    px->need_ack = TRUE;
    px->ackless = FALSE;
    px->start = time(NULL);

    px->n_err = px->n_can = 0;


static unsigned near XmTxStop(struct _xmstuff *px)
{
    if ((prm.flags2 & FLAG2_STRICTXFER) && timeleft() <= 0)
    {
        logit(log_dl_exceeds_time);
        px->n_can = NUM_CAN;
        px->n_err = 10;
        return TRUE;
    }

    if (!loc_kbhit())
        return FALSE;

    if (loc_getch() != K_ESC)
        return FALSE;

    px->n_can = NUM_CAN;
    px->n_err = 10;

    return TRUE;
}


    if (px->protocol == PROTOCOL_YMODEMG)
        Delay(10);

    if (px->last_ch == XM_CAN)
        px->n_can++;
    else
        px->n_can = 2;
}


    if (px->protocol == PROTOCOL_XMODEM || px->protocol == PROTOCOL_XMODEM1K)
        return TRUE;


    XmPrepareBlock0(px);

    if (px->protocol == PROTOCOL_YMODEMG && !px->filename)
    {
        px->do_crc = TRUE;
        XmTxBlock(px, 0, 128, FALSE);
    }

    while (px->n_err < 10 && px->n_can < NUM_CAN && carrier())
    {

        if (!mdm_avail())
        {
            continue;
        }

                dlogit(("@hdr: autoACK ym-g"));
                px->ackless = TRUE;
                ch = XM_ACK;
                break;
            }
#endif
            break;


        if (ch == XM_ACK)
        {

            if (px->protocol == PROTOCOL_SEALINK)
                px->last_ack = 0;

            dlogit(("@hdr: got ack"));


            if (XmGetACK(px))
                break;
        }
    }

    dlogit(("@hdr: n_can=%d, n_err=%d", px->n_can, px->n_err));

    if (px->n_can >= NUM_CAN || px->n_err >= 10)
        XmSendCAN();

    return (px->n_err < 10 ? TRUE : FALSE);
}


    while (px->n_can < NUM_CAN && carrier())
    {
        {
            if (++n_eot > 10)
            {
                XmSendCAN();
                return FALSE;
            }

            mdm_pputcw(XM_EOT);


        if (!mdm_avail())
        {
            dlogit(("@eot: got nak"));


        default:
            dlogit(("@eot: got junk '%c' (%#02x)", ch == 0 ? ' ' : ch, ch));
        }

        px->last_ch = ch;
    }

    XmSendCAN();
    return FALSE;
}

static void near XmTxGotNAK(struct _xmstuff *px)
{

    if (px->ackless)
    {
        dlogit(("@ymodem-g nak; xfer aborted"));
        px->n_err = 10;
        return;
    }



    if (px->block == 0)
        px->block++;

    if (px->block > px->n_blocks)
        px->block = px->n_blocks;


    dlogit(("@after nak, block=%ld, last_ack=%ld", px->block, px->last_ack));

    if (px->protocol == PROTOCOL_SEALINK && px->block != 1)
        mdm_dump(DUMP_OUTPUT);
}


    if (!XmGetACK(px))
    {
        dlogit(("@short ack %ld", px->last_ack));
        return FALSE;
    }

    if (px->protocol == 'S' && px->block >= px->n_blocks)
        XmStatusTx(px, XS_SENT);

    dlogit(("@got ACK %ld", px->last_ack));
    px->n_err = 0;

    return TRUE;
}


    XmStatusTx(px, XS_SENT);

    dlogit(("@sending block %ld (last %ld)", px->block, px->last_ack));


static unsigned near XmTxBlocks(struct _xmstuff *px)
{
    int started = FALSE;
    long t1;
    int ch;


    while (px->last_ack < px->n_blocks && px->n_err < 10 && px->n_can < NUM_CAN && carrier())
    {

        if (px->ackless || px->block <= px->last_ack + px->window)
            if (px->block <= px->n_blocks)
            {
                if (!started)
                {
                    started = TRUE;
                    px->start = time(NULL);
                    ThruStart();
                }

                XmTxOneBlock(px);


                if (!mdm_avail())
                    continue;
            }

            {
                dlogit(("@timeout"));
                return FALSE;
            }


        do
        {
            ch = mdm_getc();

            dlogit(("@rec'd '%c' (%#02x)", ch, ch));

            switch (ch)
            {
            case XM_CAN:
                XmTxGotCAN(px);
                break;
#ifndef XM_NO_CRC
            case XM_G:
            case XM_C:
                if (!px->crc_set)

static unsigned XmTxFile(struct _xmstuff *px)
{

    if (!XmTxHeader(px))
        return FALSE;


        if (!XmTxBlocks(px))
            return FALSE;


unsigned XmTx(char *filename, word protocol, unsigned long ulFiles, unsigned long ulBytes,
              char *szRealName)
{
    struct _xmstuff x;
    byte *buf;

    long siz;
    unsigned ret;
    BFILE bf = NULL;

    if (filename && is_devicename(filename))
    {
        logit(log_cant_send_dev, filename);
        return FALSE;
    }


    if (filename && (bf = Bopen(filename, BO_RDONLY | BO_BINARY, BSH_DENYNO, 8192)) == NULL)
    {
        logit(cantfind, filename);
        return FALSE;
    }


    (void)memset(&x, 0, sizeof x);

    x.protocol = (sword)protocol;
    x.filename = filename;
    x.bf = bf;
    x.size = siz;
    x.xm_buffer = buf + 3;
    x.ulTotalFiles = ulFiles;
    x.ulTotalBytes = ulBytes;

    ThruStart();

    dlogit(("@XmTxFile(%s,%d)", filename ? filename : "(null)", x.protocol));

    XferWinNewFile(x.filename, x.size);


    if (filename)
        Bclose(bf);

    free(buf);

    return ret;
}
