///////////////////////////////////////////////////////////////////////////////
// tdm.h
// Model-independent
///////////////////////////////////////////////////////////////////////////////

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

#define tdmTimeInfinite DBL_MAX

///////////////////////////////////////////////////////////////////////////////

typedef struct _tdmDEVSModel tdmDEVSModel;

typedef void (* tdmInitializationFunction) (tdmDEVSModel *);

typedef void (* tdmExternalTransitionFunction) (tdmDEVSModel *, tdmTime, tdmEvent);

typedef void (* tdmInternalTransitionFunction) (tdmDEVSModel *);

typedef tdmEvent (* tdmOutputFunction) (tdmDEVSModel *);

typedef tdmTime (* tdmTimeAdvanceFunction) (tdmDEVSModel *);

typedef struct _tdmDEVSModel
{
	///////////////////////////////////////////////////////////////////////////
	// Variables for defining an atomic model
	///////////////////////////////////////////////////////////////////////////

	//
	tdmCommon *						StateVariables;

	tdmInitializationFunction		InitializationFunction;
	tdmExternalTransitionFunction	ExternalTransitionFunction;
	tdmInternalTransitionFunction	InternalTransitionFunction;
	tdmOutputFunction				OutputFunction;
	tdmTimeAdvanceFunction			TimeAdvanceFunction;

	///////////////////////////////////////////////////////////////////////////
	// Variables for coupling
	///////////////////////////////////////////////////////////////////////////

	// Every output event would be delivered to the models that each element in OutputCouplings points out.
	tdmDEVSModel ** OutputCouplings;

	///////////////////////////////////////////////////////////////////////////
	// Variables for simulation
	///////////////////////////////////////////////////////////////////////////

	// The time of the last event
	tdmTime LastEventTime;

	// The time of the next event
	tdmTime NextEventTime;
}
tdmDEVSModel;

///////////////////////////////////////////////////////////////////////////////

// Initialize the models.
void			TDMInitializeModels	(void);

// Finalize the models.
void			TDMFinalizeModels	(void);

// Return the start address of the model array.
tdmDEVSModel *	TDMGetDEVSModels	(void);
