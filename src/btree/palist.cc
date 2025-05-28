// SPDX-License-Identifier: GPL-2.0-or-later

#pragma off(unreferenced)
static char rcs_id[]="$Id: palist.cc,v 1.1.1.1 2002/10/01 17:49:29 sdudley Exp $";
#pragma on(unreferenced)

#include "palist.h"

//////////////////////////////////////////////////////////////////////////////
// Parent list object
//////////////////////////////////////////////////////////////////////////////

// Constructor for the list of parent nodes

CPPEXPORT PALIST::PALIST()
{
  ppn=new PNODE;

  if (ppn)
  {
    ppn->next=0;
    ppn->nn=0L;
  }

  fSearched=FALSE;
  current_idx=0;
}

// Destructor for the list of parent nodes

CPPEXPORT PALIST::~PALIST()
{
  PNODE *p, *pnext;

  // Free the linked list of nodes

  for (p=ppn; p; pnext=p->next, delete p, p=pnext)
    ;
}

// Add another parent to the list of parents

int CPPEXPORT PALIST::add(NNUM nn, int current_idx)
{
  PNODE *p;

  p=new PNODE;

  if (!p)
    return FALSE;

  p->current_idx=current_idx;
  p->nn=nn;
  p->next=ppn;
  ppn=p;

  return TRUE;
}

// Pop one node off the list and return its node number

NNUM CPPEXPORT PALIST::pop(int *pcurrent_idx)
{
  PNODE *p;
  NNUM rc;

  if (!ppn)
    return 0L;

  p=ppn;
  rc=p->nn;
  *pcurrent_idx=p->current_idx;

  // Unlink the first node

  ppn=ppn->next;

  delete p;

  return rc;
}

// Return a linked list of parents of this node

PNODE * CPPEXPORT PALIST::nodes()
{
  return ppn;
}


