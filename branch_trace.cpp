#include <stdio.h>
#include "pin.H"

using std::string;

FILE* trace;

VOID found_branch(ADDRINT pc, ADDRINT target, BOOL taken) {
    fprintf(trace, "0x%lx, 0x%lx, %d\n", pc, target, taken);
}

VOID instruction_executed(INS ins, VOID* v) {
    if (INS_IsBranch(ins)) {
        INS_InsertCall(ins, IPOINT_BEFORE, (AFUNPTR)found_branch, IARG_INST_PTR, IARG_BRANCH_TARGET_ADDR, IARG_BRANCH_TAKEN, IARG_END);
    }
}

VOID end_trace(INT32 code, VOID* v) {
    fclose(trace);
}

KNOB< string > KnobOutputFile(KNOB_MODE_WRITEONCE, "pintool", "o", "branch_trace.out", "Specify output file name");

INT32 Usage() {
    PIN_ERROR("This Pintool prints a trace of branch addresses\n" + KNOB_BASE::StringKnobSummary() + "\n");
    return -1;
}

int main(int argc, char* argv[]) {
    // Initialize Pin.
    if (PIN_Init(argc, argv))
        return Usage();
    
    // Determine output file name and write the CSV header.
    string trace_file = "branch_trace.out";
    for (int i=0; i<argc; i++)
        if (!strcmp(argv[i], "-o"))
            trace_file = string(argv[i+1]);

    trace = fopen(trace_file.c_str(), "w");
    fprintf(trace, "pc, target, taken\n");

    // Register instruction_executed to be called on every instruction.
    INS_AddInstrumentFunction(instruction_executed, NULL);

    // Register end_trace to be called when the application exits.
    PIN_AddFiniFunction(end_trace, NULL);

    // Start the program. This never returns, so can't clean up afterwards.
    PIN_StartProgram();

    return 0;
}

