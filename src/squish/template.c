// SPDX-License-Identifier: GPL-2.0-or-later


#define INCL_DOS
#include "msgapi.h"
#include "sqfeat.h"
#include <os2.h>
#include <string.h>

static char szAppName[] = "Template";


word FEATENTRY _export FeatureInit(struct _feat_init far *pfi)
{

    strcpy(pfi->szConfigName, szAppName);
    return 0;
}


word FEATENTRY _export FeatureConfig(struct _feat_config far *pfc)
{
    char *p;

    printf("Config: got args: \"");

    for (p = pfc->ppszArgs[1]; p && *p; p++)
        printf("%s ", p);

    printf("\"\n");

    return 0;
}


word FEATENTRY _export FeatureNetMsg(struct _feat_netmsg far *pfn)
{
    printf("Packed message to \"%s\"\n", pfn->pMsg->to);
    return 0;
}

word FEATENTRY _export FeatureTossMsg(struct _feat_toss far *pft)
{
    printf("Tossed message to \"%s\"\n", pft->pMsg->to);
    return 0;
}

word FEATENTRY _export FeatureScanMsg(struct _feat_scan far *pfs)
{
    printf("Scanned message to \"%s\"\n", pfs->pMsg->to);
    return 0;
}

word FEATENTRY _export FeatureTerm(struct _feat_term far *pft)
{
    printf("Feature termination.\n");
    (void)pft;
    return 0;
}

#ifdef __FLAT__
void FEATENTRY _export Feature32Bit(void)
#else
void FEATENTRY _export Feature16Bit(void)
#endif
{
}
