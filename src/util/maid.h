// SPDX-License-Identifier: GPL-2.0-or-later



#if 0
  MAID: MAximus International Definitions specification:

In USER.DEF / SYSOP.DEF (sysop-editable):

  item="text" \
       "moretext"
  item2="second text item"
         
Above file is fed into MAID compiler.  Output of MAID, ASCII text, one to a
line, into MAIDOUT.H:

      MAID(item,"text""moretext")
      MAID(item2,"second text item")

In MAX.H:  (We can define INTERNAL_STRING, to make all of the strings
            internal.  Once we've got the external compiler working, we
            just #undef the INTERNAL_STRING variable, and we're all
            set to go with the multilingulal version.)  */

#ifdef INTERNAL_STRING

#define MAID(i, t) extrn char *i IS(t);
#define s(i) (i)
    

#include "maidout.h"




#define s(i) (maid_heap + maid_ofs[i])


#define MAID(i, t) (i),

  enum _maid_str
  {
#include "maidout.h"
    
    struct _mcomp
    {
      char *token;
      int val;
    };
    

#define MAID(i, t) {#i, i},
      
    struct _mcomp[]=
    {
#include "maidout.h"
