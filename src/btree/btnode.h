// SPDX-License-Identifier: GPL-2.0-or-later

#ifndef __BTNODE_H_DEFINED
#define __BTNODE_H_DEFINED

class BTREE; // Forward decl for B-tree class

// In-memory node record

class BTNODE
{
    BTREE *pbt;       // Related B-tree
    char *pcDiskNode; // On-disk version of node

  public:
    NNUM nn;         // Number of this node
    unsigned uiKeys; // Number of keys in this node

    unsigned fFree;  // Is this node free or in use?
    NNUM nnNextFree; // The next free node in the free list

    NNUM *child; // Children of this node
    void **key;  // Keys for this node

    BTNODE(BTREE *pbt, NNUM n = 0L);
    ~BTNODE();
    int get();
    int put();
};

#endif // __BTNODE_H_DEFINED
