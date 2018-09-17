#include <stdarg.h>
#include <stdio.h>
#include <glib.h>
#include "pin/api/ins.h"
#include "pin/PinManager.h"
#include "pin/InsInternal.h"

VOID INS_AddInstrumentFunction(INS_INSTRUMENT_CALLBACK fun, VOID *val)
{
    g_array_append_val(pin->insInstrumentFunctions[0], fun);
    g_array_append_val(pin->insInstrumentFunctions[1], val);
    ++pin->n_insInstrumentFunctions;
}

VOID INS_InsertCall(INS ins, IPOINT ipoint, AFUNPTR funptr, ...)
{
    va_list vl;
    GArray *iargs = g_array_new(FALSE, FALSE, sizeof(INT32));
    size_t n_args = 0;
    INT32 iarg;

    GArray *(*calls)[3];
    switch(ipoint)
    {
        case IPOINT_BEFORE:
            calls = &ins->beforeCalls;
            break;
        default:
            g_error("Not support IPOINT");
            break;
    }

    va_start(vl, funptr);
    iarg = va_arg(vl, INT32);
    while(iarg != IARG_END)
    {
        g_array_append_val(iargs, iarg);
        switch(iarg)
        {
            case IARG_ADDRINT:
            case IARG_PTR:
            case IARG_BOOL:
            case IARG_UINT32:
                iarg = va_arg(vl, INT32);
                g_array_append_val(iargs, iarg);
                break;
            default:
                g_error("Not support IARG");
                break;
        }
        ++n_args;
        iarg = va_arg(vl, INT32);
    }
    g_array_append_val((*calls)[0], funptr);
    g_array_append_val((*calls)[1], iargs);
    g_array_append_val((*calls)[2], n_args);
    ++ins->n_beforeCalls;
}
