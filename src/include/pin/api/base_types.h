#ifndef PIN_API_BASE_TYPES_H
#define PIN_API_BASE_TYPES_H 

#include <stdint.h>

typedef void VOID;
typedef char CHAR;
typedef int BOOL;
typedef int32_t INT32;
typedef int64_t INT64;
typedef uint32_t UINT32;
typedef uint64_t UINT64;

typedef int64_t ADDRINT;

typedef VOID(*AFUNPTR)();

struct _InsInternal;
typedef struct _InsInternal* INS;

struct _BblInternal;
typedef struct _BblInternal* BBL;

struct _PinManager;
typedef struct _PinManager PinManager;
extern PinManager *pin;

#endif
