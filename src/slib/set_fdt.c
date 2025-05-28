// SPDX-License-Identifier: GPL-2.0-or-later


#include "prog.h"
#include <dos.h>


int _fast set_fdt(int handle, union stamp_combo *filestamp)
{
    FILESTATUS3 fs3;
    int stat;

    if ((stat = DosQueryFileInfo(handle, FIL_STANDARD, &fs3, sizeof fs3)) == 0)
    {
        *(USHORT *)&fs3.fdateLastWrite = filestamp->dos_st.date;
        *(USHORT *)&fs3.ftimeLastWrite = filestamp->dos_st.time;

        stat = DosSetFileInfo(handle, FIL_STANDARD, (void *)&fs3, sizeof fs3);
    }

    return (stat);
}

    unsigned short write_time;
};


int _fast set_fdt(int handle, union stamp_combo *filestamp)
{
    union REGS regs;

#ifdef __386__
    regs.x.ebx = handle;
    regs.x.edx = (unsigned)filestamp->dos_st.date;
    regs.x.ecx = (unsigned)filestamp->dos_st.time;

    int386(0x21, &regs, &regs);

    return (regs.x.cflag ? regs.x.eax : 0);
#else
    regs.x.bx = handle;
    regs.x.dx = filestamp->dos_st.date;
    regs.x.cx = filestamp->dos_st.time;

    int86(0x21, &regs, &regs);

    return (regs.x.cflag ? regs.x.ax : 0);
#endif
}

#elif defined(NT)

#include "pwin.h"

int _fast set_fdt(int handle, union stamp_combo *psc)
{
    FILETIME ft;

    DosDateTimeToFileTime(psc->dos_st.date, psc->dos_st.time, &ft);
    return !SetFileTime((HANDLE)handle, NULL, NULL, &ft);
}

#elif defined(UNIX)
#include <sys/types.h>
#include <utime.h>

int set_fdt(int fd, union stamp_combo *psc)
{
#if 0
  struct utimbuf touchBuf;
  struct timeval tmdate, *tmdate_p;

  if ((fd < 0) || (!psc))
    return 1;

  memset(&touchBuf, 0, sizeof(touchBuf));
  memset(&tmdate, 0, sizeof(tmdate));

  tmdate_p = DosDate_to_TmDate(psc, &tmdate);
  if (!tmdate_p)
    return 1;

  touchBuf.actime = touchBuf.modtime = tmdate_p->tv_sec;

  
  return 0;
#endif
