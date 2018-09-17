#ifndef PIN_BBLINTERNAL_H
#define PIN_BBLINTERNAL_H 

#include "api/base_types.h"

typedef struct _BblInternal
{
    int numInsns;
    INS insHead;
    INS insTail;
} BblInternal;

BBL bbl_create(void);
void bbl_delete(BBL bbl);
void bbl_addIns(BBL bbl, INS ins);

#endif
