// SPDX-License-Identifier: GPL-2.0-or-later

struct DISKNODEHDR
{
    unsigned short fFree;  // Is this node free or in use?
    NNUM nnNextFree;       // The next free node in the free list
    unsigned short usKeys; // Number of keys in this node
};

// Header for a B-tree file, as it is stored on disk.

struct DISKFILEHDR
{
    NNUM nnHead;              // Head of the B-tree
    NNUM nnFree;              // Next free block in file
    unsigned short usOrder;   // Order of the B-tree
    unsigned short usKeySize; // Size of each key element
    unsigned long cKeys;      // Total number of keys in file
};