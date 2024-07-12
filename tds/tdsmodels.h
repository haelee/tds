#pragma once

#include "tdsdatatypes.h"

typedef struct _tdsAtomicModel tdsAtomicModel;

// Initialization function
typedef void (* tdsInitializationFunction) (tdsAtomicModel *);

// External transition function
typedef tdsAtomicModel * (* tdsExternalTransitionFunction) (tdsAtomicModel *, tdsTime, tdsEvent);

// Internal transition function
typedef tdsAtomicModel * (* tdsInternalTransitionFunction) (tdsAtomicModel *);
// Output function
typedef tdsEvent (* tdsOutputFunction) (tdsAtomicModel *);

// Time advance function
typedef tdsTime (* tdsTimeAdvanceFunction) (tdsAtomicModel *);

typedef struct _tdsAtomicModel
{
	tdsStateVariable * StateVariables;
	tdsInitializationFunction InitializationFunction;
	tdsExternalTransitionFunction ExternalTransitionFunction;
	tdsInternalTransitionFunction InternalTransitionFunction;
	tdsOutputFunction OutputFunction;
	tdsTimeAdvanceFunction TimeAdvanceFunction;
}
tdsAtomicModel;
