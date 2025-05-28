// SPDX-License-Identifier: GPL-2.0-or-later



void _MexKillStructString(void *pstr, int increment)
{
    IADDR where;

    where.segment = SEG_GLOBAL;
    where.offset = MexPtrToVM(pstr) + increment;
    where.indirect = FALSE;
    MexKillString(&where);
}


    where = MexStoreHeapByteString(s, len);


void MexArgBegin(PMA pma)
{
    pma->last.segment = SEG_AR;
    pma->last.offset = (VMADDR)AR_CONTROL_DATA;
    pma->arg_size = 0;
}


dword MexArgGetDword(PMA pma)
{
    dword *pdw;

    pma->last.indirect = FALSE;
    pma->arg_size += sizeof(dword);

    pdw = MexFetch(FormDword, &pma->last);
    pma->last.offset += sizeof(dword);

    return pdw ? *pdw : 0;
}


char *MexArgGetString(PMA pma, int fPassByRef)
{
    IADDR ia;
    char *pcData;
    char *rc;
    word wLen;

    if (fPassByRef)
        pcData = MexArgGetRefString(pma, &ia, &wLen);
    else
        pcData = MexArgGetNonRefString(pma, &ia, &wLen);

    if ((rc = malloc(wLen + 1)) == NULL)
        return NULL;

    memcpy(rc, pcData, wLen);
    rc[wLen] = 0;


char *MexArgGetRefString(PMA pma, IADDR *pia, word *pwLen)
{
    IADDR *piaFetch;
    char *str;

    pma->last.indirect = FALSE;
    pma->arg_size += sizeof(IADDR);

    piaFetch = MexFetch(FormAddr, &pma->last);
    pma->last.offset += sizeof(IADDR);

    if (piaFetch != NULL)
    {

        if ((str = MexFetch(FormString, piaFetch)) != NULL)
        {
            }

            if (pwLen)
                *pwLen = *(word *)str;

            str += sizeof(word);
            return str;
        }
    }

    return NULL;
}


char *MexArgGetNonRefString(PMA pma, IADDR *pia, word *pwLen)
{
    IADDR *piaFetch;
    char *str;

    pma->last.indirect = FALSE;
    pma->arg_size += sizeof(IADDR);

    piaFetch = MexFetch(FormAddr, &pma->last);


        if ((str = MexFetch(FormString, piaFetch)) != NULL)
        {
            if (pwLen)
                *pwLen = *(word *)str;

            str += sizeof(word);
            return str;
        }
    }

    return NULL;
}


word MexArgEnd(PMA pma) { return pma->arg_size; }

#endif
