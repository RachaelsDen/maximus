// SPDX-License-Identifier: GPL-2.0-or-later


typedef int32 FOFS;


#define SQUIQSH_IDX_EXPAND 64




#define Sqd ((SQDATA *)(ha->apidata))
#define HSqd ((SQDATA *)(((struct _msgh OS2FAR *)hmsg)->ha->apidata))


struct _sqhdr
{
#define SQHDRID 0xafae4453L


} __attribute__((packed, aligned(2)));

} __attribute__((packed, aligned(2)));



} SQIDXSEG;



typedef struct _sqdata
{






struct _msgh
{




    FOFS foRead;


    SQHDR sqhRead;


    FOFS foWrite;


    SQHDR sqhWrite;

};


unsigned _SquishReadMode(HMSG hmsg);
unsigned _SquishWriteMode(HMSG hmsg);
unsigned _SquishCopyBaseToData(HAREA ha, SQBASE *psqb);
unsigned _SquishWriteBaseHeader(HAREA ha, SQBASE *psqb);
unsigned _SquishReadBaseHeader(HAREA ha, SQBASE *psqb);
unsigned _SquishExclusiveBegin(HAREA ha);
unsigned _SquishExclusiveEnd(HAREA ha);
unsigned _SquishCopyDataToBase(HAREA ha, SQBASE *psqb);
unsigned _SquishReadHdr(HAREA ha, FOFS fo, SQHDR *psqh);
unsigned _SquishWriteHdr(HAREA ha, FOFS fo, SQHDR *psqh);
FOFS _SquishGetFrameOfs(HAREA ha, dword dwMsg);

HIDX _SquishOpenIndex(HAREA ha);
int _SquishBeginBuffer(HIDX hix);
int SidxGet(HIDX hix, dword dwMsg, SQIDX *psqi);
int SidxPut(HIDX hix, dword dwMsg, SQIDX *psqi);
unsigned _SquishRemoveIndexEntry(HIDX hix, dword dwMsg, SQIDX *psqiOut, SQHDR *psqh,
                                 int fFixPointers);
unsigned _SquishCloseIndex(HIDX hix);
int _SquishEndBuffer(HIDX hix);
dword _SquishIndexSize(HIDX hix);
unsigned _SquishFixMemoryPointers(HAREA ha, dword dwMsg, SQHDR *psqh);

