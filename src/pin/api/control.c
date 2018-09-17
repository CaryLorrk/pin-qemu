#include <glib.h>
#include "pin/api/base_types.h"
#include "pin/api/control.h"
#include "pin/PinManager.h"

BOOL PIN_Init(INT32 argc, CHAR **argv)
{
    return 0;
}
VOID PIN_StartProgram(void)
{
    pin->cpu_loop(pin->env);
}
VOID PIN_AddFiniFunction(FINI_CALLBACK fun, VOID *val)
{
    g_array_append_val(pin->finiFunctions[0], fun);
    g_array_append_val(pin->finiFunctions[1], val);
    ++pin->n_finiFunctions;
}
