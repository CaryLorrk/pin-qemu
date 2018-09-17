#ifndef PIN_INSINTERNAL_H
#define PIN_INSINTERNAL_H

#include "api/base_types.h"
typedef struct _InsInternal
{
    UINT64 pc;
    GArray *beforeCalls[3];
    size_t n_beforeCalls;
    INS next;
    INS prev;
} InsInternal;

INS ins_create(void);
void ins_delete(INS ins);

#endif
