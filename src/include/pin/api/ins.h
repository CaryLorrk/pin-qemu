#ifndef PIN_API_INS_H
#define PIN_API_INS_H

#include "base_types.h"
#include "arg.h"

typedef VOID(*INS_INSTRUMENT_CALLBACK)(INS ins, VOID *v);

VOID INS_AddInstrumentFunction(INS_INSTRUMENT_CALLBACK fun, VOID *val);
VOID INS_InsertCall(INS ins, IPOINT ipoint, AFUNPTR funptr, ...);


#endif
