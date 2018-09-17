#include <glib.h>
#include "pin/InsInternal.h"

INS ins_create(void)
{
    INS ins = g_slice_new0(InsInternal);
    ins->beforeCalls[0] = 
        g_array_new(FALSE, FALSE, sizeof(AFUNPTR));
    ins->beforeCalls[1] =
        g_array_new(FALSE, FALSE, sizeof(GArray*));
    ins->beforeCalls[2] =
        g_array_new(FALSE, FALSE, sizeof(size_t));

    return ins;
}

void ins_delete(INS ins)
{
    int idx, i;
    for (idx = 0; idx < 3; ++idx) {
        if (idx == 1) {
            for (i = 0; i < ins->n_beforeCalls; ++i)
            {
                g_array_free(
                        g_array_index(
                            ins->beforeCalls[1],
                            GArray*, i), FALSE);
            }
        }
        g_array_free(ins->beforeCalls[idx], FALSE);
    }
    g_slice_free(InsInternal, ins);
}

