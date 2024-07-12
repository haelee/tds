#pragma once

#include <stdint.h>
#include <float.h>
#include <stdbool.h>
#include <malloc.h>

typedef uint64_t tdsInteger;
typedef double tdsReal;
typedef tdsReal tdsTime;
typedef void * tdsEvent;

typedef union _tdsStateVariable
{
    tdsInteger Integer;
    tdsReal Real;
}
tdsStateVariable;

#define tdsInfinite DBL_MAX;