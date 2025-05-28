// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: vm_read.c,v 1.1.1.1 2002/10/01 17:54:17 sdudley Exp $";
#pragma on(unreferenced)

#define COMPILING_MEX_VM

#include "bfile.h"
#include "prog.h"
#include "vm.h"
#include <string.h>

static void NoMem(void) { (*pfnLogger)("!MEX:  out of memory reading file"); }


    if (Bread(b, (char *)&vmh, sizeof(struct _vmh)) != sizeof(struct _vmh))
        return -1;

    high_cs = vmh.n_inst;


    vmh.lGlobSize += 2048;


    hpinit();


    if (init_symtab(256 + vmh.n_imp) == -1)
        return -1;


    ofs = MexEnterSymtab(" NULL ", sizeof(word));
    *(VMADDR *)(pbDs + ofs) = 0;


    if (Bread(b, (char *)pinCs, byt) != (signed int)byt)
        return -1;

    return 0;
}


        ofs = MexEnterSymtab(iref.name, iref.size);


            memset((char *)pbDs + ofs, '\0', iref.size);
        }


        for (pat = iref.n_patch; pat--;)
        {

            if (gpat.ip > high_cs)
                vm_err(err_patch_ofs);


            if (gpat.argn == 1)
                pinCs[gpat.ip].arg1.addr.offset += ofs;
            else
                pinCs[gpat.ip].arg2.addr.offset += ofs;
        }
    }

    return 0;
}


    for (fdef = vmh.n_fdef; fdef--;)
    {
        struct _dfuncdef dfd;
        struct _funcdef *pfd;

        if (Bread(b, (char *)&dfd, sizeof(dfd)) != sizeof(dfd) ||
            (pfd = malloc(sizeof(struct _funcdef))) == NULL)
        {
            NoMem();
            return -1;
        }

        pfd->quad = dfd.quad;
        pfd->next = fdlist;
        fdlist = pfd;

        if ((pfd->name = strdup(dfd.name)) == NULL)
            return -1;
    }

    return 0;
}


        if (Bread(b, (char *)&dfc, sizeof(dfc)) != sizeof(dfc))
        {
            return -1;
        }

        pvma = pvmaOrig = malloc(size = sizeof(VMADDR) * dfc.n_quads);

        if (pvma == NULL || Bread(b, (char *)pvma, (unsigned)size) != size)
        {
            NoMem();
            return -1;
        }


        for (fdl = fdlist; fdl; fdl = fdl->next)
            if (eqstr(dfc.name, fdl->name))
            {
                while (pvma < pvmaOrig + dfc.n_quads)
                    pinCs[*pvma++].res.jump_label = fdl->quad;

                break;
            }

        free(pvmaOrig);


static int near VmReadProc(BFILE b)
{
    int rc = 0;

    pinCs = NULL;

    if (VmReadFileHdr(b) == -1)
        return -1;

    if (rc != -1 && VmReadGlobDataRefs(b) == -1)
        rc = -1;

    if (rc != -1 && VmReadFuncExports(b) == -1)
        rc = -1;

    if (rc != -1 && VmReadFuncImports(b) == -1)
        rc = -1;

    return rc;
}

