// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: s_misc.c,v 1.2 2003/06/05 03:13:40 wesgarland Exp $";
#pragma on(unreferenced)

#define NOVARS
#ifdef SWAP
#include "../swap/swap.h"
#endif
#include "alc.h"
#include "crc.h"
#include "dr.h"
#include "max.h"
#include "msgapi.h"
#include "prog.h"
#include "s_dupe.h"
#include "squish.h"
#include <ctype.h>
#include <dos.h>
#include <errno.h>
#include <fcntl.h>
#include <io.h>
#include <process.h>
#include <share.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>

#if defined(__TURBOC__) || defined(__MSC__)

        NoMem();

    orig_buffer = buffer;
}

void Free_Buffer(void)
{
    if (buffer)
        free(buffer);

    buffer = orig_buffer = NULL;
}


void SetPktOfs(long ofs) { read_ofs = ofs; }


long GetPktOfs(void) { return (read_ofs - (long)chs); }

static void near Skip_To_Nul(int pktfile, char *buf, unsigned buflen)
{
    char *s;
    unsigned got;

    for (s = NULL; (got = (unsigned)fastread(pktfile, buf, buflen)) != 0;)
        if ((s = memchr(buf, '\0', got)) != NULL)
            break;

    if (s)
        (void)lseek(pktfile, -((long)got - (long)(s - buf)) + 1L, SEEK_CUR);
}

char *Get_To_Nul(void *msg, unsigned int *length, int pktfile, int gp)
{
    byte *b = buffer + sizeof(XMSG);
    byte *p, *s = NULL;
    unsigned got;

    if (pktfile == -1)
    {
        orig_buffer = buffer;
        chs = 0;
        return NULL;
    }

    if (gp)
    {

            (void)memmove(b, orig_buffer, chs);


                chs += got;
                read_ofs += (long)got;
            }

            orig_buffer = b;
        }

        got = min(sizeof(struct _pktprefix), chs);


        orig_buffer += got;
        chs -= got;


    if (msg)
    {
        (void)memmove(buffer, msg, sizeof(XMSG));
        (void)memmove(b, orig_buffer, chs);
        orig_buffer = b;
    }

    if (!chs)
    {
        orig_buffer = b;
        got = (unsigned)fastread(pktfile, b, maxmsglen);

        if (got > 0)
        {
            chs += got;
            read_ofs += (long)got;
        }
    }

    for (;;)
    {
        if ((p = memchr(orig_buffer, '\0', chs)) != NULL)
        {

                s = orig_buffer;
                p = orig_buffer + chs;

    for (e = s + strlen(s); s < e; s++)
        if (*s > ' ' && *s < 127)
            crc = xcrc32(*s, crc);

    return crc;
}

void DiskFull(struct _cfgarea *ar)
{
    S_LogMsg("!Error writing msg to %s; no disk space!", ar->name);

    bad_packet = TRUE;


void _fast NoMem(void)
{
    S_LogMsg("!Ran out of memory.  Aborting abnormally. (mem=%ld)", coreleft());

    (void)printf("\nRan out of memory!\n");

    S_LogClose();
    exit(ERL_ERROR);
}


char *GetNextToken(byte *start, byte *buf, byte *token)
{
    byte *p, *s;

    if (buf == NULL)
        return NULL;

    p = buf;

    while (p && (p = strstr(p, token)) != NULL)
    {

        if (p[-1] == '\x0d' || p[-1] == '\x0a' || (byte)p[-1] == (byte)0x8d)

byte *GetTearPos(byte *msgbuf, byte **endtear)
{
    byte *found, *estart;
    byte *sv;
    byte *s;

    found = msgbuf;

    while ((found = GetNextToken(msgbuf, found, "---")) != NULL)
    {
        s = found;

            s = found + strlen(found);


        if (s[0] == ' ' && s[2] == ' ' && s[3] == 'O' && s[4] == 'r' && s[5] == 'i' &&
            s[6] == 'g' && s[7] == 'i' && s[8] == 'n' && s[9] == ':')
        {
            extern char *seen_by_str;



            if (*s == '\x0d')
                s++;

            estart = s;


            if (*s != '\0')
                return NULL;

            if (endtear)
    }

    if (endtear)
        *endtear = NULL;


    if (zone > 0xfff && zone != 0xffff)
        zone = config.addr->zone;


            if ((len = (word)strlen(outname)) != 3)
                while (outname[len] == '\\' || outname[len] == '/')
                    outname[len--] = '\0';


    gmt = time(NULL);
    lt = localtime(&gmt);

    ph->dest_node = (sword)them_node;
    ph->year = (word)lt->tm_year + 1900;
    ph->month = (word)lt->tm_mon;
    ph->day = (word)lt->tm_mday;
    ph->hour = (word)lt->tm_hour;
    ph->minute = (word)lt->tm_min;
    ph->second = (word)lt->tm_sec;
    ph->baud = 0;
    ph->ver = PKTVER;
    ph->orig_net = (sword)us->net;
    ph->dest_net = (sword)them_net;
    ph->product = pMax;
    ph->rev_maj = SQUISH_REV_MAJ;
    ph->rev_min = SQUISH_REV_MIN;
    ph->password[0] = '\0';
    ph->qm_orig_zone = ph->orig_zone = us->zone;
    ph->qm_dest_zone = ph->dest_zone = them_zone;
    ph->aux_net = us->net;

    ph->cw = cREV2P;


    ph->orig_point = us->point;
    ph->dest_point = them_point;
    ph->product_hi = 0;



    sb.zone = them_zone;
    sb.net = them_net;
    sb.node = them_node;
    sb.point = them_point;

    for (np = config.pwd; np; np = np->next)
    {
        if (AddrMatchS(&sb, &np->addr))
        {
            (void)strncpy(ph->password, np->pwd, 8);
            break;
        }
    }
}


    if ((config.area = SkipCreateList(16, 8, CfgareaComp)) == NULL)
        NoMem();
}

void Cleanup(void)
{
    struct _cfgarea *ar;
    struct _sblist *sb, *nextsb;
    struct _arcinfo *ap, *nextap;
    struct _remap *rem, *nextrem;
    struct _nodepwd *pwd, *nextpwd;
    struct _fwdlist *fwd, *nextfwd;
    struct _statlist *sl, *nextsl;
    struct _groute *gr, *nextgr;
    struct _tosspath *tp, *nexttp;
    struct _outb *pob, *nextpob;


        ft.struct_len = sizeof(ft);


        if (feat->pszDLLName)
            free(feat->pszDLLName);

        if (feat->pszConfigName)
            free(feat->pszConfigName);


        for (sb = ar->scan; sb; nextsb = sb->next, free(sb), sb = nextsb)
            ;

        for (sb = ar->update_ok; sb; nextsb = sb->next, free(sb), sb = nextsb)
            ;

        for (sl = ar->statlist; sl; nextsl = sl->next, free(sl), sl = nextsl)
            ;

        free(ar->path);
        free(ar->name);
        free(ar);
    }

    (void)SkipDestroyList(config.area);

    for (ap = config.arc; ap; nextap = ap->next, (free)(ap), ap = nextap)
    {
        if (ap->arcname)
            (free)(ap->arcname);

        if (ap->extension)
            (free)(ap->extension);

        if (ap->add)
            (free)(ap->add);

        if (ap->extract)
            (free)(ap->extract);

        if (ap->view)
            (free)(ap->view);

        if (ap->id)
            (free)(ap->id);

        return TRUE;
    else
        return FALSE;
}

int MatchSS(struct _sblist *m1, struct _sblist *m2, int ign_zone)
{
    if ((m1->zone == m2->zone || m2->zone == 0 || m1->zone == 0 || m1->zone == ZONE_ALL ||
         m2->zone == ZONE_ALL || (config.flag & FLAG_CHECKZ) == 0 || ign_zone) &&
        (m2->net == m1->net || m1->net == NET_ALL || m2->net == NET_ALL) &&
        (m2->node == m1->node || m1->node == NODE_ALL || m2->node == NODE_ALL) &&
        (m2->point == m1->point || m1->point == POINT_ALL ||

    NW(bad_scan_all);


        for (ar = SkipFirst(config.area); ar; ar = SkipNext(config.area))
        {

        if ((etfile = shfopen(etname, "r", O_RDONLY | O_NOINHERIT)) == NULL)
        {

                (void)printf("Can't find `%s'; no areas scanned.\n", etname);
                S_LogMsg("#Can't read echotoss log `%s'; scan aborted", etname);
            }
        }
    case 'C':
        return MSGCRASH;
    case 'H':
        return MSGHOLD;
    case 'D':
        return MSGCRASH | MSGHOLD;
    }
}

int NetmailArea(struct _cfgarea *ar)
{
    struct _cfgarea *net;

    for (net = config.netmail; net; net = net->next_type)
        if (net == ar)
            return TRUE;

    return FALSE;
}

int BadmsgsArea(struct _cfgarea *ar)
{
    struct _cfgarea *net;

    for (net = config.badmsgs; net; net = net->next_type)
        if (net == ar)
            return TRUE;

    return FALSE;
}

int DupesArea(struct _cfgarea *ar)
{
    struct _cfgarea *net;

    for (net = config.dupes; net; net = net->next_type)
        if (net == ar)
            return TRUE;

    return FALSE;
}

NETADDR *SblistToNetaddr(struct _sblist *sb, NETADDR *n)
{
    n->zone = sb->zone;
    n->net = sb->net;
    n->node = sb->node;
    n->point = sb->point;
    return n;
}

struct _sblist *NetaddrToSblist(NETADDR *n, struct _sblist *sb)
{
    sb->zone = n->zone;
    sb->net = n->net;
    sb->node = n->node;
    sb->point = n->point;
    return sb;
}

#ifdef SWAP
static char *near MakeFullPath(char *cmd)
{
    char this[PATHLEN];
    char progname[PATHLEN];
    char *path = getenv("PATH");
    char *try;
    char *newpath;
    char *s;
    word last = TRUE;


    newpath = path ? sstrdup(path) : sstrdup(".");

                    free(try);
                    *this = '\0';
                    continue;
                }
            }
        }


        if ((nul_file = sopen(NULL_DEVICE, O_CREAT | O_TRUNC | O_WRONLY | O_BINARY, SH_COMPAT,
                              S_IREAD | S_IWRITE)) != -1)
        {
            (void)dup2(nul_file, fileno(stdout));
            (void)close(nul_file);
        }
    }

#ifdef __WATCOMC__
    _heapshrink();
#endif

    uninstall_24();

#ifdef OS_2
    {

        USHORT i;

        for (i = 5; i < 50; i++)
            (void)DosSetFHandState(i, OPEN_FLAGS_NOINHERIT);
    }
#endif

#ifdef SWAP
    if (config.flag2 & FLAG2_SWAP)
    {
        char *s;
        char exec_return;
        char *_swappath;
        char *path = MakeFullPath(cmd);

        if (config.swappath && *config.swappath)
            _swappath = config.swappath;
        else
            _swappath = "__SQUISH.~~~";

        s = strtok(path, " ");

        if (!s)
            s = path;

        errno = swap(s, s + strlen(s) + 1, &exec_return, _swappath);

        if (errno)
        {
            case 3:
                errno = EBADF;
                break;
            }

            arcret = -1;
        }
        else
            arcret = exec_return;

        free(path);

    }
    else
#endif
        arcret = spawnvp(P_WAIT, args[0], (char **)args);

    install_24();

    if (archiver && (config.flag & FLAG_QUIETARC))
    {
        (void)dup2(save_stdout, fileno(stdout));
        (void)close(save_stdout);
    }

    if ((config.flag2 & FLAG2_SWAP) == 0)
        for (x = 0; x < nargs; x++)
            free(args[x]);

    free(cmd);
    return arcret;
}


    if (da[19] == (byte)0xffu || da[18] == '\0' || da[18] == ' ')
        (void)memmove(da + 10, da + 9, 10);

            *da = '0';

        if (da[0] < '0' || da[0] > '3' || da[1] < '0' || da[1] > '9' || da[2] != ' ')
            return TRUE;

        for (mo = 0; mo < 12; mo++)
            if (strncmp(da + 3, months_ab[mo], 3) == 0)
                break;

        if (mo == 12)
            return TRUE;

        if (da[6] != ' ')
            return TRUE;

        if (da[7] < '0' || da[7] > '9' || da[8] < '0' || da[8] > '9')
            return TRUE;

        if (da[9] != ' ' || da[10] != ' ')
            return TRUE;


void MashMsgid(char *begin, dword *msgid_hash, dword *msgid_serial)
{
    char hash_buf[PATHLEN];
    size_t maxsize;
    char *end;


    end = begin;


        while (*end && *end != ' ')
            end++;
    }

    maxsize = min(PATHLEN - 1, (size_t)(end - begin));

    strncpy(hash_buf, begin, maxsize);
    hash_buf[(size_t)maxsize] = 0;
    *msgid_hash = SquishHash(hash_buf);


    if (sscanf(end, "%08" INT32_FORMAT "x", msgid_serial) != 1)
    {
        *msgid_serial = *msgid_hash = 0L;
        return;
    }
}
