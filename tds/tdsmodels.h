#pragma once

#include "tdsdatatypes.h"

typedef struct _tdsAtomicModel tdsAtomicModel;

typedef void (* tdsInitializationFunction) (tdsAtomicModel *);

typedef tdsAtomicModel * (* tdsExternalTransitionFunction) (tdsAtomicModel *, tdsTime, tdsEvent);

typedef tdsAtomicModel * (* tdsInternalTransitionFunction) (tdsAtomicModel *);

typedef tdsEvent (* tdsOutputFunction) (tdsAtomicModel *);

typedef tdsTime (* tdsTimeAdvanceFunction) (tdsAtomicModel *);

typedef struct _tdsAtomicModel
{
	tdsCommon *						StateVariables;
	tdsInitializationFunction		InitializationFunction;
	tdsExternalTransitionFunction	ExternalTransitionFunction;
	tdsInternalTransitionFunction	InternalTransitionFunction;
	tdsOutputFunction				OutputFunction;
	tdsTimeAdvanceFunction			TimeAdvanceFunction;
}
tdsAtomicModel;
