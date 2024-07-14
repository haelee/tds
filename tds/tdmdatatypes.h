#pragma once

#include <stdint.h>
#include <float.h>
#include <stdbool.h>

typedef uint64_t	tdmInteger;
typedef double		tdmReal;

typedef union _tdmCommon
{
	tdmInteger	Integer;
	tdmReal		Real;
}
tdmCommon;

typedef tdmReal		tdmTime;
typedef tdmCommon	tdmEvent;

#define tdmTimeInfinite DBL_MAX;
