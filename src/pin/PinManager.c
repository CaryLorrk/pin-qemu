#include "pin/PinManager.h"

PinManager *pin = NULL;

void pin_create(void)
{
    pin = g_malloc(sizeof(PinManager));

    pin->insInstrumentFunctions[0] = g_array_new(FALSE, FALSE, sizeof(INS_INSTRUMENT_CALLBACK));
    pin->insInstrumentFunctions[1] = g_array_new(FALSE, FALSE, sizeof(VOID*));
    pin->n_insInstrumentFunctions = 0;

    pin->finiFunctions[0] = g_array_new(FALSE, FALSE, sizeof(FINI_CALLBACK));
    pin->finiFunctions[1] = g_array_new(FALSE, FALSE, sizeof(VOID*));
    pin->n_finiFunctions = 0;
}

void pin_delete(void)
{
    g_array_free(pin->insInstrumentFunctions[0], TRUE);
    g_array_free(pin->insInstrumentFunctions[1], TRUE);
    g_array_free(pin->finiFunctions[0], TRUE);
    g_array_free(pin->finiFunctions[1], TRUE);
    g_free(pin);
}

void pin_load(const CHAR *path)
{
    if (!g_module_supported()) {
        g_error("Not support dynamic loading");
    }

    pin->pintool = g_module_open(path, G_MODULE_BIND_LAZY);
    if (!pin->pintool) {
        g_error("%s",g_module_error());
    }

    if (!g_module_symbol(pin->pintool, "main", (void**)&pin->pintool_main)) {
        g_error("%s", g_module_error());
    }
}

void callPintool(void *cpu_loop, void *env)
{
    if (!pin)
        return;
    pin->cpu_loop = cpu_loop;
    pin->env = env;
    pin->pintool_main(0,0);
}

void callInsInstrumentFunctions(INS ins)
{
    int idx;
    if (!pin)
        return;
    for (idx = 0; idx < pin->n_insInstrumentFunctions; ++idx)
    {
        INS_INSTRUMENT_CALLBACK func;
        VOID *val;
        func = g_array_index(pin->insInstrumentFunctions[0],
                             INS_INSTRUMENT_CALLBACK,
                             idx);
        val = g_array_index(pin->insInstrumentFunctions[1],
                            VOID*, idx);
        func(ins, val);
    }
}

void callFiniFunctions(int code)
{
    int idx;
    if (!pin)
        return;
    for (idx = 0; idx < pin->n_finiFunctions; ++idx)
    {
        FINI_CALLBACK func;
        VOID *val;
        func = g_array_index(pin->finiFunctions[0],
                             FINI_CALLBACK,
                             idx);
        val = g_array_index(pin->finiFunctions[1],
                            VOID*, idx);
        func(code, val);

    }
}
