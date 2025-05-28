// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: sem_flow.c,v 1.1.1.1 2002/10/01 17:54:02 sdudley Exp $";
#pragma on(unreferenced)

#include "mex.h"
#include "prog.h"

PATCH *GenJumpOut();


PATCH IfTest(DATAOBJ *obj)
{
    PATCH p;
    char tn[MAX_TN_LEN];

    p.quad = this_quad;
    p.next = NULL;

    if (obj)
    {
        Generate(QOP_JZ, obj, NULL, NULL);
        MaybeFreeTemporary(obj, TRUE);

        if (!IsIntegral(obj->type) && obj)
            error(MEXERR_INVALIDTYPEFORSTMT, TypeName(obj->type, tn), "if");
    }

    return p;
}

void IfEnd(PATCH *if_test, ELSETYPE *elses)
{
    BackPatch(if_test, elses->else_label);
    BackPatch(elses->patchout, this_quad);
}

void ElseHandler(ELSETYPE *e)
{
    PATCH *ret;

    ret = e->patchout = smalloc(sizeof(PATCH));
    ret->quad = this_quad;
    ret->next = NULL;
    Generate(QOP_JMP, NULL, NULL, NULL);
    e->else_label = this_quad;
}


void GenDoWhileOut(WHILETYPE *w, DATAOBJ *obj)
{
    char tn[MAX_TN_LEN];

    w->jump.quad = this_quad;
    w->jump.next = NULL;

    if (obj && !IsIntegral(obj->type))
        error(MEXERR_INVALIDTYPEFORSTMT, TypeName(obj->type, tn), "do while");

    Generate(QOP_JNZ, obj, NULL, NULL);
    BackPatch(&w->jump, w->top_quad);

    MaybeFreeTemporary(obj, TRUE);
}

void WhileTest(WHILETYPE *w, DATAOBJ *obj)
{
    char tn[MAX_TN_LEN];

    w->jump.quad = this_quad;
    w->jump.next = NULL;

    if (obj && !IsIntegral(obj->type))
        error(MEXERR_INVALIDTYPEFORSTMT, TypeName(obj->type, tn), "while");

    Generate(QOP_JZ, obj, NULL, NULL);
    MaybeFreeTemporary(obj, TRUE);
}


void GenForTest(FORTYPE *pfr, DATAOBJ *pdo)
{
    char tn[MAX_TN_LEN];

    if (pdo && !IsIntegral(pdo->type))
        error(MEXERR_INVALIDTYPEFORSTMT, TypeName(pdo->type, tn), "for");


    if (pdo)
    {

    pfr->paJmpBody.quad = this_quad;
    pfr->paJmpBody.next = NULL;

    Generate(QOP_JMP, NULL, NULL, NULL);

    MaybeFreeTemporary(pdo, TRUE);
}


void GenForJmpTest(FORTYPE *pfr)
{
    pfr->paJmpTest.quad = this_quad;
    pfr->paJmpTest.next = NULL;

    Generate(QOP_JMP, NULL, NULL, NULL);
}


void GenForJmpPostAndCleanup(FORTYPE *pfr)
{

    BackPatch(&pfr->paJzDone, this_quad);
    BackPatch(&pfr->paJmpBody, pfr->vmBody);
    BackPatch(&pfr->paJmpTest, pfr->vmTest);
    BackPatch(&pfr->paJmpPost, pfr->vmPost);
}


void GenWhileOut(WHILETYPE *w)
{
    PATCH here;


    Generate(QOP_JMP, NULL, NULL, NULL);


    BackPatch(&here, w->top_quad);
}
