// SPDX-License-Identifier: GPL-2.0-or-later

#include "bbuf.h"
#include "blkio.h"

// BLKIOBUF:  Buffered block I/O class

class BLKIOBUF : public BLKIO, private BLOCKBUF
{
    NNUM nnHighPut;       // Highest node # put to file
    unsigned uiBlkSize;   // Block size for file
    unsigned uiMaxBlocks; // Max # of blocks to buffer

    int _insert_list(NNUM nn, char *pcDiskNode, unsigned fSetDelta);

  public:
    CPPEXPORT BLKIOBUF(unsigned uiMaxBlocks = 32);
    virtual CPPEXPORT ~BLKIOBUF();

    int CPPEXPORT enable_buffer(unsigned fEnable);
    int CPPEXPORT flush_buffer(void);

    // Functions overriden from BLKIO

    virtual int CPPEXPORT close();
    virtual int CPPEXPORT set_block_size(unsigned int uiBlkSize);

    virtual int CPPEXPORT get(NNUM nn, char *pcDiskNode);
    virtual int CPPEXPORT put(NNUM nn, char *pcDiskNode);
    virtual NNUM CPPEXPORT high_node(void);

    // Functions inherited from BLKIO but not overriden:
    //
    // int open(char *szPath, int fNewFile);
    // int get_header(char *pcDiskNode, unsigned uiSize);
    // int put_header(char *pcDiskNode, unsigned uiSize);
    // int lock(NNUM nn);
    // int unlock(NNUM nn);
};