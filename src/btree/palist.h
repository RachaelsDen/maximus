// SPDX-License-Identifier: GPL-2.0-or-later

#ifndef __PALIST_H_DEFINED
#define __PALIST_H_DEFINED

#include "btype.h"

// Node used in list of 'our node's parents'

struct PNODE
{
    NNUM nn;         // Node number of parent
    int current_idx; // Current offset within keys
    PNODE *next;
};

// Linked list used for storing chain-of-command (list of all
// our parents, grandparents, etc.) from the head of the
// B-tree down to this node

class PALIST
{
    PNODE *ppn; // Linked list of nodes
  public:
    int fSearched;     // Been used for a search already?
    int current_idx;   // Index in tree.  Only used for browse.
    NNUM current_node; // Node num in tree. "   "    "    "

    CPPEXPORT PALIST();
    CPPEXPORT ~PALIST();
    int CPPEXPORT add(NNUM nn, int current_idx);
    NNUM CPPEXPORT pop(int *pcurrent_idx);
    PNODE *CPPEXPORT nodes();
};

#endif // __PALIST_H_DEFINED