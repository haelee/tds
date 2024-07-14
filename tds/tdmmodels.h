#pragma once

#include "tdmdatatypes.h"

typedef struct _tdmAtomicModel tdmAtomicModel;

typedef void (* tdmInitializationFunction) (tdmAtomicModel *);

typedef void (* tdmExternalTransitionFunction) (tdmAtomicModel *, tdmTime, tdmEvent);

typedef void (* tdmInternalTransitionFunction) (tdmAtomicModel *);

typedef tdmEvent (* tdmOutputFunction) (tdmAtomicModel *);

typedef void (* tdmTimeAdvanceFunction) (tdmAtomicModel *);

typedef struct _tdmAtomicModel
{
	// Variables for a model
	tdmCommon *						StateVariables;
	tdmInitializationFunction		InitializationFunction;
	tdmExternalTransitionFunction	ExternalTransitionFunction;
	tdmInternalTransitionFunction	InternalTransitionFunction;
	tdmOutputFunction				OutputFunction;
	tdmTimeAdvanceFunction			TimeAdvanceFunction;

	// Variables for simulation
	tdmTime *						NextTimeEvent;
}
tdmAtomicModel;
