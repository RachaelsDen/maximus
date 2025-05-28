// SPDX-License-Identifier: GPL-2.0-or-later


void Convert_MaxPriv(void);
void Convert_Opus110(void);
void ConvertTo_Opus110(void);
void Convert_Quick(void);
void Convert_Opus103(void);
void Convert_Max(int c);
void Convert_Max102(void);
void Check_If_Exist(void);
long CRC(char *s);
char *BASIC_String(char *s, int len);
void Blank_User(struct _usr *usr);
void Convert_RBBS(char *name);
void Reverse_Max200(void);

byte MaxToOpusPriv(int mpriv);
int OpusToMaxPriv(byte opriv);

#define TOTPRIVS 12













    word lastmsg[MAXLREAD];

};

struct _sys110
{




{
    char name[36], city[26], pwd[16], data_phone[13], home_phone[13], last_time[6], last_date[9];

    byte attrib;

    char flags[4];

    int credit, pending, times_posted, highmsgread, seclvl, times, ups, downs, upk, downk, todayk,
        elapsed, len;

    int combinedptr;

    byte age;

    byte rsvd1[5];
};



{



};

