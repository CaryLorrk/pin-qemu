#ifndef PIN_PINMANAGER_H
#define PIN_PINMANAGER_H

#include <glib.h>
#include <gmodule.h>
#include "api/base_types.h"
#include "api/ins.h"
#include "api/control.h"

struct _PinManager
{
    INT32 argc;
    CHAR **argv;

    GModule *pintool;
    int(*pintool_main)(int,char**);

    void (*cpu_loop)(void *);
    void *env;

    GArray *insInstrumentFunctions[2];
    size_t n_insInstrumentFunctions;

    GArray *finiFunctions[2];
    size_t n_finiFunctions;
};

void pin_create(void);
void pin_delete(void);
void pin_load(const CHAR *path);

void callPintool(void *cpu_loop, void *env);

void callInsInstrumentFunctions(INS ins);

void callFiniFunctions(int code);

#endif
