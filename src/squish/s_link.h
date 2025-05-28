// SPDX-License-Identifier: GPL-2.0-or-later


struct _link;

static void Link_Area(struct _cfgarea *ar, HAREA opensq);
static void near LinkIt(HAREA sq, struct _cfgarea *ar);
static int _stdc msgcomp(const void *i1, const void *i2);
static int _stdc msgidcomp(const void *i1, const void *i2);
static size_t msgidsearch(struct _link **link, long nl, struct _link *find);
static int _stdc umsgidcomp(const void *i1, const void *i2);

struct _link
{
