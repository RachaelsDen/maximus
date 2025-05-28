// SPDX-License-Identifier: GPL-2.0-or-later

#pragma off(unreferenced)
static char rcs_id[]="$Id: bbuf.cc,v 1.2 2003/06/11 19:41:07 wesgarland Exp $";
#pragma on(unreferenced)

#include <stdio.h>
#include <limits.h>
#include <string.h>
#include "bbuf.h"


// Constructor for a block buffer

CPPEXPORT BLOCKBUF::BLOCKBUF()
{
  fOpen=FALSE;
  uiNumBlocks=0;
  uiLRUCtr=0;
}


// Standard block buffer destructor.  Just deinitialize us, if necessary.

CPPEXPORT BLOCKBUF::~BLOCKBUF()
{
  deinit();
}



// Initialize a block buffer with a specified buffer size

int CPPEXPORT BLOCKBUF::init(unsigned uiBlkSize)
{
  if (fOpen)
    return FALSE;

  // Initialize our object elements

  fOpen=TRUE;
  this->uiBlkSize=uiBlkSize;
  bbList=0;
  bbDelta=0;
  uiNumBlocks=0;
  uiLRUCtr=0;

  return TRUE;
}


// Deinitialize the block buffer by freeing the list contents

int CPPEXPORT BLOCKBUF::deinit(void)
{
  if (!fOpen)
    return FALSE;

  // Free the linked list

  for (struct _bblist *bb=bbList, *bbnext;
       bb;
       bbnext=bb->next, delete bb, bb=bbnext)
  {
    if (bb->pvBlock)
      delete [] bb->pvBlock;
  }

  fOpen=FALSE;

  return TRUE;
}


// Get a node from the buffer, if it exists

void * CPPEXPORT BLOCKBUF::get(NNUM nn)
{
  for (struct _bblist *bb=bbList, *bbLast=0; bb; bbLast=bb, bb=bb->next)
    if (bb->nn==nn)
    {
      // If we're not already the first node in the list, move this
      // block to the head.

      if (bbLast)
      {
        bbLast->next=bb->next;
        bb->next=bbList;
        bbList=bb;
      }

      bb->uiHits=uiLRUCtr++;
      return bb->pvBlock;
    }

  // Couldn't find it, so return null.

  return 0;
}


// Put a node into the buffer, replacing any node that may already exist

int CPPEXPORT BLOCKBUF::put(NNUM nn, void *pvBlock, unsigned fDelta)
{
  bbDelta=0;

  // Stop when we find a match

  struct _bblist *bb;

  for (bb=bbList; bb; bb=bb->next)
    if (bb->nn==nn)
      break;

  // If we couldn't find a match, add a new node

  if (!bb)
  {
    // Allocate a new block

    if ((bb=new _bblist)==0)
      return FALSE;

    // Allocate a buffer for this block

    if ((bb->pvBlock=(void *)new char[uiBlkSize])==0)
    {
      delete bb;
      return FALSE;
    }

    // Append to the beginning of the list

    bb->next=bbList;
    bbList=bb;

    bb->fDelta=FALSE;

    uiNumBlocks++;
  }

  // Copy data into the block

  bb->nn=nn;
  bb->uiHits=uiLRUCtr++;

  if (fDelta)
    bb->fDelta=TRUE;

  memmove(bb->pvBlock, pvBlock, uiBlkSize);

  return TRUE;
}


// Find the first node with the delta bit set, starting from the
// beginning.

void * CPPEXPORT BLOCKBUF::delta_first(NNUM *pnn)
{
  // Start looking for delta bits from the beginning of the list

  for (bbDelta=bbList; bbDelta; bbDelta=bbDelta->next)
    if (bbDelta->fDelta)
    {
      *pnn=bbDelta->nn;
      return bbDelta->pvBlock;
    }

  return 0;
}

// Find the next node with the delta bit set

void * CPPEXPORT BLOCKBUF::delta_next(NNUM *pnn)
{
  if (!bbDelta || !bbDelta->next)
    return 0;

  // Search the linked list to find the next delta bit after the
  // current one.

  for (bbDelta=bbDelta->next; bbDelta; bbDelta=bbDelta->next)
    if (bbDelta->fDelta)
    {
      *pnn=bbDelta->nn;
      return bbDelta->pvBlock;
    }

  return 0;
}


// Get the data and block number of the most recently-used block,
// removing it from the buffer.

int CPPEXPORT BLOCKBUF::get_lru(NNUM *pnn, void *pvBlock, unsigned *pfDelta)
{
  unsigned uiLowHits=UINT_MAX;
  struct _bblist *bbLow=0;
  struct _bblist *bbLast=0;
  struct _bblist *bbLastLow=0;

  for (struct _bblist *bb=bbList; bb; bbLast=bb, bb=bb->next)
    if (bb->uiHits < uiLowHits)
    {
      uiLowHits=bb->uiHits;
      bbLow=bb;
      bbLastLow=bbLast;
    }

  // If we couldn't find a block, return null

  if (!bbLow)
    return FALSE;

  // Remove this node from the linked list

  if (bbList==bbLow)
    bbList=bbLow->next;
  else bbLastLow->next=bbLow->next;

  memmove(pvBlock, bbLow->pvBlock, uiBlkSize);
  *pfDelta=bbLow->fDelta;
  *pnn=bbLow->nn;

  // Now delete the memory associated with this block

  delete [] bbLow->pvBlock;
  delete bbLow;

  // Decrement the block count for this list

  uiNumBlocks--;

  return TRUE;
}

