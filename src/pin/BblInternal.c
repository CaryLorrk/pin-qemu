#include <glib.h>
#include "pin/BblInternal.h"
#include "pin/InsInternal.h"

BBL bbl_create(void)
{
    BBL bbl = g_slice_new0(BblInternal);
    return bbl;
}

void bbl_delete(BBL bbl)
{
    if (bbl->insHead != 0)
    {
        g_slice_free_chain(InsInternal, bbl->insHead, next);
    }

    g_slice_free(BblInternal, bbl);
}

void bbl_addIns(BBL bbl, INS ins)
{
    if (bbl->insHead == 0)
    {
        bbl->insHead = bbl->insTail = ins;
    }
    else
    {
        bbl->insTail->next = ins;
        ins->prev = bbl->insTail;
        bbl->insTail = ins;
    }
}
