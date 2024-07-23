///////////////////////////////////////////////////////////////////////////////
// tds.s
// Model-independent
///////////////////////////////////////////////////////////////////////////////

#include "tdm.h"

#include <stdlib.h>
#include <time.h>

// Pointer to the model array
static tdmDEVSModel * TDSDEVSModels = 0;

void TDSInitializeSimulation (tdmTime InitialTime)
{
	tdmDEVSModel * DEVSModel = 0;

	TDSDEVSModels	= TDMGetDEVSModels ();
	DEVSModel		= TDSDEVSModels;

	// For each of the atomic models:
	do
	{
		// Call the initialization function of the model.
		(* DEVSModel -> InitializationFunction) (DEVSModel);

		// Set the time of the last event to the initial time.
		DEVSModel -> LastEventTime = InitialTime;

		// Call the time advance function (ta) of the model.
		// Update the time of the next event using the function's return value.
		DEVSModel -> NextEventTime = InitialTime + (* DEVSModel -> TimeAdvanceFunction) (DEVSModel);
	}
	while (0 != ((++ DEVSModel) -> StateVariables));
}

void TDSFinalizeSimulation (void)
{
}

tdmDEVSModel * TDSGetImminentModel (void)
{
	tdmDEVSModel *	DEVSModel		= TDSDEVSModels;
	tdmDEVSModel *	ImminentModel	= DEVSModel;

	while (0 != ((++ DEVSModel) -> StateVariables))
	{
		if (DEVSModel -> NextEventTime < ImminentModel -> NextEventTime)
		{
			ImminentModel = DEVSModel;
		}
	}

	return ImminentModel -> NextEventTime < tdmTimeInfinite ? ImminentModel : 0;
}

void TDSRun (tdmTime SimulationTime)
{
	tdmDEVSModel *	ImminentModel	= 0;
	tdmDEVSModel **	Couplings		= 0;
	tdmCommon		Event;

	TDSInitializeSimulation (SimulationTime);

	// If there exists an imminent model,
	while (0 != (ImminentModel = TDSGetImminentModel ()))
	{
		SimulationTime = ImminentModel -> NextEventTime;

		// Set the time of the last event to the current simulation time.
		ImminentModel -> LastEventTime = SimulationTime;

		// Call the model's output function (lambda).
		Event = (* ImminentModel -> OutputFunction) (ImminentModel);

		// Call the model's internal transition function (delta_int).
		(* ImminentModel -> InternalTransitionFunction) (ImminentModel);

		// Call the model's time advance function (ta).
		// Update the time of the next event using the function's return value.
		ImminentModel -> NextEventTime = SimulationTime + (* ImminentModel -> TimeAdvanceFunction) (ImminentModel);

		Couplings = ImminentModel -> OutputCouplings;

		// For each of the coupled models,
		while (0 != (* Couplings))
		{
			// Call the model's external transition function (delta_ext).
			(* (* Couplings) -> ExternalTransitionFunction) (* Couplings, SimulationTime - (* Couplings) -> LastEventTime, Event);

			// Set the time of the last event to the current simulation time.
			(* Couplings) -> LastEventTime = SimulationTime;

			// Call the model's time advance function (ta).
			// Update the time of the next event using the function's return value.
			(* Couplings) -> NextEventTime = SimulationTime + (* (* Couplings) -> TimeAdvanceFunction) (* Couplings);

			Couplings ++;
		}
	}

	TDSFinalizeSimulation ();
}

int main (void)
{
	srand (time (0));

	TDMInitializeModels ();

	TDSRun (0.0);

	TDMFinalizeModels ();
	return 0;
}