// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: max_chat.c,v 1.1.1.1 2002/10/01 17:51:29 sdudley Exp $";
#pragma on(unreferenced)


#define MAX_LANG_max_chat

#include "max_chat.h"
#include "alc.h"
#include "mm.h"
#include "prog.h"
#include <fcntl.h>
#include <io.h>
#include <mem.h>
#include <share.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

#ifdef OS_2
#include "modem.h"
#include "pos2.h"
#endif

static struct _cstat cstat;

word cur_ch = -1;
word num_task = 0;

word *tasks = NULL;

long scan_time = NORM_SCAN_TIME;

#ifdef MCP

#define INCL_DOS
#include "pos2.h"

#include "mcp.h"

HPIPE hpMCP;


        time_ping = timerset(2 * 60 * 100);
    }
}

void SendVideoDump(void)
{
    VIO_DUMP_HDR *pdh;
    int i, size;
    byte *buf, *bufp;

    if ((buf = bufp = malloc(size = win->s_width * win->s_height * 2 + sizeof *pdh)) == NULL)
    {
        logit(mem_none);
        return;
    }

    pdh = (VIO_DUMP_HDR *)bufp;

    pdh->bHeight = (BYTE)win->s_height;
    pdh->bWidth = (BYTE)win->s_width;
    pdh->bCurRow = (BYTE)win->row;
    pdh->bCurCol = (BYTE)win->col;
    pdh->bCurAttr = (BYTE)curattr;

    bufp += sizeof *pdh;

    for (i = 0; i < win->s_height; i++)
    {
        memmove(bufp, win->rowtable[i], win->s_width * 2);
        bufp += win->s_width * 2;
    }


void ChatSetStatus(int avail, char *status)
{
    if (!hpMCP)
        return;

    cstat.avail = avail;
    strcpy(cstat.username, usrname);
    strcpy(cstat.status, status);

    McpSendMsg(hpMCP, PMSG_SET_STATUS, (BYTE *)&cstat, sizeof cstat);
}


int ChatSendMsg(byte dest_tid, int type, int len, char *msg)
{
    struct _cdat *pcd;
    BYTE *buf;
    OS2UINT rc, cbWritten;

    if (!hpMCP)
        return -1;

    if ((buf = malloc(len + sizeof(USHORT) + sizeof *pcd)) == NULL)
    {
        logit(mem_none);
        return -1;
    }

    *(USHORT *)buf = PMSG_MAX_SEND_MSG;

    pcd = (struct _cdat *)(buf + sizeof(USHORT));
    pcd->tid = task_num;
    pcd->dest_tid = dest_tid;
    pcd->type = type;
    pcd->len = len;

    memmove(buf + sizeof(USHORT) + sizeof *pcd, msg, len);

    if ((rc = DosWrite(hpMCP, buf, len + sizeof(USHORT) + sizeof *pcd, &cbWritten)) != 0)
    {
        logit("!SYS%04d: DosWrite MCP 2", rc);
        return -1;
    }

    free(buf);

    return 0;
}


    if (hpMCP)
        return -1;


    if (!*szMcpPipe)
        strcpy(szMcpPipe, "\\pipe\\maximus\\mcp");

    strcpy(szPipe, szMcpPipe);
    strcat(szPipe, "\\maximus");

    fFirst = TRUE;


                psz[strlen(psz)] = 0;


                rc = DosExecPgm(szFailObj, PATHLEN, EXEC_BACKGROUND, szMcpString, NULL, &rcd,
                                szMcpString);


                if (rc)
                {
                    logit(log_mcp_err_2, rc);
                    break;
                }
            }
        }
    } while (!fOpened && !timeup(lTryTime));

    if (fOpened)
        McpSendMsg(hpMCP, PMSG_HELLO, &tid, 1);
    else
    {
        hpMCP = 0;
        logit(log_no_mcp, szMcpPipe);
    }

    return 0;
}


int usStrokes;
byte cbStrokeBuf[MAX_BUF_STROKE];

static void near ChatDispatchMsg(byte *pbMsg, USHORT cbMsg)
{
    USHORT usType = *(USHORT *)pbMsg;
    USHORT usAdd;

    if (!hpMCP)
        return;

    switch (usType)
    {
    case RPMSG_HAPPY_DAGGER:
        logit("!MCP-initiated shutdown");
        ChatSetStatus(FALSE, "Terminating...");
        quit(ERROR_KEXIT);
        break;

    case RPMSG_MONITOR:
        mcp_video = !!pbMsg[2];


        if (mcp_video)
            SendVideoDump();
        break;


    case RPMSG_KEY:
        cbMsg -= 2;
        usAdd = min(MAX_BUF_STROKE - usStrokes, cbMsg);

        memmove(cbStrokeBuf + usStrokes, pbMsg + sizeof(USHORT), usAdd);

        usStrokes += usAdd;
        break;
    }
}


    if (!usGot)
        return 1;

    if (ad.cbmessage > maxlen)
    {
        logit("!MCP message truncated (%d)", ad.cbmessage);
        ad.cbmessage = maxlen;
    }

    if ((rc = DosRead(hpMCP, msg, ad.cbmessage, &usGot)) != 0)
        logit("!SYS%04d: MCP DosRead", rc);
    else if (usGot != ad.cbmessage)
        logit("!Could not read all MCP data from pipe %d/%d", usGot, ad.cbmessage);
    else
    {
        struct _cdat *pcd;

        if (*(USHORT *)msg == RPMSG_GOT_MSG)
        {

            memmove(msg, msg + sizeof(USHORT) + sizeof *pcd, min(ad.cbmessage, *len));

            return 0;
        }
        else
            ChatDispatchMsg(msg, ad.cbmessage);
    }

    return 1;
}

#else
void ChatSetStatus(int avail, char *status)
{
    char temp[PATHLEN];

    int flag, fd;

    if (!*PRM(ipc_path))
        return;

    sprintf(temp, ipcxx_bbs, PRM(ipc_path), task_num);

    if (fexist(temp))
    {
        if ((fd = ChatOpenIPC(task_num)) == -1)
            return;

        flag = TRUE;
    }
    else
    {
        if ((fd = sopen(temp, O_WRONLY | O_CREAT | O_TRUNC | O_BINARY | O_NOINHERIT, SH_DENYNONE,
                        S_IREAD | S_IWRITE)) == -1)
            return;

        flag = FALSE;
    }

    if (read(fd, (char *)&cstat, sizeof(struct _cstat)) < sizeof(struct _cstat))
        memset(&cstat, '\0', sizeof(struct _cstat));

    cstat.avail = avail;
    strcpy(cstat.username, usrname);
    strcpy(cstat.status, status);

    if (cstat.msgs_waiting == 0)
        cstat.next_msgofs = (long)sizeof(struct _cstat);

    lseek(fd, 0L, SEEK_SET);
    write(fd, (char *)&cstat, sizeof(struct _cstat));

    if (flag)
        ChatCloseIPC(fd);
    else
        close(fd);
}

int ChatSendMsg(byte tid, int type, int len, char *msg)
{
    struct _cdat cdat;
    struct _cstat cs;

    int fd;

    if ((fd = ChatOpenIPC(tid)) == -1)
        return -1;

    read(fd, (char *)&cs, sizeof(struct _cstat));

    cs.msgs_waiting++;

    cdat.tid = task_num;
    cdat.type = type;
    cdat.len = len;

    else
    {

        if (cs->msgs_waiting > 5000)
            cs->msgs_waiting = 0;

        {
#ifdef DEBUG
            Printf("IPC:max ");
#endif

            close(fd);
            fd = -1;
        }
    }

    if (fd != -1)
        lseek(fd, 0L, SEEK_SET);

    free(fname);

    return fd;
}

void ChatCloseIPC(int fd)
{
    if (!*PRM(ipc_path))
        return;

    if (!(prm.flags2 & FLAG2_noshare))
        unlock(fd, 0L, 1L);

    close(fd);
}
#endif


void ChatSaveStatus(struct _css *css)
{
#ifndef MCP
    if (!*PRM(ipc_path))
        return;
#endif

    css->avail = cstat.avail;
    strcpy(css->status, cstat.status);
}

void ChatRestoreStatus(struct _css *css)
{
#ifndef MCP
    if (!*PRM(ipc_path))
        return;
#endif

    ChatSetStatus(css->avail, css->status);
}

void Check_For_Message(char *s1, char *s2)
{
    int redo, type, len;
    time_t now;
    byte tid;

    char *msg;
    static long last_check = 0L;

#ifdef MCP
    static long last_received = 0x7fffffffL;
#endif

    now = time(NULL);

    if (
#ifdef MCP
        hpMCP &&
#else
        *PRM(ipc_path) &&
#endif
        fLoggedOn && task_num &&
        (now >= last_check + scan_time
#ifdef MCP // If we received a msg within last 20 seconds, poll continuously
         || now <= last_received + 20
#endif
         ))
    {
        last_check = time(NULL);

        redo = FALSE;

        if ((msg = malloc(PATHLEN)) != NULL)
        {
            while (ChatGetMsg(&tid, &type, &len, msg, PATHLEN) == 0)
            {
#ifdef MCP
                last_received = now;
#endif
                ChatHandleMessage(tid, type, len, msg, &redo);
            }

            free(msg);
        }

        if (redo)
        {
            if (s1 && s2)
                Printf(ss, s1, s2);

            vbuf_flush();
        }
    }
}
