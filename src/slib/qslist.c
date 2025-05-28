// SPDX-License-Identifier: GPL-2.0-or-later


#include "prog.h"


void *_fast qsortl(void *list, void *(_stdc *getnext)(void *), void(_stdc *setnext)(void *, void *),
                   int(_stdc *compare)(void *, void *))
{
    void *low_list, *high_list, *sorted, *pivot, *temp;

