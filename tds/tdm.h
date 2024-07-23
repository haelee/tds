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

///////////////////////////////////////////////////////////////////////////////

typedef struct _tdmDEVSModel tdmDEVSModel;

typedef void (* tdmInitializationFunction) (tdmDEVSModel *);

typedef void (* tdmExternalTransitionFunction) (tdmDEVSModel *, tdmTime, tdmEvent);

typedef void (* tdmInternalTransitionFunction) (tdmDEVSModel *);

typedef tdmEvent (* tdmOutputFunction) (tdmDEVSModel *);

typedef tdmTime (* tdmTimeAdvanceFunction) (tdmDEVSModel *);

typedef struct _tdmDEVSModel
{
	// Variables for an atomic model
	tdmCommon *						StateVariables;
	tdmInitializationFunction		InitializationFunction;
	tdmExternalTransitionFunction	ExternalTransitionFunction;
	tdmInternalTransitionFunction	InternalTransitionFunction;
	tdmOutputFunction				OutputFunction;
	tdmTimeAdvanceFunction			TimeAdvanceFunction;

	// Variables for coupling
	tdmDEVSModel **					OutputCouplings;
}
tdmDEVSModel;

///////////////////////////////////////////////////////////////////////////////

bool			TDMInitializeModels	(void);
bool			TDMFinalizeModels	(void);
tdmDEVSModel *	TDMGetDEVSModels	(void);
