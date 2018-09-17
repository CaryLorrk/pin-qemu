#ifndef PIN_API_CONTROL_H
#define PIN_API_CONTROL_H 

#include "base_types.h"

typedef VOID(*FINI_CALLBACK)(INT32 code, VOID *v);

BOOL PIN_Init(INT32 argc, CHAR **argv);
VOID PIN_StartProgram(void);
VOID PIN_AddFiniFunction(FINI_CALLBACK fun, VOID *val);

#endif
