#include <iostream>
#include <fstream>
#include "pin.H"


static UINT64 icount = 0;

VOID doprint(UINT32 x) { cout << x << endl; }
VOID docount() { icount++; }

VOID Instruction(INS ins, VOID *v)
{   
    INS_InsertCall(ins, IPOINT_BEFORE, (AFUNPTR)(doprint), IARG_UINT32, 32, IARG_END);
    INS_InsertCall(ins, IPOINT_BEFORE, (AFUNPTR)(docount), IARG_END);
}

VOID Fini(INT32 code, VOID *v)
{
    cout << "Count " << icount << endl;
}

int main(int argc, char * argv[])
{
    if (PIN_Init(argc, argv)) return -1;

    INS_AddInstrumentFunction(Instruction, 0);
    PIN_AddFiniFunction(Fini, 0);

    PIN_StartProgram();
    
    return 0;
}
