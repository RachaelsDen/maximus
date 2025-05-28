// SPDX-License-Identifier: GPL-2.0-or-later

#pragma off(unreferenced)
static char rcs_id[]="$Id: btnode.cc,v 1.1.1.1 2002/10/01 17:49:21 sdudley Exp $";
#pragma on(unreferenced)

#include <string.h>
#include "btree.h"
#include "btreep.h"

//////////////////////////////////////////////////////////////////////////////
// B-tree node object
//////////////////////////////////////////////////////////////////////////////


// Constructor for a B-tree node

BTNODE::BTNODE(BTREE *pbtRelated, NNUM n)
{
  // Store information about our owning B-tree

  pbt=pbtRelated;

  // Allocate enough memory for the on-disk node record

  pcDiskNode=new char[pbt->uiNodeSize];

  if (!pcDiskNode)
    throw NoMem(0);

  memset(pcDiskNode, 0, pbt->uiNodeSize);

  // Initialize the node number and # of keys to zero

  nn=n;
  uiKeys=0;

  fFree=FALSE;
  nnNextFree=0L;

  // Initialize the child and key lists to NULL since nothing has
  // yet been read.

  key=new void *[pbt->uiOrder];

  if (!key)
  {
    delete [] pcDiskNode;
    throw NoMem(0);
  }

  // Assign the array of 'child node numbers' to a pointer that
  // can be easily accessed.

  child=(NNUM *)(pcDiskNode + sizeof(DISKNODEHDR));


  // Now do the same for all the keys, by setting up pointers to
  // point to the beginning of each key.

  char *p=(char *)(child+pbt->uiOrder+1);

  for (int i=0; i < pbt->uiOrder; i++)
  {
    key[i]=(void *)p;             // Copy pointer
    p += pbt->uiKeySize;          // Increment to starting offset of next key
  }
}


BTNODE::~BTNODE()
{
  // Just free the memory that was used by the disk buffer

  delete [] pcDiskNode;
  delete [] key;
}


// Fetch a node from the on-disk B-tree

int BTNODE::get()
{
  DISKNODEHDR *pnh;

  if (!nn)
    return FALSE;

  // Read this block into memory

  if (! pbt->get(nn, pcDiskNode))
    return FALSE;

  // Copy the header information out of the node's header

  pnh=(DISKNODEHDR *)pcDiskNode;

  uiKeys=pnh->usKeys;
  nnNextFree=pnh->nnNextFree;
  fFree=pnh->fFree;

  // Make sure that the caller got a free block if that is what was
  // requested.

  return (fFree==pnh->fFree);
}


// Write an in-memory node back to the disk-based B-tree

int BTNODE::put()
{
  DISKNODEHDR *pnh;

  if (!nn)
    return FALSE;

  // Copy the information from our class instance to the disk header

  pnh=(DISKNODEHDR *)pcDiskNode;

  pnh->usKeys=(unsigned short)uiKeys;
  pnh->fFree=(unsigned short)fFree;
  pnh->nnNextFree=nnNextFree;

  return pbt->put(nn, pcDiskNode);
}


