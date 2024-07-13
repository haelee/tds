#pragma once

#include <stdint.h>
#include <float.h>
#include <stdbool.h>

typedef uint64_t	tdsInteger;
typedef double		tdsReal;

typedef union _tdsCommon
{
	tdsInteger	Integer;
	tdsReal		Real;
}
tdsCommon;

typedef tdsReal		tdsTime;
typedef tdsCommon	tdsEvent;

#define tdsTimeInfinite DBL_MAX;
