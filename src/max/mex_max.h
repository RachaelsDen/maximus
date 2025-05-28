// SPDX-License-Identifier: GPL-2.0-or-later


#ifndef __MEX_MAX_H_DEFINED
#define __MEX_MAX_H_DEFINED

#define CIT_DAY_TIME 0
#define CIT_CALL_TIME 1
#define CIT_DL_LIMIT 2
#define CIT_RATIO 3
#define CIT_MIN_BAUD 4
#define CIT_MIN_XFER_BAUD 5

struct mex_instancedata
{
    word instant_video;
    word task_num;
    word local;
    word port;
    dword speed;
    word alias_system;
    word ask_name;
    word use_umsgid;
};

struct mex_cstat
{
    word task_num;
    word avail;
    IADDR username;
    IADDR status;
};

struct mex_date
{
};

struct mex_stamp
{
    struct mex_date date;
    struct mex_time time;
};

struct mex_usr
{


















