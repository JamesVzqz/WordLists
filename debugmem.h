#ifndef DEBUGMEM_H
#define DEBUGMEM_H
#include"memorymanager.h"
/*
Basic dynamic memory tracer: works by replacing new/delete, new[]/delete[] with
		overloaded versions that track the addresses of the allocated memory.

Usage:	Replace all calls to 'new' you want to track with DEBUG_NEW

		To get a report of the current allocations call GETMEMORYREPORT().
*/

// Check for current allocations
#define GETMEMORYREPORT() memoryReport()

// Reset the number of tracked allocations, does not deallocate
#define RESET() reset()

// Get the number of tracked allocations
#define SIZE() getNumAlloc()

#define DEBUG_NEW new(__FILE__, __func__, __LINE__)

#endif