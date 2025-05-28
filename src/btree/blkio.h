// SPDX-License-Identifier: GPL-2.0-or-later

// Block I/O class for B-tree and database routines

#ifndef __BLKIO_H_DEFINED
#define __BLKIO_H_DEFINED

#include "btype.h" // B-tree type definitions

class BLKIO
{
    int fd;                // File handle used for I/O
    unsigned fOpen;        // Has the file been opened?
    unsigned uiBlkSize;    // Block size for this file
    unsigned fShareLoaded; // Is SHARE.EXE loaded?

    int BLKIO::position(NNUM nn);

  public:
    CPPEXPORT BLKIO();
    virtual CPPEXPORT ~BLKIO();

    int CPPEXPORT open(char *szPath, int fNewFile);
    int CPPEXPORT get_header(char *pcDiskNode, unsigned uiSize);
    int CPPEXPORT put_header(char *pcDiskNode, unsigned uiSize);

    virtual int CPPEXPORT set_block_size(unsigned int uiBlkSize);
    virtual int CPPEXPORT close();

    virtual int CPPEXPORT get(NNUM nn, char *pcDiskNode);
    virtual int CPPEXPORT put(NNUM nn, char *pcDiskNode);
    virtual int CPPEXPORT lock(NNUM nn);
    virtual int CPPEXPORT unlock(NNUM nn);

    virtual NNUM CPPEXPORT high_node(void);
};

#endif // __BLKIO_H_DEFINED