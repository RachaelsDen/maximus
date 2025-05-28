// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: events.c,v 1.2 2003/06/04 23:14:57 wesgarland Exp $";
#pragma on(unreferenced)

#include "events.h"
#include "mm.h"
#include "prog.h"
#include <ctype.h>
#include <fcntl.h>
#include <io.h>
#include <share.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

static struct _event *elist;
static unsigned num_event;

#ifndef UNIX
static char event_name[] = "%sevents%02x%s";
#else
static char event_name[] = "%setc/events%02x%s";
#endif

static union stamp_combo done_date;


void EventListFree(void)
{
    struct _event *e, *enext;

    num_event = 0;

    for (e = elist; e; enext = e->next, free(e), e = enext)
        ;

    elist = NULL;
}


    for (l = elist; l && l->next; l = l->next)
        ;


static void near EventMemToDisk(struct _event *pe, struct _diskevent *pde)
{
    memset(pde, '\0', sizeof(struct _diskevent));

    pde->day = pe->day;
    pde->fill1 = pe->fill1;
    pde->flags = pe->flags;
    pde->erl = pe->erl;
    pde->data1 = pe->data1;
    pde->data2 = pe->data2;
    pde->data3 = pe->data3;
    pde->start = pe->start;
    pde->end = pe->end;
    pde->eventnum = pe->eventnum;

    strcpy(pde->tune, pe->tune);
}


    if (!elist)
        return;

    sprintf(edatn, event_name, PRM(sys_path), e_num, dotdat);

    if ((fd = sopen(edatn, O_CREAT | O_TRUNC | O_WRONLY | O_BINARY, SH_DENYNONE,
                    S_IREAD | S_IWRITE)) == -1)
    {
        cant_open(edatn);
        return;
    }

    if (dateit)
        Get_Dos_Date(&done_date);

    write(fd, (char *)&done_date, sizeof(union stamp_combo));


    sprintf(ebbsn, event_name, PRM(sys_path), e_num, dotbbs);

    if (FileDate(ebbsn, &scBbs) == 0 && FileDate(edatn, &scDat) == 0)
    {
        if (!GEdate(&scDat, &scBbs))
        {
            SCOMBO now;

            Get_Dos_Date(&now);

            SetFileDate(ebbsn, &now);
            Delay(200);
            SetFileDate(edatn, &now);
        }
    }
}

            break;
        }

    Write_Events(event_num, FALSE);
}


static void near Parse_Flag(struct _diskevent *e, char *word)
{
    char flag[PATHLEN];
    char value[PATHLEN];

    getword(word, flag, "=", 1);
    getword(word, value, "=", 2);

    if (eqstri(flag, "exit"))
    {
        e->flags |= EFLAG_ERLVL;
        e->erl = atoi(value);
    }
    else if (eqstri(flag, "bells"))
    {
        e->flags |= EFLAG_YELL;
        e->data1 = atoi(value);

        if (!e->data2)
            e->data2 = 3;

        if (!*e->tune)
            strcpy(e->tune, "Yell");
    }
    else if (eqstr(flag, "maxyell"))
        e->data2 = atoi(value);
    else if (eqstr(flag, "tune"))
        strnncpy(e->tune, value, sizeof(e->tune) - 1);
    else
        Event_Syntax_Err(flag);
}


static void near Parse_Time(struct _etime *t, char *word)
{
    char hour[20];
    char min[20];

    getword(word, hour, ":", 1);
    getword(word, min, ":", 2);

    t->hour = atoi(hour);
    t->min = atoi(min);

    if (t->hour > 23 || t->min > 59)
        logit(log_bad_evt_time, word);
}


    if ((p = strchr(line, ';')) != NULL)
        *p = '\0';

    word = strtok(line, ctl_delim);

    while (word && *word)
    {
        switch (wn++)
        {
        case 1:
            if (!eqstri(word, "event"))
            {
                Event_Syntax_Err(word);
                return FALSE;
            }
            break;

        case 2:
            Parse_Day(&de, word);
            break;

        case 3:
            Parse_Time(&de.start, word);
            break;

        default:
            if (isdigit(*word))
                Parse_Time(&de.end, word);
            else
                Parse_Flag(&de, word);
        }

        word = strtok(NULL, ctl_delim);
    }


static int near Parse_Event_File(char *ebbsname)
{
    char temp[PATHLEN];
    FILE *ef;

    EventListFree();

    if ((ef = fopen(ebbsname, fopen_read)) == NULL)
        return FALSE;

    while (fgets(temp, PATHLEN, ef) != NULL)
        Process_Event_Line(temp);

    fclose(ef);
    return TRUE;
}


    if ((e->day & (1 << ts->tm_wday)) == 0)
        return FALSE;

    if (!for_now)
        return TRUE;

    Event_To_Dos_Date(&e->start, &then_st, &now);
    Event_To_Dos_Date(&e->end, &then_end, &now);


int GetEvent(word eflag, int not_eflag, struct _event *out, int now)
{
    struct _event *e;

    for (e = elist; e; e = e->next)
        if ((e->flags & eflag) == eflag && (e->flags & not_eflag) == 0 && InEvent(e, now))
        {
            if (out)
                *out = *e;

            return TRUE;
        }

    return FALSE;
}


    if (now.dos_st.date != done_date.dos_st.date)
    {
        for (pe = elist; pe; pe = pe->next)
            if (pe->flags & EFLAG_DONE)
                pe->flags &= ~EFLAG_DONE;

        Write_Events(e_num, TRUE);
    }
}

static int near TryReadEither(int e_num, int write_anyway)
{
    union stamp_combo edat_st, ebbs_st;

    char edatn[PATHLEN];
    char ebbsn[PATHLEN];

    sprintf(edatn, event_name, PRM(sys_path), e_num, dotdat);
    sprintf(ebbsn, event_name, PRM(sys_path), e_num, dotbbs);


        if (!Parse_Event_File(ebbsn))
            if (!write_anyway)
                return FALSE;


    return TRUE;
}


void Read_Events(void)
{
    if (!TryReadEither(event_num, FALSE))
    {
        if (TryReadEither(0, FALSE))
            event_num = 0;
        else
            TryReadEither(event_num, TRUE);
    }
}
