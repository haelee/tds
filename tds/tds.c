// Simulation engine
#include "tds.h"
#include "tdmgenerated.h"

///////////////////////////////////////////////////////////////////////////////
// Static variables
///////////////////////////////////////////////////////////////////////////////

static tdsDEVSSimulator	TDSDEVSSimulators [TDM_NUMBER_OF_ATOMIC_MODELS + 1] = {0};

tdsDEVSSimulator * TDSInitializeSimulation (tdmTime InitialTime)
{
	tdmDEVSModel *		DEVSModel			= TDMGetDEVSModels ();
	tdsDEVSSimulator *	DEVSSimulator		= TDSDEVSSimulators;
	tdsDEVSSimulator *	ImminentSimulator	= DEVSSimulator;

	while (DEVSModel -> StateVariables)
	{
		DEVSSimulator -> DEVSModel = DEVSModel;
		(* DEVSModel -> InitializationFunction) (DEVSModel);

		DEVSSimulator -> LastEventTime = InitialTime;
		DEVSSimulator -> NextEventTime = InitialTime + (* DEVSModel -> TimeAdvanceFunction) (DEVSModel);

		if (DEVSSimulator -> NextEventTime < ImminentSimulator -> NextEventTime)
		{
			ImminentSimulator = DEVSSimulator;
		}

		++ DEVSModel;
		++ DEVSSimulator;
	};

	DEVSSimulator -> DEVSModel		= 0;
	DEVSSimulator -> NextEventTime	= tdmTimeInfinite;

	return ImminentSimulator;
}

void TDSRun (tdmTime InitialTime)
{
//	tdsDEVSSimulator *	DEVSSimulator		= 0;
	tdsDEVSSimulator *	ImminentSimulator	= 0;
	tdmCommon			tdmEvent;

	ImminentSimulator = TDSInitializeSimulation (InitialTime);

	while (ImminentSimulator -> NextEventTime < tdmTimeInfinite)
	{
		// The imminent model generates an output event.
		tdmEvent = (* ImminentSimulator -> DEVSModel -> OutputFunction) (ImminentSimulator -> DEVSModel);

		// The imminent model transitions internally.
		(* ImminentSimulator -> DEVSModel -> InternalTransitionFunction) (ImminentSimulator -> DEVSModel);
	}
}

int main (void)
{
	TDMInitializeModels ();

	TDSRun (0.0);

	TDMFinalizeModels ();
	return 0;
}